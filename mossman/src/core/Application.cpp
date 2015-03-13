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

	RtAudio *audio = 0;
	try {
		audio = new RtAudio();
	} catch (RtAudioError &error) {
		error.printMessage();
		std::cout << "Error initializing RtAudio";
		exit(EXIT_FAILURE);
	}

	// TODO this here only to test if RtAudio works at all, remove / move later
	int devices = audio->getDeviceCount();

	RtAudio::DeviceInfo info;
	  for (int i=1; i<=devices; i++) {

	    try {
	      info = audio->getDeviceInfo(i);
	    }
	    catch (RtAudioError &error) {
	      error.printMessage();
	      break;
	    }

	    // max number of output channels for each device
	    std::cout << "device = " << i;
	    std::cout << ": maximum output channels = " << info.outputChannels << "\n";
	  }

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
