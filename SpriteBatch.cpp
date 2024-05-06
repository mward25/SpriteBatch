#include "SpriteBatch.hpp"
#include "Common.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

namespace swift
{
	SpriteBatch::SpriteBatch(const sf::Texture& tex, unsigned int s)
	:	vertices(s * 6),
		texture(tex),
	    spriteNum(0)
	{
		sf::Vector2f texSize = static_cast<sf::Vector2f>(texture.getSize());
		for(auto i = 0u; i < vertices.size(); i += 6)
		{
            /// Quad (Deprecated)
            /*vertices[i].texCoords = {0, 0};
			vertices[i + 1].texCoords = {texSize.x, 0};
			vertices[i + 2].texCoords = texSize;
			vertices[i + 3].texCoords = {0, texSize.y};*/
            /// Ol' Triangle method
			/*vertices[i].texCoords = {0, 0};
			vertices[i + 1].texCoords = {texSize.x, 0};
			vertices[i + 2].texCoords = {0, texSize.y};
			vertices[i + 3].texCoords = texSize;
			vertices[i + 4].texCoords = {0, texSize.y};
			vertices[i + 5].texCoords = {texSize.x, 0};*/
            std::array<sf::Vector2f, 6> triangles = getTrianglesFromVector(texSize);
            for( int j = 0; j < 6; j++ ) { 
                vertices[i+j].texCoords = triangles[j];
            }
		}
	}
	
	const std::vector<sf::Vertex>& SpriteBatch::getVertices() const
	{
		return vertices;
	}

	std::array<sf::Vertex*, 6> SpriteBatch::addSprite()
	{
		if((spriteNum + 1) * 6 <= vertices.size())
		{
            std::cout << "Adding sprite, spriteNum = " << spriteNum << std::endl;
			unsigned int s = spriteNum * 6;
			spriteNum++;
			return {&vertices[s], &vertices[s + 1], &vertices[s + 2], &vertices[s + 3], &vertices[s+4], &vertices[s+5]};
		}
		else
        {
            std::cout << " Not adding sprite, (spriteNum+1)*6=" << (spriteNum+1)*6 << std::endl;
			return {nullptr};
        }
	}
	
	sf::Vector2u SpriteBatch::getTextureSize() const
	{
		return texture.getSize();
	}

	void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.texture = &texture;
		target.draw(vertices.data(), spriteNum * 6, sf::Triangles, states);
	}
}
