#ifndef	TILESET_HPP
#define TILESET_HPP
#include "TileDefinition.hpp"
struct Tileset
{
public:
	std::string name;
	std::string textureName;
	std::vector<std::shared_ptr<TileDefinition>> tileDefinitions;

	std::shared_ptr<TileDefinition> getTileDefinition(std::string name)
	{
		for (int i = 0; i < tileDefinitions.size(); i++)
		{
			if (tileDefinitions[i]->name == name)
				return tileDefinitions[i];
		}
		return nullptr;
	}

	bool loadFromFile(std::string location)
	{
		TextFileData file;

		Logger::i("Loading tileset definition in \"" + location + "\"");
		//load file
		file.loadFile(location);


		auto tileset = file.getFirstElementByName("TILESET");
		if (tileset == nullptr)
		{
			Logger::e("Tileset in " + location + " is not defined, tileset is not loaded");
			return false;
		}


		auto varName = tileset->getVariableByName("Name");
		if (varName != nullptr)
			name = tileset->getVariableByName("Name")->toString(0);
		else
		{
			Logger::e("Tileset in " + location + " have no name!");
		}

		auto varTexture = tileset->getVariableByName("Texture");
		if (varTexture != nullptr)
			textureName = varTexture->toString(0);
		else
		{
			Logger::e("Texture in " + location + " is not defined, tileset is not loaded");
			return false;
		}

		sf::Texture * texture = GameAssetsManager::getTexture(textureName);


		// set tile definitions data

		auto tiles = file.getAllElementsByName("TILE");
		for (int i = 0; i < tiles.size(); i++)
		{
			std::shared_ptr<TileDefinition> t = std::make_shared<TileDefinition>();
			t->setTile(tiles[i], texture, textureName);
			tileDefinitions.push_back(t);
		}

		setBackgroundTileDefinitions();
		return true;
	}

private:
	void setBackgroundTileDefinitions()
	{
		for each (auto def in tileDefinitions)
		{
			if (def->backgroundTile == "")
			{
				continue;
			}
			else
			{
				auto bgDef = getTileDefinition(def->backgroundTile);
				def->backgroundTileDefinition = bgDef;
			}
		}
	}
};

#endif