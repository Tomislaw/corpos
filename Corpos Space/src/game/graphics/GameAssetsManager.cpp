#include "GameAssetsManager.hpp"
#include "GAMESPRITE.hpp"

GameAssetsManager* GameAssetsManager::instance = nullptr;

GameAssetsManager::GameAssetsManager()
{
	loadDefaultResources();
}


GameAssetsManager * GameAssetsManager::getInstance()
{
	if (instance == 0)
	{
		instance = new GameAssetsManager();
	}

	return instance;
}

GameAssetsManager::~GameAssetsManager()
{
}

void GameAssetsManager::loadTextures(std::string location)
{
	Logger::i("Loading texture definitions in " + location);

	TextFileData file;
	file.loadFile(location);

	auto textures_list = file.getAllElementsByName("TEXTURE");

	Logger::i("Found " + std::to_string(textures_list.size()) + " textures");


	for (int i = 0; i < textures_list.size(); i++)
	{
		// Get location of texture
		auto varLocation = textures_list[i]->getVariableByName("Location");
		if (varLocation == nullptr)
		{
			Logger::e("Texture definition " + std::to_string(i) + " in " + location + " missing path!");
			continue;
		}


		// get name of texture
		auto varName = textures_list[i]->getVariableByName("Name");
		if (varName == nullptr)
		{
			Logger::e("Texture definition " + std::to_string(i) + " in " + location + " missing name!");
			continue;
		}

		Logger::i("Loading " + varLocation->toString(0));
		sf::Texture texture;
		if (!texture.loadFromFile(varLocation->toString(0)))
		{
			Logger::e("Failed loading texture  " + varName->toString(0) + " in " + varLocation->toString(0));
			continue;
		}

		texture.setSmooth(false);
		getInstance()->textures.insert_or_assign(varName->toString(0), texture);
	}



	return ;
}

void GameAssetsManager::loadSprites(std::string location)
{
	TextFileData file; //Loading sprites
	file.loadFile(location);
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
		getInstance()->gameSprites.insert_or_assign(n,sprite);
	}
}

sf::Texture * GameAssetsManager::getTexture(std::string texture)
{
	std::map<std::string, sf::Texture>::iterator i = getInstance()->textures.find(texture);

	if (i == getInstance()->textures.end()) 
	{ 
		Logger::e("Failed to get texture \"" + texture + "\"");
		return &getInstance()->textures["default"];
	}
	else { return &i->second; }
}

GameSprite * GameAssetsManager::getSprite(std::string sprite)
{
	std::map<std::string, GameSprite>::iterator i = getInstance()->gameSprites.find(sprite);

	if (i == getInstance()->gameSprites.end())
	{
		Logger::e("Failed to get sprite \"" + sprite + "\"");
		return &getInstance()->gameSprites["default"];
	}
	else { return &i->second; }
}

void GameAssetsManager::loadDefaultResources()
{
		HRSRC resBlock = FindResource(NULL, MAKEINTRESOURCE(IDB_PNG1), L"PNG");
		HGLOBAL myGlobal = LoadResource(NULL, resBlock);
		LPVOID firstByte = LockResource(myGlobal);
		DWORD resSize = SizeofResource(NULL, resBlock);
		sf::Texture defaultTexture;
		defaultTexture.loadFromMemory(firstByte, resSize);
		textures.insert_or_assign("default", defaultTexture);

		//GameSprite defaultSprite;
		//defaultSprite.SetTexture(*getTexture("default"));
		//gameSprites.insert_or_assign("default", defaultSprite);
}