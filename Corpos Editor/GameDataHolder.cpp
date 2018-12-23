#include "GameDataHolder.h"
#include "options.h"

GameDataHolder* GameDataHolder::instance = nullptr;
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
	//delete texture_names;
}

void GameDataHolder::loadTextures()
{
	std::string location = Options::textureLocation;

	TextFileData file;
	file.loadFile(location);
	auto textures_list = file.getAllElementsByName("TEXTURE");

	Logger::i("Found " + std::to_string(textures_list.size()) + " textures");

	texture = new sf::Texture[textures_list.size()];
	for (int i = 0; i < textures_list.size(); i++)
	{
		//Logger::i("Loading " + textures_list[i]->getVariableByName("Location")->var[0]);
		texture[i].loadFromFile(textures_list[i]->getVariableByName("Location")->var[0]);
		texture[i].setSmooth(0);
		texture_names.push_back((textures_list[i]->getVariableByName("Name")->var[0]));
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
	for (int i = 0; i < textureArraySize; i++)
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

std::vector<std::string>& GameDataHolder::getTextureList()
{
	return texture_names;
}

void GameDataHolder::loadSprites()
{
	TextFileData file; //Loading sprites
	file.loadFile(Options::spriteLocation);
	auto entities = file.getAllElementsByName("ENTITY_DEFIINITION");
	Logger::i("Found " + std::to_string(entities.size()) + " game sprites");
	for (int i = 0; i < entities.size(); i++)
	{
		std::string s = entities.at(i)->getVariableByName("Texture")->var[0];
		std::string n = entities.at(i)->getVariableByName("Name")->var[0];
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