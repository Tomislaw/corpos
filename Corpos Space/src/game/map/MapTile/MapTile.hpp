#ifndef	MAPTILE_HPP
#define MAPTILE_HPP
#include "src\game\map\AbstractTile.hpp"
class MapTile
{

public:

	MapTile() {}

	MapTile(std::shared_ptr<AbstractTile> tile) { mainTile = tile; }

	void appendTile(std::shared_ptr<AbstractTile> tile)
	{
		if (tile == nullptr)return;

		if (mainTile == nullptr)
		{
			mainTile = tile;
			return;
		}

		if (tile->getId() != mainTile->getId()) return;

		if (mainTile->isBackground() && !tile->isBackground()) return;

		tiles.push_back(tile);
	}

	std::shared_ptr<AbstractTile > getMainTile()
	{
		return mainTile;
	}

	std::vector<std::shared_ptr<AbstractTile >> & getTiles()
	{
		return tiles;
	}

	void updateConnectingToTiles(
		MapTile * LT, MapTile * T, MapTile * RT,
		MapTile * L, MapTile * R,
		MapTile * LB, MapTile  * B, MapTile * RB
	)
	{
		if (mainTile != nullptr)
		{
			mainTile->updateTextureCoords(shouldConnectToTile(mainTile, LT),
				shouldConnectToTile(mainTile, T),
				shouldConnectToTile(mainTile, RT),
				shouldConnectToTile(mainTile, L),
				shouldConnectToTile(mainTile, R),
				shouldConnectToTile(mainTile, LB),
				shouldConnectToTile(mainTile, B),
				shouldConnectToTile(mainTile, RB));
		}

		for each (auto tile in tiles)
		{
			tile->updateTextureCoords(shouldConnectToTile(tile, LT),
				shouldConnectToTile(tile, T),
				shouldConnectToTile(tile, RT),
				shouldConnectToTile(tile, L),
				shouldConnectToTile(tile, R),
				shouldConnectToTile(tile, LB),
				shouldConnectToTile(tile, B),
				shouldConnectToTile(tile, RB));
		}
	}

	void onMainTileDestroy()
	{
		if (mainTile == nullptr)return;

		mainTile->destroy();

		bool destroyOnlyForeground = !mainTile->isBackground();

		for each (auto tile in tiles)
		{
			if(destroyOnlyForeground && !tile->isBackground())
				tile->destroy();
		}
		
	}

	void clearBackgroundTiles()
	{
		for each (auto tile in tiles)
		{
			tile->destroy();
		}
		tiles.clear();
	}

	std::string toString()
	{
		std::string str = "mainTile: ";
		if (mainTile == nullptr) str += "nullptr \n";
		else {
			str += "{\n" + mainTile->toString() + "\n}";
		}
		if (tiles.size() == 0) return str;
		else
		{
			str += "\nbgTiles:";
			for each (auto tile in tiles)
			{
				str += "\ntile: ";
				if (tile == nullptr)str += nullptr;
				else str += tile->toString();
			}
		}
	}

	bool isBlocking()
	{
		if (mainTile == nullptr) return false;
		else return mainTile->isBlocking();
	}

private:
	std::shared_ptr<AbstractTile> mainTile;

	std::vector<std::shared_ptr<AbstractTile>> tiles;

	static bool shouldConnectToTile(std::shared_ptr<AbstractTile> tile, MapTile * mapTile)
	{
		if (mapTile == nullptr || tile == nullptr)return false;
	

		if (tile->isConnectingToTile(mapTile->getMainTile())) return true;

		for each (auto var in mapTile->getTiles())
		{
			if (tile->isConnectingToTile(var))return true;
		}
		return false;
	}

};


#endif