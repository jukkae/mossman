/*
 * Renderer.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: ville
 */

#include <SFML/Graphics.hpp>
#include <memory>
#include "SFMLRenderer.h"

namespace Mossman {
namespace Graphics {

SFMLRenderer::SFMLRenderer(std::shared_ptr<sf::RenderWindow> context) : mContext(context) {

}

SFMLRenderer::~SFMLRenderer() {
	// TODO Auto-generated destructor stub
}

} /* namespace Graphics */
} /* namespace Mossman */
