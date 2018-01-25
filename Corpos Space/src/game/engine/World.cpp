#include "World.hpp"
std::string * World::texture_names = nullptr;
sf::Texture * World::texture = nullptr;
int World::textureArraySize = 0;

World::World()
{
	this->entitylist.setTilemapPtr(&tilemap);

	//Set getTexture function for world map
	this->tilemap.getFunctionGetTexture() = std::bind(&World::getTexture, std::placeholders::_1);
}


World::~World()
{

}

bool World::loadTextures(std::string location)
{

	Logger::i("Loading texture definitions in " + location);

	TextFileData file;
	file.loadFile(location);

	auto textures_list = file.getAllElementsByName("TEXTURE");

	Logger::i("Found " + std::to_string(textures_list.size()) + " textures");

	texture = new sf::Texture[textures_list.size()];
	texture_names = new std::string[textures_list.size()];
	for (int i = 0; i < textures_list.size(); i++)
	{
		// Get location of texture
		auto varLocation = textures_list[i]->getVariableByName("Location");
		if (varLocation == nullptr)
		{
			Logger::e("Texture definition " + std::to_string(i) + " in " + location + " is invalid!");
			continue;
		}


		// get name of texture
		auto varName = textures_list[i]->getVariableByName("Name");
		if (varName == nullptr)
		{
			Logger::e("Texture definition " + std::to_string(i) + " in " + location + " missing name!");
			texture_names[i] = "Missing name texture";
		}
		else texture_names[i]=varName->toString(0);

		Logger::i("Loading " + varLocation->toString(0));
		auto loaded = texture[i].loadFromFile(varLocation->toString(0));
		if (loaded)
			texture[i].setSmooth(0);
		else
		{
			Logger::e("Can't load " + location);
		}
	}
	textureArraySize = textures_list.size();

	
	return true;

}

bool World::loadEntitylist(std::string location)
{
	entitylist.loadSpriteDefinition(location);

	loadMap("bin/map/mm.txt");

	return true;
}

sf::Texture* World::getTexture(std::string name)
{
	for (int i = 0; i < textureArraySize;i++)
	{
		if (texture_names[i] == name) return &texture[i];
	}
	return nullptr;
}

void World::update(float delta)
{
	entitylist.update(delta);
}

void World::draw(sf::RenderWindow & window)
{
	entitylist.getCurrentCamera().setBackgroundView(window);
	window.draw(background);

	entitylist.getCurrentCamera().setNormalView(window);
	tilemap.drawBackground(window);
	tilemap.draw(window);
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
	tilemap.loadTileset("bin/graphics/tileset/tileset1.txt");
	tilemap.loadMap(tm);
	//load it after tilemap
	entitylist.loadMap(file);

	auto tex = getTexture("background1");
	background.setTexture(*tex);
}
