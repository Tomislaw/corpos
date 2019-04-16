#ifndef	WORLD_HPP
#define WORLD_HPP

#include <SFML\Graphics.hpp>
#include "game\utility\Logger.hpp"
#include "game\utility\TextFileData.hpp"
#include "game\engine\EntityList.hpp"
#include "game\map\Tilemap.hpp"
#include "game\map\Tilemap.h"
#include "game\utility\Pathfind.hpp"
#include <functional>
#include "game\graphics\GameAssetsManager.hpp"
//One of the main classes that contains EntityList(enitity container) and tilemap.
//
class World
{
public:

	EntityList entitylist;
	//Tilemap tilemap;
	TileMap tilemap2;

	World();
	~World();

	// update map
	void update(float delta);
	// draw it
	void draw(sf::RenderWindow & window);

	// resolve keyboard/mouse events
	void events(sf::Event e);
	// load map
	void loadMap(std::string map);
	void reloadMap();


protected:
	TextFileData mapFile;
	bool shouldReload = false;
};

#endif