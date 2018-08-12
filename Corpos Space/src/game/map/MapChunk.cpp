#include "MapChunk.hpp"

TextureChunk::TextureChunk(const sf::Texture * texture, const std::string textureName)
{
	this->texture = texture;
	this->textureName = textureName;
}

void TextureChunk::load()
{
	for each (auto tile in tiles)
	{
		if(tile->isBackground())
			tile->load(background);
		else
			tile->load(foreground);
	}
}

void TextureChunk::unload()
{
	foreground.clear();
	background.clear();
	for each (auto tile in tiles)
	{
		tile->unload();
	}

}

void TextureChunk::drawForeground(sf::RenderTarget & target)
{
	target.draw(foreground, texture);
}

void TextureChunk::drawBackground(sf::RenderTarget & target)
{
	target.draw(background, texture);
}

void TextureChunk::appendTile(std::shared_ptr<AbstractTile> tile)
{
	tiles.push_back(tile);
}

void MapChunk::appendTile(std::shared_ptr<AbstractTile> tile)
{
	if (tile == nullptr)return;
	for each (auto chunk in textureChunks)
	{
		if (chunk.getTextureName() == tile->getTileDefinition().texture_name)
		{
			chunk.appendTile(tile);
			return;
		}
	}
	textureChunks.push_back(TextureChunk(tile->getTileDefinition().texture,
	tile->getTileDefinition().texture_name));
	textureChunks.back().appendTile(tile);
}

void MapChunk::unload()
{
	for each (TextureChunk chunk in textureChunks)
	{
		chunk.unload();
	}
}

void MapChunk::drawForeground(sf::RenderTarget & target)
{
	for each (TextureChunk chunk in textureChunks)
	{
		chunk.drawForeground(target);
	}
}

void MapChunk::drawBackground(sf::RenderTarget & target)
{
	for each (TextureChunk chunk in textureChunks)
	{
		chunk.drawBackground(target);
	}
}