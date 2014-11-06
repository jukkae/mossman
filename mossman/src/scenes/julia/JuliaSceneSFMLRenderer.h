/*
 * JuliaSceneSFMLRenderer.h
 *
 *  Created on: Nov 3, 2014
 *      Author: ville
 */

#ifndef MOSSMAN_SRC_SCENES_JULIA_JULIASCENESFMLRENDERER_H_
#define MOSSMAN_SRC_SCENES_JULIA_JULIASCENESFMLRENDERER_H_

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "graphics/SFMLRenderer.h"
#include "core/SceneRenderer.h"

namespace mossman {
namespace scenes {

class JuliaScene;

namespace julia {

class JuliaSceneSFMLRenderer : public graphics::SFMLRenderer, public SceneRenderer<JuliaScene> {
public:
	JuliaSceneSFMLRenderer(std::shared_ptr<sf::RenderWindow> context, JuliaScene* scene);
	virtual ~JuliaSceneSFMLRenderer();
	void render();
private:
	sf::Shader mShader;
	sf::Vector2f c;
	sf::VertexArray mVertex;
	sf::Texture mTexture;
	float mShrink;
};

} /* namespace julia */
} /* namespace scenes */
} /* namespace mossman */

#endif /* MOSSMAN_SRC_SCENES_JULIA_JULIASCENESFMLRENDERER_H_ */
