#pragma once

#include "MapTile.hpp"
#include "game\map\TileFactory.hpp"
#include "game\utility\String.hpp"
#include "game\map\TileSet.hpp"

namespace corpos
{
	class MapTileFactory
	{
	public:
		static MapTile create(std::string & variable, sf::Vector2i & position, std::vector<Tileset> & definitions)
		{
			if (variable.size() == 0 || variable == "0" || definitions.size() == 0)
				return MapTile();

			std::size_t found = variable.find('//');

			MapTile tile;
			if (found != std::string::npos) {
				auto tilesStr = String::split(variable, '//');
				for each (auto tileStr in tilesStr)
					appendTile(tileStr, position, definitions, tile);
			}
			else {
				appendTile(variable, position, definitions, tile);
			}
			return tile;
		}
	private:

		static void appendTile(std::string & variable, sf::Vector2i & position, std::vector<Tileset> & definitions, MapTile & tile)
		{
			//if not using main tileset
			// {tileset_name}.{tile_name}
			std::size_t found = variable.find('.');
			if (found != std::string::npos)
			{
				auto tileStr = String::split(variable, '.');
				if (tileStr.size() != 2)
				{
					Logger::e("Invalid tile: " + variable);
					return;
				}

				for (int i = 0; i < definitions.size(); i++)
				{
					if (definitions[i].name == tileStr[0])
					{
						auto def = definitions[i].getTileDefinition(tileStr[1]);
						if (def != nullptr)
						{
							tile.appendTile(TileFactory::create(def, position));
						}
						return;
					}
				}
			}		//if using main tileset
			else    //{tile_name}
			{
				auto def = definitions.front().getTileDefinition(variable);
				if (def != nullptr)
				{
					tile.appendTile(TileFactory::create(def, position));
				}
				return;
			}
		}

		MapTileFactory() {};
	};
}