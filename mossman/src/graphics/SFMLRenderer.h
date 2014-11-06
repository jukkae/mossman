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

namespace mossman {
namespace graphics {

class SFMLRenderer {
public:
	SFMLRenderer(std::shared_ptr<sf::RenderWindow> context);
	virtual ~SFMLRenderer();
protected:
	std::shared_ptr<sf::RenderWindow> mContext;
};

} /* namespace graphics */
} /* namespace mossman */

#endif /* MOSSMAN_SRC_GRAPHICS_SFMLRENDERER_H_ */
