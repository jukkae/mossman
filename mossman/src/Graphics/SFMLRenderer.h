/*
 * Renderer.h
 *
 *  Created on: Nov 3, 2014
 *      Author: ville
 */

#ifndef MOSSMAN_SRC_GRAPHICS_SFMLRENDERER_H_
#define MOSSMAN_SRC_GRAPHICS_SFMLRENDERER_H_

#include <memory>
#include <SFML/Graphics.hpp>

namespace Mossman {
namespace Graphics {

class SFMLRenderer {
public:
	SFMLRenderer(std::shared_ptr<sf::RenderWindow> context);
	virtual ~SFMLRenderer();
protected:
	std::shared_ptr<sf::RenderWindow> mContext;
};

} /* namespace Graphics */
} /* namespace Mossman */

#endif /* MOSSMAN_SRC_GRAPHICS_SFMLRENDERER_H_ */
