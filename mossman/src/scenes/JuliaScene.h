/*
 * JuliaScene.h
 *
 *  Created on: Nov 3, 2014
 *      Author: ville
 */

#ifndef SCENES_JULIA_JULIASCENE_H_
#define SCENES_JULIA_JULIASCENE_

#include "core/Scene.h"

namespace mossman {
namespace scenes {

class JuliaScene : public Scene {
public:
	JuliaScene();
	virtual ~JuliaScene();

	virtual void update(double dt);
	virtual void activated();
	virtual void deactivated();
};

} /* namespace scenes */
} /* namespace mossman */

#endif /* SCENES_JULIA_JULIASCENE_H_ */
