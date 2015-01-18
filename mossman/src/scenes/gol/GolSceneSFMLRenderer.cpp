/*
 * GolSceneSFMLRenderer.cpp
 * Created on: 18.1.2015
 *     author: jukka
 */

#include "GolSceneSFMLRenderer.h"
#include <iostream>
#include <cmath>

namespace mossman {
namespace scenes {
namespace gol {

GolSceneSFMLRenderer::GolSceneSFMLRenderer(std::shared_ptr<sf::RenderWindow> context, GolScene* scene) :
		graphics::SFMLRenderer(context),
		SceneRenderer<GolScene>(scene)
{
	if(!mShader.loadFromFile("res/scenes/gol/gol.frag", sf::Shader::Fragment)) {
		std::cout << "UH OH!" << std::endl;
	}

	mTexture.loadFromFile("res/scenes/gol/texture.png");

	c = sf::Vector2f(0.5, 0.5);

	sf::Vector2u windowSize = mContext->getSize();
	auto quad = sf::VertexArray(sf::Quads, 4);
	quad[0].texCoords = sf::Vector2f(0,0);
	quad[1].texCoords = sf::Vector2f((float) windowSize.x, 0);
	quad[2].texCoords = sf::Vector2f((float) windowSize.x, (float) windowSize.y);
	quad[3].texCoords = sf::Vector2f(0, (float) windowSize.y);

	quad[0].position = sf::Vector2f(0, 0);
	quad[1].position = sf::Vector2f((float) windowSize.x, 0);
	quad[2].position = sf::Vector2f((float) windowSize.x, (float) windowSize.y);
	quad[3].position = sf::Vector2f(0, (float) windowSize.y);

	mVertex = quad;
	mShrink = 4.0f / windowSize.x;

	mShader.setParameter("iterations", 30);
	mShader.setParameter("translateX", windowSize.x / 2);
	mShader.setParameter("translateY", windowSize.y / 2);
	mShader.setParameter("shrink", mShrink);
	mShader.setParameter("tex", mTexture);

}

GolSceneSFMLRenderer::~GolSceneSFMLRenderer() {
	// TODO Auto-generated destructor stub
}

void GolSceneSFMLRenderer::render() {
	float x = c.x, y = c.y;
	float angularVelocity = 0.05;
	c.x = x * std::cos(angularVelocity) - y * std::sin(angularVelocity);
	c.y = x * std::sin(angularVelocity) + y * std::cos(angularVelocity);

	mShader.setParameter("c", c);
	mContext->draw(mVertex, &mShader);
	std::cout << "OK" << std::endl;
}

} /* namespace gol */
} /* namespace scenes */
} /* namespace mossman */
