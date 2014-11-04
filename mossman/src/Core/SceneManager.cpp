/*
 * SceneManager.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: ville
 */

#include "SceneManager.h"
#include "Scene.h"

namespace Mossman {
namespace Core {

SceneManager::SceneManager() : mActiveScene(nullptr), mActiveRenderer(nullptr) {
	// TODO Auto-generated constructor stub

}

SceneManager::~SceneManager() {
	// TODO Auto-generated destructor stub
}

int SceneManager::addScene(Scene* scene, Renderer* renderer) {
	return addScene(
			std::unique_ptr<Scene>(scene),
			std::unique_ptr<Renderer>(renderer)
	);
}

int SceneManager::addScene(std::unique_ptr<Scene> scene, std::unique_ptr<Renderer> renderer) {
	if(mScenes.size() == 0) {
		mActiveScene = scene.get();
		mActiveRenderer = renderer.get();
	}
	mScenes.push_back(std::move(scene));
	mRenderers.push_back(std::move(renderer));
	return mScenes.size() - 1;
}

void SceneManager::setActiveScene(unsigned int index) {
	if(index >= mScenes.size()) return;

	auto newScene = mScenes[index].get();
	if(newScene == mActiveScene) return;
	if(mActiveScene != nullptr) mActiveScene->deactivated();
	mActiveScene = newScene;
	mActiveScene->activated();
	mActiveRenderer = mRenderers[index].get();
}
void SceneManager::updateActiveScene(double dt) {
	if(mActiveScene == nullptr) return;

	mActiveScene->update(dt);
}

void SceneManager::renderActiveScene() {
	if(mActiveRenderer == nullptr) return;

	mActiveRenderer->render();
}

} /* namespace Core */
} /* namespace Mossman */
