#include "World.hpp"

World::World()
{
	//entitylist.setTilemapPtr(&tilemap);
	entitylist.setTileMapPtr(&tilemap2);
	//Set getTexture function for world map
	//tilemap.getFunctionGetTexture() = std::bind(&GameAssetsManager::getTexture, std::placeholders::_1);


	auto getTile = [&](int x, int y)
	{ 
		return tilemap2.getTile(x, y);
	};
	AStar::PathFind::getTile = std::bind(getTile,std::placeholders::_1, std::placeholders::_2);
}


World::~World()
{

}



void World::update(float delta)
{
	entitylist.update(delta);
}

void World::draw(sf::RenderWindow & window)
{
	entitylist.getCurrentCamera().setForegroundView(window);
	//entitylist.getCurrentCamera().setBackgroundView(window);
	window.draw(background);

	//entitylist.getCurrentCamera().setNormalView(window);
	//tilemap.drawBackground(window);
	//tilemap.draw(window);
	
	
	tilemap2.drawBackground(window);
	
	tilemap2.draw(window);
	entitylist.draw(window);
}


void World::events(sf::Event e)
{
	entitylist.events(e);
}

void World::loadMap(std::string map)
{
	TextFileData file;
	file.loadFile(map);
	auto tm = file.getFirstElementByName("TILEMAP");

	//its important to load tilemap first
	//tilemap.loadTileset("bin/graphics/tileset/tileset1.txt");
	//tilemap.loadMap(tm);

	tilemap2.loadTileset("bin/graphics/tileset/tileset1.txt");
	tilemap2.loadMap(*tm);

	//load it after tilemap
	entitylist.loadMap(file);

	auto tex = GameAssetsManager::getTexture("background1");
	background.setTexture(*tex);
}
