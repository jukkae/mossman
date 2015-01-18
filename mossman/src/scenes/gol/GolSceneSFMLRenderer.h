/*
 * GolSceneSFMLRenderer.h
 *
 *  Created on: 18.1.2015
 *      author: jukka
 */

#ifndef MOSSMAN_SRC_SCENES_GOL_GOLSCENESFMLRENDERER_H_
#define MOSSMAN_SRC_SCENES_GOL_GOLSCENESFMLRENDERER_H_

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "graphics/SFMLRenderer.h"
#include "core/SceneRenderer.h"

namespace mossman {
namespace scenes {

class GolScene;

namespace gol {

class GolSceneSFMLRenderer : public graphics::SFMLRenderer, public SceneRenderer<GolScene> {
public:
	GolSceneSFMLRenderer(std::shared_ptr<sf::RenderWindow> context, GolScene* scene);
	virtual ~GolSceneSFMLRenderer();
	void render();
private:
	sf::Shader mShader;
	sf::Vector2f c;
	sf::VertexArray mVertex;
	sf::Texture mTexture;
	float mShrink;
};

} /* namespace gol */
} /* namespace scenes */
} /* namespace mossman */

#endif /* MOSSMAN_SRC_SCENES_GOL_GOLSCENESFMLRENDERER_H_ */
