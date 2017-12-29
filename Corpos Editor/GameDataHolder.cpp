#include "GameDataHolder.h"
#include "options.h"

GameDataHolder* GameDataHolder::instance= nullptr;
GameDataHolder::GameDataHolder()
{
}



GameDataHolder * GameDataHolder::getInstance()
{
	if (instance == 0)
	{
		instance = new GameDataHolder();
	}

	return instance;
}

GameDataHolder::~GameDataHolder()
{
	delete texture;
	delete texture_names;
}

void GameDataHolder::loadTextures()
{
	std::string location = Options::textureLocation;
	

	TextFileData file;
	file.load_file(location);
	auto textures_list = file.get_all_elements_by_name("TEXTURE");

	Logger::i("Found " + std::to_string(textures_list.size()) + " textures");

	texture = new sf::Texture[textures_list.size()];
	texture_names = new std::string[textures_list.size()];
	for (int i = 0; i < textures_list.size(); i++)
	{
		//Logger::i("Loading " + textures_list[i]->get_variable_by_name("Location")->var[0]);
		texture[i].loadFromFile(textures_list[i]->get_variable_by_name("Location")->var[0]);
		texture[i].setSmooth(0);
		texture_names[i] = (textures_list[i]->get_variable_by_name("Name")->var[0]);
	}
	textureArraySize = textures_list.size();


}

sf::Texture * GameDataHolder::getTexture(std::string texture)
{
	if (textureArraySize == 0)
	{
		Logger::e("Can't find any texture");
		return nullptr;
	}
	for (int i = 0; i < textureArraySize;i++)
	{
		if (texture_names[i] == texture)return &this->texture[i];
	}
	//Logger::e("Texture with name \"" + texture + "\" not found. Returning first texture in array.");
	//return &this->texture[0];
	return nullptr;
}

std::vector<GameSprite>* GameDataHolder::getSpriteList()
{
	return &game_sprite_definitions;
}

void GameDataHolder::loadSprites()
{
	TextFileData file; //Loading sprites
	file.load_file(Options::spriteLocation);
	auto entities = file.get_all_elements_by_name("ENTITY_DEFIINITION");
	Logger::i("Found " + std::to_string(entities.size()) + " game sprites");
	for (int i = 0; i < entities.size(); i++)
	{
		std::string s = entities.at(i)->get_variable_by_name("Texture")->var[0];
		std::string n = entities.at(i)->get_variable_by_name("Name")->var[0];
		sf::Texture * t = getTexture(s);
		if (t == nullptr)
		{
			Logger::e("Texture \"" + s + "\" not found! Sprite \"" + n + "\" not created!");
			continue;
		}
		GameSprite sprite(*t, entities.at(i));
		game_sprite_definitions.push_back(sprite);
	}
}
