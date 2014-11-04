/*
 * SceneRenderer.h
 *
 *  Created on: Nov 4, 2014
 *      Author: ville
 */

#ifndef MOSSMAN_SRC_GRAPHICS_SCENERENDERER_H_
#define MOSSMAN_SRC_GRAPHICS_SCENERENDERER_H_

#include "Renderer.h"

namespace Mossman {
namespace Graphics {

template<class TScene>
class SceneRenderer : public Renderer {
public:
	SceneRenderer(TScene* scene) {
		mScene = scene;
	}
	virtual ~SceneRenderer() {};
	virtual void render() = 0;
protected:
	TScene* mScene;
};

} /* namespace Graphics */
} /* namespace Mossman */

#endif /* MOSSMAN_SRC_GRAPHICS_SCENERENDERER_H_ */
