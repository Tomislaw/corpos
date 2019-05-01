#include <SFML\Graphics.hpp>
#include "AbstractTile.hpp"
#include <set>
#ifndef	MAP_CHUNK_HPP
#define MAP_CHUNK_HPP

namespace corpos
{
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
		std::shared_ptr<sf::VertexArray> foreground;
		//background
		std::shared_ptr<sf::VertexArray> background;

		std::string textureName;
		const sf::Texture* texture;

		//set drawing order
		struct CustomComparator {
			bool operator() (const std::shared_ptr<AbstractTile > &a, const std::shared_ptr<AbstractTile > &b)
			{
				return *a.get() < *b.get();
			};
		};
		std::multiset<std::shared_ptr<AbstractTile >, CustomComparator> tiles;
		//std::vector<std::shared_ptr<AbstractTile >> tiles;
	};

	class MapChunk
	{
	public:
		MapChunk() {};

		void appendTile(std::shared_ptr<AbstractTile> tile);

		void load();

		void unload();

		void clearTiles();

		void drawForeground(sf::RenderTarget& target);
		void drawBackground(sf::RenderTarget& target);

	private:
		std::vector<TextureChunk> textureChunks;
	};
}

#endif