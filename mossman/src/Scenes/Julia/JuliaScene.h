/*
 * JuliaScene.h
 *
 *  Created on: Nov 3, 2014
 *      Author: ville
 */

#ifndef SCENES_JULIA_JULIASCENE_H_
#define SCENES_JULIA_JULIASCENE_

#include "../../Core/Scene.h"
#include "JuliaSceneSFMLRenderer.h"

namespace Mossman {
namespace Scenes {
namespace Julia {

using namespace Mossman::Core;

class JuliaScene : public Scene {
public:
	JuliaScene();
	virtual ~JuliaScene();

	virtual void update(double dt);
	virtual void activated();
	virtual void deactivated();
};

} /* namespace Julia */
} /* namespace Scenes */
} /* namespace Mossman */

#endif /* SCENES_JULIA_JULIASCENE_H_ */
