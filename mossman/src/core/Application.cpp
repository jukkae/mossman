/*
 * Application.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: ville
 */

#include "Application.h"

#include <memory>

#include "scenes/julia/JuliaSceneSFMLRenderer.h"
#include "scenes/JuliaScene.h"

#include "scenes/gol/GolSceneSFMLRenderer.h"
#include "scenes/GolScene.h"

namespace mossman {

Application::Application() :
		mWindow(nullptr), mQuitSignaled(false) {
	// TODO Auto-generated constructor stub

}

Application::~Application() {
	// TODO Auto-generated destructor stub
}

void Application::init() {
	using namespace mossman::scenes;
	mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 1024),
			"mossman");
	mWindow->setVerticalSyncEnabled(true);

	JuliaScene* juliaScene = new JuliaScene();

	julia::JuliaSceneSFMLRenderer* juliaSceneRenderer =
			new julia::JuliaSceneSFMLRenderer(mWindow, juliaScene);

	mSceneManager.addScene(juliaScene, juliaSceneRenderer);

	GolScene* golScene = new GolScene();
	gol::GolSceneSFMLRenderer* golSceneRenderer = new gol::GolSceneSFMLRenderer(
			mWindow, golScene);

	mSceneManager.addScene(golScene, golSceneRenderer);

	// TODO this is only here to get RtAudio up and running,
	// refactor later!

	// Create an api map.
	std::map<int, std::string> apiMap;
	apiMap[RtAudio::MACOSX_CORE] = "OS-X Core Audio";
	apiMap[RtAudio::WINDOWS_ASIO] = "Windows ASIO";
	apiMap[RtAudio::WINDOWS_DS] = "Windows Direct Sound";
	apiMap[RtAudio::WINDOWS_WASAPI] = "Windows WASAPI";
	apiMap[RtAudio::UNIX_JACK] = "Jack Client";
	apiMap[RtAudio::LINUX_ALSA] = "Linux ALSA";
	apiMap[RtAudio::LINUX_PULSE] = "Linux PulseAudio";
	apiMap[RtAudio::LINUX_OSS] = "Linux OSS";
	apiMap[RtAudio::RTAUDIO_DUMMY] = "RtAudio Dummy";

	std::vector<RtAudio::Api> apis;
	RtAudio::getCompiledApi(apis);

	std::cout << "\nRtAudio Version " << RtAudio::getVersion() << std::endl;

	std::cout << "\nCompiled APIs:\n";
	for (unsigned int i = 0; i < apis.size(); i++)
		std::cout << "  " << apiMap[apis[i]] << std::endl;

	RtAudio audio;
	RtAudio::DeviceInfo info;

	std::cout << "\nCurrent API: " << apiMap[audio.getCurrentApi()]
			<< std::endl;

	unsigned int devices = audio.getDeviceCount();
	std::cout << "\nFound " << devices << " device(s) ...\n";

	for (unsigned int i = 0; i < devices; i++) {
		info = audio.getDeviceInfo(i);

		std::cout << "\nDevice Name = " << info.name << '\n';
		if (info.probed == false)
			std::cout << "Probe Status = UNsuccessful\n";
		else {
			std::cout << "Probe Status = Successful\n";
			std::cout << "Output Channels = " << info.outputChannels << '\n';
			std::cout << "Input Channels = " << info.inputChannels << '\n';
			std::cout << "Duplex Channels = " << info.duplexChannels << '\n';
			if (info.isDefaultOutput)
				std::cout << "This is the default output device.\n";
			else
				std::cout << "This is NOT the default output device.\n";
			if (info.isDefaultInput)
				std::cout << "This is the default input device.\n";
			else
				std::cout << "This is NOT the default input device.\n";
			if (info.nativeFormats == 0)
				std::cout << "No natively supported data formats(?)!";
			else {
				std::cout << "Natively supported data formats:\n";
				if (info.nativeFormats & RTAUDIO_SINT8)
					std::cout << "  8-bit int\n";
				if (info.nativeFormats & RTAUDIO_SINT16)
					std::cout << "  16-bit int\n";
				if (info.nativeFormats & RTAUDIO_SINT24)
					std::cout << "  24-bit int\n";
				if (info.nativeFormats & RTAUDIO_SINT32)
					std::cout << "  32-bit int\n";
				if (info.nativeFormats & RTAUDIO_FLOAT32)
					std::cout << "  32-bit float\n";
				if (info.nativeFormats & RTAUDIO_FLOAT64)
					std::cout << "  64-bit float\n";
			}
			if (info.sampleRates.size() < 1)
				std::cout << "No supported sample rates found!";
			else {
				std::cout << "Supported sample rates = ";
				for (unsigned int j = 0; j < info.sampleRates.size(); j++)
					std::cout << info.sampleRates[j] << " ";
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;

	//END OF TEST

	/*
	 RtAudio *audio = 0;
	 try {
	 audio = new RtAudio();
	 } catch (RtAudioError &error) {
	 error.printMessage();
	 std::cout << "Error initializing RtAudio";
	 exit(EXIT_FAILURE);
	 }
	 */

}

void Application::update(double dt) {
	sf::Event event;
	while (mWindow->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			mQuitSignaled = true;
			mWindow->close();
			return;
		}
	}

	mSceneManager.updateActiveScene(dt);
	mWindow->clear();
	mSceneManager.renderActiveScene();
	mWindow->display();
}

bool Application::isRunning() const {
	return !mQuitSignaled;
}

std::shared_ptr<sf::RenderWindow> Application::getRenderContext() const {
	return mWindow;
}

} /* namespace mossman */
