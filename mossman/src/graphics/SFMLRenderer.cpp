/*
 * Renderer.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: ville
 */

#include "SFMLRenderer.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace mossman {
namespace graphics {

SFMLRenderer::SFMLRenderer(std::shared_ptr<sf::RenderWindow> context) : mContext(context) {

}

SFMLRenderer::~SFMLRenderer() {
	// TODO Auto-generated destructor stub
}

} /* namespace graphics */
} /* namespace mossman */
