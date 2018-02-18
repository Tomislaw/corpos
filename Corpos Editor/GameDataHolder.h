
#ifndef GAMEDATAHOLDER_H
#define GAMEDATAHOLDER_H

#include <iostream>
#include <memory>
#include <vector>
#include "game\graphics\GameSprite.hpp"
#include "game\utility\TextFileData.hpp"
class GameDataHolder
{
private:
	GameDataHolder();
	GameDataHolder(const GameDataHolder &);
	static GameDataHolder* instance;
public:
	static GameDataHolder * GameDataHolder::getInstance();
	~GameDataHolder();
	void loadTextures();
	void loadSprites();
	sf::Texture * getTexture(std::string texture);
	std::vector <GameSprite> * getSpriteList();
	std::vector <std::string> & getTextureList();

private:
	std::vector <GameSprite> game_sprite_definitions;
	std::vector <std::string> texture_names;
	sf::Texture *texture;
	int textureArraySize;
};

#endif