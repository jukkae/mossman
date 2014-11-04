/*
 * Renderer.h
 *
 *  Created on: Nov 4, 2014
 *      Author: ville
 */

#ifndef MOSSMAN_SRC_GRAPHICS_RENDERER_H_
#define MOSSMAN_SRC_GRAPHICS_RENDERER_H_

namespace Mossman {
namespace Graphics {

class Renderer {
public:
	Renderer() {};
	virtual ~Renderer() {};
	virtual void render() = 0;
};

} /* namespace Graphics */
} /* namespace Mossman */

#endif /* MOSSMAN_SRC_GRAPHICS_RENDERER_H_ */
