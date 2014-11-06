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

namespace mossman {

Application::Application() : mWindow(nullptr), mQuitSignaled(false) {
	// TODO Auto-generated constructor stub

}

Application::~Application() {
	// TODO Auto-generated destructor stub
}

void Application::init() {
	using namespace mossman::scenes;
	mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 1024), "mossman");
	mWindow->setVerticalSyncEnabled(true);

	JuliaScene* juliaScene = new JuliaScene();

	julia::JuliaSceneSFMLRenderer* juliaSceneRenderer = new julia::JuliaSceneSFMLRenderer(mWindow, juliaScene);

	mSceneManager.addScene(juliaScene, juliaSceneRenderer);
}

void Application::update(double dt) {
	sf::Event event;
	while (mWindow->pollEvent(event))
	{
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
