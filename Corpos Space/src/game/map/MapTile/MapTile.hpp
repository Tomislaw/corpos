#ifndef	MAPTILE_HPP
#define MAPTILE_HPP
#include "src\game\map\AbstractTile.hpp"
class MapTile
{
private:
	std::vector<std::shared_ptr<AbstractTile >> tiles;

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
};


#endif