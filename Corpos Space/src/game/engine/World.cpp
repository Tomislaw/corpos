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
		Logger::i("Loading " + textures_list[i]->getVariableByName("Location")->var[0]);
		texture[i].loadFromFile(textures_list[i]->getVariableByName("Location")->var[0]);
		texture[i].setSmooth(0);
		texture_names[i]=(textures_list[i]->getVariableByName("Name")->var[0]);
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
	window.draw(background);
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

	tilemap.loadTileset("bin/graphics/tileset/tileset1.txt");
	tilemap.loadMap(tm);

	auto map_props = file.getAllElementsByName("PROP");
	for (int i = 0; i < map_props.size();i++)
	{
		auto p = std::shared_ptr<Prop>(new  Prop(map_props.at(i)));
		entitylist.addProp(p);
	}

	auto map_characters = file.getAllElementsByName("CHARACTER");
	for (int i = 0; i < map_characters.size();i++)
	{
		auto p = CharacterCreator::create(map_characters.at(i), &tilemap);
		entitylist.addCharacter(p);
	}


	entitylist.setPlayerEntity("@player");

	auto tex = getTexture("background1");
	background.setTexture(*tex);
}
