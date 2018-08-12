#include "MapChunk.hpp"

TextureChunk::TextureChunk(const sf::Texture * texture, const std::string textureName)
{
	this->texture = texture;
	this->textureName = textureName;
	foreground = std::make_shared<sf::VertexArray>(sf::Quads);
	background = std::make_shared<sf::VertexArray>(sf::Quads);
}

void TextureChunk::load()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i]->isBackground())
			tiles[i]->load(background);
		else
			tiles[i]->load(foreground);
	}
}

void TextureChunk::unload()
{
	foreground->clear();
	background->clear();
	for each (auto tile in tiles)
	{
		tile->unload();
	}

}

void TextureChunk::drawForeground(sf::RenderTarget & target)
{
	target.draw(*foreground, texture);
}

void TextureChunk::drawBackground(sf::RenderTarget & target)
{
	target.draw(*background, texture);
}

void TextureChunk::appendTile(std::shared_ptr<AbstractTile> tile)
{
	tiles.push_back(tile);
}




void MapChunk::appendTile(std::shared_ptr<AbstractTile> tile)
{
	if (tile == nullptr)return;

	for (int i = 0; i < textureChunks.size(); i++)
	{
		textureChunks[i].appendTile(tile);
		return;
	}

	textureChunks.push_back(TextureChunk(tile->getTileDefinition().texture,
	tile->getTileDefinition().texture_name));
	textureChunks.back().appendTile(tile);
}

void MapChunk::load()
{
	for (int i = 0; i < textureChunks.size(); i++)
	{
		textureChunks[i].load();
	}
}

void MapChunk::unload()
{
	for (int i = 0; i < textureChunks.size(); i++)
	{
		textureChunks[i].unload();
	}
}

void MapChunk::drawForeground(sf::RenderTarget & target)
{
	for (int i = 0; i < textureChunks.size(); i++)
	{
		textureChunks[i].drawForeground(target);
	}
}

void MapChunk::drawBackground(sf::RenderTarget & target)
{
	for (int i = 0; i < textureChunks.size(); i++)
	{
		textureChunks[i].drawBackground(target);
	}
}
