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
#include "RtAudio.h" //TODO seems reasonable to include here, right?
// not sure about RtAudio being under core, though

#include "SceneManager.h"

namespace mossman {

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

} /* namespace mossman */

#endif /* MOSSMAN_SRC_APPLICATION_H_ */
