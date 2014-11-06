/*
 * SceneManager.h
 *
 *  Created on: Nov 3, 2014
 *      Author: ville
 */

#ifndef MOSSMAN_SRC_CORE_SCENEMANAGER_H_
#define MOSSMAN_SRC_CORE_SCENEMANAGER_H_

#include <vector>
#include <memory>

#include "Renderer.h"

namespace mossman {

class Scene;

class SceneManager {
public:
	SceneManager();
	virtual ~SceneManager();

	int addScene(std::unique_ptr<Scene> scene, std::unique_ptr<Renderer> renderer);
	int addScene(Scene* scene, Renderer* renderer);

	void setActiveScene(unsigned int index);
	void updateActiveScene(double dt);
	void renderActiveScene();

private:
	std::vector<std::unique_ptr<Scene>> mScenes;
	std::vector<std::unique_ptr<Renderer>> mRenderers;
	Scene* mActiveScene;
	Renderer* mActiveRenderer;
};

} /* namespace mossman */

#endif /* MOSSMAN_SRC_CORE_SCENEMANAGER_H_ */
