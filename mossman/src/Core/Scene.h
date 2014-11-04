/*
 * Scene.h
 *
 *  Created on: Nov 3, 2014
 *      Author: ville
 */

#ifndef MOSSMAN_SRC_CORE_SCENE_H_
#define MOSSMAN_SRC_CORE_SCENE_H_

#include "../Application.h"

namespace Mossman {
namespace Core {

class Scene {
public:
	Scene();
	virtual ~Scene();

	virtual void update(double dt) = 0;
	virtual void activated() = 0;
	virtual void deactivated() = 0;
};

} /* namespace Core */
} /* namespace Mossman */

#endif /* MOSSMAN_SRC_CORE_SCENE_H_ */
