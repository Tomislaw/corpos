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
			tileCount.y = size->toInt(1);
			tileCount.x = size->toInt(0);
		}
		else
		{
			Logger::e("Map have no size");
			return false;
		}
		Logger::i("Map size: " + std::to_string(this->tileCount.x) + " " + std::to_string(this->tileCount.y));



		std::string mainTileset = "";
		auto varTilesets = tm.getVariableByName("Tilesets");
		if (varTilesets != nullptr)
		{
			mainTileset = varTilesets->toString(0);
		}
		else mainTileset = tilesets.at(0).name;


		for (int y = 0; y < tileCount.y; y++)
		{
			auto tile = tm.getVariableByName("X" + std::to_string(y));
			if (tile == nullptr)
			{
				Logger::e("X" + std::to_string(y) + " is missing, map is not created");
				return false;
			}
			for (int x = 0; x < tileCount.x; x++)
			{
				if (tileCount.x < tile->var.size())
				{
					Logger::e("Not enough tiles in :X" + std::to_string(y)
						+ " Found:" + std::to_string(tile->var.size())
						+ " Required:" + std::to_string(tileCount.x));
					return false;
				}

	
				appendTile(MapTileFactory::create(tile->var.at(x), sf::Vector2i(x, y), tilesets));
			}
		}

		//refreashMap();
		generateBackgroundTiles();
		generateMapChunks();
		refreashMap();

		for (size_t i = 0; i < chunks.size(); i++)
		{
			chunks[i].load();
		}

		//refreashMap();
		return false;
	}
	void generateBackgroundTiles()
	{
		for (int x = 0; x < tileCount.x; x++)
		{
			for (int y = 0; y < tileCount.y; y++)
			{
				generateBackgroundTile(x, y);
			}
		}
	}

	void generateBackgroundTile(int x, int y)
	{
		auto center = getTile(x, y);
		if (center->getMainTile() == nullptr)return;

		auto bg = TileFactory::create(center->getMainTile()->getBackgroundTileDefinition(),
			center->getMainTile()->getId());
		center->appendTile(bg);

		auto maybeAppendTile = [](MapTile * center, MapTile * tile)
		{
			if (tile == nullptr)return;
			if (tile->getMainTile() == nullptr)return;

			bool shouldAddForeground = !center->getMainTile()->isConnectingToTile(tile->getMainTile());
			if (shouldAddForeground)
			{
				auto copy = TileFactory::create(tile->getMainTile()->getTileDefinitionPtr(),
					center->getMainTile()->getId());

				center->appendTile(copy);

				bool shouldAddBackground = !center->getMainTile()->getBackgroundTileDefinition().expired();
				if (shouldAddBackground)
				{
					auto copy = TileFactory::create(tile->getMainTile()->getBackgroundTileDefinition(),
						center->getMainTile()->getId());
					center->appendTile(copy);
				}

			}


		};

	

		auto left = getTile(x - 1, y);
		auto right = getTile(x + 1, y);
		auto top = getTile(x, y - 1);
		auto bottom = getTile(x, y + 1);

		maybeAppendTile(center, left);
		maybeAppendTile(center, right);
		maybeAppendTile(center, top);
		maybeAppendTile(center, bottom);



		//if (left != nullptr && left->getMainTile() != nullptr)
		//{
		//	bool shouldAddBackground = !center->getMainTile()->isConnectingToTile(left->getMainTile());
		//	if (shouldAddBackground)
		//	{
		//		auto copy = TileFactory::create(left->getMainTile()->getTileDefinitionPtr(),
		//			center->getMainTile()->getId());

		//		center->appendTile(copy);
		//	}
		//}


		/*if (right != nullptr&& right->getMainTile() != nullptr)
		{

			bool shouldAddBackground = !center->getMainTile()->isConnectingToTile(right->getMainTile());

			if (shouldAddBackground)
			{
				auto copy = TileFactory::create(right->getMainTile()->getTileDefinitionPtr(),
					center->getMainTile()->getId());

				center->appendTile(copy);
			}
		}*/


		//if (top != nullptr&& top->getMainTile() != nullptr)
		//{
		//	bool shouldAddBackground = !center->getMainTile()->isConnectingToTile(top->getMainTile());
		//	if (shouldAddBackground)
		//	{
		//		auto copy = TileFactory::create(top->getMainTile()->getTileDefinitionPtr(),
		//			center->getMainTile()->getId());

		//		center->appendTile(copy);
		//	}
		//}


		//if (bottom != nullptr && bottom->getMainTile() != nullptr)
		//{
		//	bool shouldAddBackground = !center->getMainTile()->isConnectingToTile(bottom->getMainTile());

		//	if (shouldAddBackground)
		//	{
		//		auto copy = TileFactory::create(bottom->getMainTile()->getTileDefinitionPtr(),
		//			center->getMainTile()->getId());

		//		center->appendTile(copy);
		//	}
		//}
	}

	void generateMapChunks()
	{
		chunks.clear();
		chunksCount.x = ceil(((double)tileCount.x / (double)MAPCHUNK_SIZE_X));
		chunksCount.y = ceil(((double)tileCount.y / (double)MAPCHUNK_SIZE_Y));

		for (int i = 0; i < chunksCount.x*chunksCount.y; i++)
		{
			chunks.push_back(MapChunk());
		}

		for (int x = 0; x < tileCount.x; x++)
		{
			for (int y = 0; y < tileCount.y; y++)
			{

				if (getTile(x, y)->getMainTile() == nullptr)continue;

				auto mapTilePos = getTile(x, y)->getMainTile()->getPosition();
				auto chunk = getChunk(mapTilePos);
				if (chunk == nullptr) throw std::exception("Failed loading map chunks");

				auto tiles = getTile(x, y)->getTiles();

				for each (auto tile in tiles)
				{
					chunk->appendTile(tile);
				}
				chunk->appendTile(getTile(x, y)->getMainTile());
			}
		}
	}

	void refreashMap()
	{
		for (int y = 0; y < tileCount.y; y++)
		{
			for (int x = 0; x < tileCount.x; x++)
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
		{
			for (size_t i = 0; i < chunks.size(); i++)
			{
				chunks[i].drawForeground(window);
			}

		}
	}

	// draw background tiles
	void drawBackground(sf::RenderTarget &window)
	{
		if (chunks.size() != 0)
		{
			for (size_t i = 0; i < chunks.size(); i++)
			{
				chunks[i].drawBackground(window);
			}
		}
	}

	bool isTileBlocking(int x, int y)
	{
		auto tile = getTile(x, y);
		if (tile == nullptr)return false;
		if (tile->getMainTile() == nullptr)return false;
		return tile->getMainTile()->isBlocking();
	}

	MapTile * getTile(sf::Vector2i id)
	{
		return getTile(id.x, id.y);
	}

	MapTile * getTile(int x, int y)
	{
		if (map.size() <= x + y * tileCount.x)return nullptr;
		if (x < 0 || y < 0 || x >= tileCount.x || y >= tileCount.y)return nullptr;
		return &map.at(x + y * tileCount.x);
	}

	void destroyTile(int x, int y)
	{
		auto tile = getTile(x,y);
		if (tile == nullptr) return;

		tile->onMainTileDestroy();
	
		refreashTile(x,y);
		refreashNearTiles(x, y);
	}

	std::vector<MapTile*> getTilesFromLine(sf::Vector2f start, sf::Vector2f end)
	{

		std::vector<sf::Vector2i> tile_ids;

		auto tileStart = this->getTileId(start);
		auto tileEnd = this->getTileId(end);

		//make sure if we re npt adding additional tiles - -2,0 etc
		if (end.x < 0) tileStart.x = -1;
		if (end.y < 0) tileEnd.y = -1;

		//return one tile if started out of map
		if (tileStart == tileEnd || tileStart.x < 0 || tileStart.y < 0)
		{
			tile_ids.push_back(tileStart);

			//return tile_ids;
		}

		// Creating line to get tiles from
		float divide = end.x - start.x;
		float a = (end.y - start.y) / divide;
		float b = end.y - a*end.x;
		// change to infinity if dividing by zero
		if (!(divide>0.0000001 || divide<-0.0000001)) { a = INFINITY; }

		// start x and y counters
		int x_count = abs(tileStart.x - tileEnd.x);
		int y_count = abs(tileStart.y - tileEnd.y);


		// set adding or decrementing
		int operation_x = 1;
		int operation_y = 1;

		if (start.x > end.x)
		{
			operation_x = -1;
		}
		if (start.y > end.y)
		{
			operation_y = -1;
		}

		// ad start tile
		tile_ids.push_back(tileStart);
		// check if have to increment y or x more often
		if (a<1 && a>-1)
		{
			int current_x = tileStart.x;

			for (int i = 0; i < x_count; i++)
			{

				float value_x = current_x * TILE_SIZE + operation_x / 10.f + TILE_SIZE / 2 * (1 + operation_x);
				sf::Vector2f function_pos_x = sf::Vector2f(value_x, a*(value_x)+b);
				sf::Vector2i id_x = getTileId(function_pos_x);

				if (id_x.x != tile_ids.back().x && id_x.y != tile_ids.back().y)
				{
					float value_y = tile_ids.back().y * TILE_SIZE + TILE_SIZE / 2 * (1 + operation_y) + operation_y / 10.f;
					sf::Vector2f function_pos_y((sf::Vector2f((value_y - b) / a, value_y)));
					sf::Vector2i id_y(getTileId(function_pos_y));

					if (id_y != tile_ids.back())tile_ids.push_back(id_y);
					if (id_y.x < 0) break;
				}


				if (id_x != tile_ids.back())tile_ids.push_back(id_x);
				if (id_x.x < 0) break;
				current_x += operation_x;
			}
			sf::Vector2i id_last(getTileId(end));
			if (id_last != tile_ids.back())
			{
				if (id_last.x != tile_ids.back().x && id_last.y != tile_ids.back().y)
				{
					float value_y = tile_ids.back().y * TILE_SIZE + TILE_SIZE / 2 * (1 + operation_y) + operation_y / 10.f;
					sf::Vector2f function_pos_y((sf::Vector2f((value_y - b) / a, value_y)));
					sf::Vector2i id_y(getTileId(function_pos_y));

					if (id_y != tile_ids.back())tile_ids.push_back(id_y);

				}

				if (id_last != tile_ids.back())tile_ids.push_back(id_last);
			}
		}
		else
		{
			if (a != INFINITY)
			{
				int current_x = tileStart.x;
				int current_y = tileStart.y;


				for (int i = 0; i < y_count; i++)
				{

					float value_y = tile_ids.back().y * TILE_SIZE + TILE_SIZE / 2 * (1 + operation_y) + operation_y / 10.f;

					sf::Vector2f function_pos_y((sf::Vector2f((value_y - b) / a, value_y)));
					sf::Vector2i id_y(getTileId(function_pos_y));


					if (id_y.x != tile_ids.back().x && id_y.y != tile_ids.back().y)
					{
						float value_x = current_x * TILE_SIZE + operation_x / 10.f + TILE_SIZE / 2 * (1 + operation_x);
						sf::Vector2f function_pos_x = sf::Vector2f(value_x, a*value_x + b);
						sf::Vector2i id_x(getTileId(function_pos_x));
						if (id_x != tile_ids.back())tile_ids.push_back(id_x);
						if (id_x.x < 0)break;

						current_x += operation_x;

					}

					if (id_y != tile_ids.back())tile_ids.push_back(id_y);
					if (id_y.x < 0)break;
					current_y += operation_y;
				}
			}
			else
			{
				for (int i = 0; i < y_count; i++)
				{
					sf::Vector2i startvector = getTileId(start + sf::Vector2f(0, (i + 1)*TILE_SIZE));
					tile_ids.push_back(startvector);
					if (startvector.y < 0) break;
				}
			}


		}

		std::vector<MapTile*> tiles;
		for each (sf::Vector2i var in tile_ids)
		{
			tiles.push_back(getTile(var.x,var.y));
		}
		return tiles;
	}

	MapChunk * getChunk(sf::Vector2f position)
	{
		int x = (position.x / TILE_SIZE) / MAPCHUNK_SIZE_X;
		int y = (position.y / TILE_SIZE) / MAPCHUNK_SIZE_Y;
		return getChunk(x, y);
	}

	MapChunk * getChunk(int x, int y)
	{
		if (chunks.size() <= x + y * chunksCount.x)return nullptr;
		if (x < 0 || y < 0 || x >= chunksCount.x || y >= chunksCount.y)return nullptr;
		return &chunks.at(x + y * chunksCount.x);
	}

	sf::Vector2i getTileId(float x, float y)
	{
		int _x = x / TILE_SIZE;
		int _y = y / TILE_SIZE;
		return sf::Vector2i(_x, _y);
	}

	sf::Vector2i getTileId(sf::Vector2f position)
	{
		int x = position.x / TILE_SIZE;
		int y = position.y / TILE_SIZE;
		return sf::Vector2i(x, y);
	}

	sf::Vector2i getTileCount() { return tileCount; }
	sf::Vector2f getMapSize() { return sf::Vector2f(tileCount.x *TILE_SIZE, tileCount.y * TILE_SIZE); }


private:
	void appendTile(MapTile tile)
	{
		map.push_back(tile);
	}
	std::vector<MapChunk> chunks;
	sf::Vector2i chunksCount;

	std::vector<MapTile> map;
	sf::Vector2i tileCount;

	std::vector<Tileset> tilesets;

};

#endif