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

typedef unsigned short MY_TYPE; // buffer format
#define FORMAT RTAUDIO_SINT8

namespace mossman {

//rtaudio input data struct
struct InputData {
	MY_TYPE* buffer;
	unsigned long bufferBytes;
	unsigned long totalFrames;
	unsigned long frameCounter;
	unsigned int channels;
};

// Interleaved buffers for rtaudio
// Callback function where data from physical buffer is copied to logical buffer
int input(void * /*outputBuffer*/, void *inputBuffer,
		unsigned int nBufferFrames, double /*streamTime*/,
		RtAudioStreamStatus /*status*/, void *data) {
	InputData *iData = (InputData *) data;

	// Simply copy the data to our allocated buffer.
	// TODO smarter handling
	unsigned int frames = nBufferFrames;
	if (iData->frameCounter + nBufferFrames > iData->totalFrames) {
		frames = iData->totalFrames - iData->frameCounter;
		iData->bufferBytes = frames * iData->channels * sizeof(MY_TYPE);
	}

	unsigned long offset = iData->frameCounter * iData->channels;
	memcpy(iData->buffer + offset, inputBuffer, iData->bufferBytes);
	iData->frameCounter += frames;

	// when buffer fills, start over again
	if (iData->frameCounter >= iData->totalFrames){
		iData->frameCounter = 0;
	}
	return 0;
}

RtAudio audio;
RtAudio adc;
InputData data;
unsigned int channels, fs, bufferFrames, device = 0, offset = 0;

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

	// rtaudio buffer stuff starts here

	double time = 0.1;

	channels = 2;
	fs = 44100;
	adc.showWarnings(true);

	// Set our stream parameters for input only.
	bufferFrames = 512;
	RtAudio::StreamParameters iParams;
	iParams.deviceId = adc.getDefaultInputDevice(); // default device
	iParams.nChannels = channels;
	iParams.firstChannel = offset;

	data.buffer = 0;
	try {
		adc.openStream( NULL, &iParams, FORMAT, fs, &bufferFrames, &input,
				(void *) &data);
	} catch (RtAudioError& e) {
		std::cout << '\n' << e.getMessage() << '\n' << std::endl;
	}

	data.bufferBytes = bufferFrames * channels * sizeof(MY_TYPE);
	data.totalFrames = (unsigned long) (fs * time);
	data.frameCounter = 0;
	data.channels = channels;
	unsigned long totalBytes;
	totalBytes = data.totalFrames * channels * sizeof(MY_TYPE);

	data.buffer = (MY_TYPE*) malloc(totalBytes);
	if (data.buffer == 0) {
		std::cout << "Memory allocation error ... quitting!\n";
		// goto cleanup;
	}

	try {
		adc.startStream();
	} catch (RtAudioError& e) {
		std::cout << '\n' << e.getMessage() << '\n' << std::endl;
		// goto cleanup;
	}

	// Create an api map.
	// PROBING STARTS HERE
	/*
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

	 std::cout << "\nCompiled APIs:\n";
	 for (unsigned int i = 0; i < apis.size(); i++)
	 std::cout << "  " << apiMap[apis[i]] << std::endl;

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
	 */
	//END OF PROBING
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

	// rtaudio: read stuff from buffer
	std::cout << "\n";
	for (int i = 0; i < data.totalFrames * channels; i++) {
		std::cout << data.buffer[i] << " ";
	}

}

bool Application::isRunning() const {
	return !mQuitSignaled;
}

std::shared_ptr<sf::RenderWindow> Application::getRenderContext() const {
	return mWindow;
}

} /* namespace mossman */
