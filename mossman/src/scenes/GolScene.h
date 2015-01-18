/*
 * GolScene.h
 * Created on: 18.1.2015
 *     Author: jukka
 */

#ifndef SCENES_GOL_GOLSCENE_H_
#define SCENES_GOL_GOLSCENE_

#include "core/Scene.h"

namespace mossman {
namespace scenes {

class GolScene: public Scene {
public:
	GolScene();
	virtual ~GolScene();

	virtual void update(double dt);
	virtual void activated();
	virtual void deactivated();
};

} /* namespace scenes */
} /* namespace mossman */

#endif /* SCENES_GOL_GOLSCENE_H_ */
