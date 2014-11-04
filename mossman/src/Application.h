/*
 * Application.h
 *
 *  Created on: Nov 3, 2014
 *      Author: ville
 */

#ifndef MOSSMAN_SRC_APPLICATION_H_
#define MOSSMAN_SRC_APPLICATION_H_

#include <SFML/Graphics.hpp>
#include <memory>

#include "Core/SceneManager.h"

namespace Mossman {

using namespace Mossman::Core;

class Application {
public:
	Application();
	virtual ~Application();

	/**
	 * Initialize the application, creating the window etc.
	 */
	void init();

	/**
	 * Update the application by dt seconds.
	 */
	void update(double dt);

	bool isRunning() const;

	std::shared_ptr<sf::RenderWindow> getRenderContext() const;

private:
	std::shared_ptr<sf::RenderWindow> mWindow;
	SceneManager mSceneManager;
	bool mQuitSignaled;
};

} /* namespace Mossman */

#endif /* MOSSMAN_SRC_APPLICATION_H_ */
