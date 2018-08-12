#include <SFML\Graphics.hpp>
#include "AbstractTile.hpp"

#ifndef	MAP_CHUNK_HPP
#define MAP_CHUNK_HPP


class TextureChunk
{
public:
	TextureChunk(const sf::Texture* texture, const std::string textureName);

	void load();

	void unload();

	void drawForeground(sf::RenderTarget& target);
	void drawBackground(sf::RenderTarget& target);

	void appendTile(std::shared_ptr<AbstractTile> tile);
	std::string getTextureName() { return textureName; }
private:
	//foreground
	sf::VertexArray foreground;
	//background
	sf::VertexArray background;


	std::string textureName;
	const sf::Texture* texture;

	std::vector<std::shared_ptr<AbstractTile >> tiles;

};


class MapChunk
{
public:
	MapChunk() {};

	void appendTile(std::shared_ptr<AbstractTile> tile);

	void load()
	{
		for each (TextureChunk chunk in textureChunks)
		{
			chunk.load();
		}
	}

	void unload();

	void drawForeground(sf::RenderTarget& target);
	void drawBackground(sf::RenderTarget& target);

private:
	std::vector<TextureChunk> textureChunks;
};

#endif