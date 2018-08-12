#ifndef	MAPTILE_HPP
#define MAPTILE_HPP
#include "src\game\map\AbstractTile.hpp"
class MapTile
{
private:
	std::vector<std::shared_ptr<AbstractTile >> tiles;

	static bool shouldConnectToTile(std::shared_ptr<AbstractTile> tile, MapTile * mapTile)
	{
		if (mapTile == nullptr)return false;
		for each (auto var in mapTile->getTiles())
		{
			if (tile->isConnectingToTile(var))return true;
		}
		return false;
	}
public:
	void appendTile(std::shared_ptr<AbstractTile> tile)
	{
		tiles.push_back(tile);
	}
	std::shared_ptr<AbstractTile > getMainTile()
	{
		if (tiles.size() == 0)return nullptr;
		return tiles.front();
	}

	std::vector<std::shared_ptr<AbstractTile >> & getTiles()
	{
		return tiles;
	}

	void updateConnectingToTiles(
		MapTile * LT, MapTile * T, MapTile * RT,
		MapTile * L,			   MapTile * R,
		MapTile * LB, MapTile  * B, MapTile * RB
		)
	{
		for each (auto tile in tiles)
		{
			tile->updateTextureCoords(shouldConnectToTile(tile,LT),
				shouldConnectToTile(tile, T),
				shouldConnectToTile(tile, RT),
				shouldConnectToTile(tile, L),
				shouldConnectToTile(tile, R),
				shouldConnectToTile(tile, LB),
				shouldConnectToTile(tile, B),
				shouldConnectToTile(tile, RB));
		}
	}


};


#endif