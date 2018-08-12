#ifndef	TILEMAP_H
#define TILEMAP_H
#include "MapTile\MapTileFactory.hpp"
#include "MapChunk.hpp"
const int MAPCHUNK_SIZE_X = 30;
const int MAPCHUNK_SIZE_Y = 30;

class TileMap
{
public:

	bool loadTileset(std::string location)
	{
		Tileset set;
		if (set.loadFromFile(location))
		{
			tilesets.push_back(set);
			return true;
		}
		return false;
	}

	bool loadMap(TextElement & tm)
	{
		map.clear();
	
		auto size = tm.getVariableByName("Size");
		if (size != nullptr)
		{
			mapSize.y = size->toInt(1);
			mapSize.x = size->toInt(0);
		}
		else
		{
			Logger::e("Map have no size");
			return false;
		}
		Logger::i("Map size: " + std::to_string(this->mapSize.x) + " " + std::to_string(this->mapSize.y));



		std::string mainTileset = "";
		auto varTilesets = tm.getVariableByName("Tilesets");
		if (varTilesets != nullptr)
		{
			mainTileset = varTilesets->toString(0);
		}
		else mainTileset = tilesets.at(0).name;


		for (int y = 0; y < mapSize.y; y++)
		{
			auto tile = tm.getVariableByName("X" + std::to_string(y));
			if (tile == nullptr)
			{
				Logger::e("X" + std::to_string(y) + " is missing, map is not created");
				return false;
			}
			for (int x = 0; x < mapSize.x; x++)
			{
				if (mapSize.x < tile->var.size())
				{
					Logger::e("Not enough tiles in :X" + std::to_string(y) 
						+ " Found:" + std::to_string(tile->var.size()) 
						+ " Required:" + std::to_string(mapSize.x));
					return false;
				}

				appendTile(MapTileFactory::create(tile->var.at(x),sf::Vector2i(x, y),tilesets));
			}
		}

		generateBackgroundTiles();
		generateMapChunks();
		refreashMap();
		chunks[0].load();
		//refreashMap();
		return false;
	}
	void generateBackgroundTiles()
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			for (int y = 0; y < mapSize.y; y++)
			{
				auto center = getTile(x, y);
				if (center->getMainTile() == nullptr)continue;
				if (!center->getMainTile()->isShowTilesBehind())continue;

				auto left = getTile(x-1, y);
				auto right = getTile(x + 1, y);
				auto top = getTile(x, y -1);
				auto bottom = getTile(x, y+1);

				if (left != nullptr && left->getMainTile()!=nullptr)
				{
					bool shouldAddBackground = !center->getMainTile()->isConnectingToTile(left->getMainTile());
					if (shouldAddBackground)
					{
						auto copy = TileFactory::create(left->getMainTile()->getTileDefinitionPtr(),
							center->getMainTile()->getId());

						center->appendTile(copy);
					}
				}
				if (right != nullptr&& right->getMainTile() != nullptr)
				{
					bool shouldAddBackground = !center->getMainTile()->isConnectingToTile(right->getMainTile());
					if (shouldAddBackground)
					{
						auto copy = TileFactory::create(right->getMainTile()->getTileDefinitionPtr(),
							center->getMainTile()->getId());

						center->appendTile(copy);
					}
				}
				if (top != nullptr&& top->getMainTile() != nullptr)
				{
					bool shouldAddBackground = !center->getMainTile()->isConnectingToTile(top->getMainTile());
					if (shouldAddBackground)
					{
						auto copy = TileFactory::create(top->getMainTile()->getTileDefinitionPtr(),
							center->getMainTile()->getId());

						center->appendTile(copy);
					}
				}
				if (bottom != nullptr&& bottom->getMainTile() != nullptr)
				{
					bool shouldAddBackground = !center->getMainTile()->isConnectingToTile(bottom->getMainTile());
					if (shouldAddBackground)
					{
						auto copy = TileFactory::create(bottom->getMainTile()->getTileDefinitionPtr(),
							center->getMainTile()->getId());

						center->appendTile(copy);
					}
				}
			}
		}
	}
	void generateMapChunks()
	{
		chunks.clear();
		chunksCount.x = ceil(((double)mapSize.x / (double)MAPCHUNK_SIZE_X));
		chunksCount.y = ceil(((double)mapSize.y / (double)MAPCHUNK_SIZE_Y));

		for (int i = 0; i < chunksCount.x*chunksCount.y;i++)
		{
			chunks.push_back(MapChunk());
		}

		for (int x = 0; x < mapSize.x; x++)
		{
			for (int y = 0; y < mapSize.y; y++)
			{
				auto tiles = getTile(x, y)->getTiles();
				if (getTile(x, y)->getMainTile() == nullptr)continue;

				auto mapTilePos = getTile(x, y)->getMainTile()->getPosition();
				auto chunk = getChunk(mapTilePos);
				if (chunk == nullptr) throw std::exception("Failed loading map chunks");

				for each (auto tile in tiles)
				{
					chunk->appendTile(tile);
				}

			}
		}
	}

	void refreashMap()
	{
		for (int y = 0; y < mapSize.y; y++)
		{
			for (int x = 0; x < mapSize.x; x++)
			{
				refreashTile(x, y);
			}
		}
	}

	// refreash tile at selected pos
	void refreashTile(int x, int y)
	{
		auto tile = getTile(x, y);
		if (tile != nullptr)
		{
			tile->updateConnectingToTiles(getTile(x - 1, y - 1), getTile(x, y - 1), getTile(x + 1, y - 1),
				getTile(x - 1, y), getTile(x + 1, y),
				getTile(x - 1, y + 1), getTile(x, y + 1), getTile(x + 1, y + 1));
		}
	}
	// refreash near tiles, used after tile is destroyed
	void refreashNearTiles(int x, int y)
	{
		refreashTile(x - 1, y - 1); refreashTile(x, y - 1); refreashTile(x + 1, y - 1);
		refreashTile(x - 1, y); refreashTile(x + 1, y);
		refreashTile(x - 1, y + 1); refreashTile(x, y + 1); refreashTile(x + 1, y + 1);
	}


	// draw it
	void draw(sf::RenderTarget &window)
	{
		if (chunks.size() != 0)
			chunks[0].drawForeground(window);
	}
	// draw background tiles
	void drawBackground(sf::RenderTarget &window)
	{
		if (chunks.size() != 0)
			chunks[0].drawBackground(window);
	}

	MapTile * getTile(int x, int y)
	{
		if (map.size() <= x + y * mapSize.x)return nullptr;
		if (x<0 || y<0 || x >= mapSize.x || y >= mapSize.y)return nullptr;
		return &map.at(x + y * mapSize.x);
	}

	MapChunk * getChunk(sf::Vector2f position)
	{
		int x = (position.x / TILE_SIZE)/ MAPCHUNK_SIZE_X;
		int y = (position.y / TILE_SIZE)/ MAPCHUNK_SIZE_Y;
		return getChunk(x, y);
	}

	MapChunk * getChunk(int x, int y)
	{
		if (chunks.size() <= x + y * chunksCount.x)return nullptr;
		if (x<0 || y<0 || x >= chunksCount.x || y >= chunksCount.y)return nullptr;
		return &chunks.at(x + y * chunksCount.x);
	}

private:
	void appendTile(MapTile tile)
	{
		map.push_back(tile);
	}
	std::vector<MapChunk> chunks;
	sf::Vector2i chunksCount;

	std::vector<MapTile> map;
	sf::Vector2i mapSize;

	std::vector<Tileset> tilesets;

};

#endif