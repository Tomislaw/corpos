#include "World.hpp"

using namespace corpos;

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
	AStar::PathfindUtils::getTile = std::bind(getTile, std::placeholders::_1, std::placeholders::_2);

	entitylist.actions().inputs.addInput("reloadMap", [&](Action action) {
		shouldReload = false;
		//reloadMap();
		shouldReload = true;
	});
}

World::~World()
{
}

void World::update(float delta)
{
	if (shouldReload) {
		reloadMap();
		shouldReload = false;
	}
	else entitylist.update(delta);
}

void World::draw(sf::RenderWindow & window)
{
	window.setMouseCursorVisible(false);
	entitylist.getCurrentCamera().setView(window);

	entitylist.drawBackground(window);
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
	//jsonMap = json_utils::from_file(map);

	mapFile.loadFile(map);
	reloadMap();
}

void World::reloadMap()
{
	auto tm = mapFile.getFirstElementByName("TILEMAP");

	tilemap2.loadTileset("bin/graphics/tileset/tileset1.txt");

	//auto succesfullyLoaded = tilemap2.loadMap(jsonMap);
	//if (!succesfullyLoaded)
	//	return Logger::e("Failed to load tilemap.");

	//succesfullyLoaded = entitylist.loadMap(jsonMap);
	//if (!succesfullyLoaded)
	//	return Logger::e("Failed to load entityList.");
	tilemap2.loadMap(*tm);

	//load it after tilemap
	entitylist.loadMap(mapFile);
}