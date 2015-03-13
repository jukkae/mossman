/*
 * JuliaSceneSFMLRenderer.cpp
 *
 *  Created on: Nov 3, 2014
 *      Author: ville
 */

#include "JuliaSceneSFMLRenderer.h"
#include <iostream>
#include <cmath>

namespace mossman {
namespace scenes {
namespace julia {

JuliaSceneSFMLRenderer::JuliaSceneSFMLRenderer(std::shared_ptr<sf::RenderWindow> context, JuliaScene* scene) :
		graphics::SFMLRenderer(context),
		SceneRenderer<JuliaScene>(scene)
{
	if(!mShader.loadFromFile("res/scenes/julia/julia.frag", sf::Shader::Fragment)) {
		std::cout << "UH OH!" << std::endl;
	}

	mTexture.loadFromFile("res/scenes/julia/texture.png");

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

JuliaSceneSFMLRenderer::~JuliaSceneSFMLRenderer() {
	// TODO Auto-generated destructor stub
}

void JuliaSceneSFMLRenderer::render() {
	float x = c.x, y = c.y;
	float angularVelocity = 0.05;
	c.x = x * std::cos(angularVelocity) - y * std::sin(angularVelocity);
	c.y = x * std::sin(angularVelocity) + y * std::cos(angularVelocity);

	mShader.setParameter("c", c);
	mContext->draw(mVertex, &mShader);
	//std::cout << "OK" << std::endl;
}

} /* namespace julia */
} /* namespace scenes */
} /* namespace mossman */
