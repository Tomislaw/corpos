#ifndef GAMEASSETSMANAGER_HPP
#define GAMEASSETSMANAGER_HPP

#include <SFML\Graphics.hpp>
#include "game\engine\Entity.hpp"
#include "game\utility\TextFileData.hpp"
class GameSprite;

class GameAssetsManager
{
public:
	std::map<std::string, GameSprite> gameSprites;
	std::map<std::string, sf::Texture > textures;
	std::map<std::string, sf::Font> fonts;

	static GameAssetsManager * getInstance();
	~GameAssetsManager();
	static void loadTextures(std::string location);
	static void loadSprites(std::string location);

	static sf::Texture * getTexture(std::string texture);
	static GameSprite * getSprite(std::string sprite);


private:
	GameAssetsManager();
	GameAssetsManager(const GameAssetsManager &);
	static GameAssetsManager* instance;

	void loadDefaultResources();
};

#endif