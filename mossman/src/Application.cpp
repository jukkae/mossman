/*
 * Application.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: ville
 */

#include "Application.h"
#include "Scenes/Julia/JuliaScene.h"
#include <memory>

namespace Mossman {

Application::Application() : mWindow(nullptr), mQuitSignaled(false) {
	// TODO Auto-generated constructor stub

}

Application::~Application() {
	// TODO Auto-generated destructor stub
}

void Application::init() {
	using namespace Mossman::Scenes::Julia;
	mWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 1024), "SFML works!");
	mWindow->setVerticalSyncEnabled(true);

	JuliaScene* juliaScene = new JuliaScene();

	JuliaSceneSFMLRenderer* juliaSceneRenderer = new JuliaSceneSFMLRenderer(mWindow, juliaScene);

	int i = mSceneManager.addScene(juliaScene, juliaSceneRenderer);
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

} /* namespace Mossman */
