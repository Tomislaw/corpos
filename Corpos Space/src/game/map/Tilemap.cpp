#include "Tilemap.hpp"
#include "game\engine\World.hpp"
#include <math.h>

Tilemap::Tilemap()
{
	//tileDefinitions.push_back(TileDefinition());
}


Tilemap::~Tilemap()
{
}
void Tilemap::setEntityListPtr(EntityList * ptr) { entityListPtr = ptr; }
/*
bool Tilemap::loadTileset(std::string location)
{
	Logger::i("Loading tileset definition in \"" + location + "\"");
	TextFileData file;

	//load file
	file.load_file(location);

	auto tileset = file.get_first_element_by_name("TILESET");
	auto texture = tileset->get_variable_by_name("Texture")->var[0];
	auto tx = World::getTexture(texture);

	auto tiles = file.get_all_elements_by_name("TILE");
	for (int i = 0; i < tiles.size();i++)
	{
		TileDefinition t;
		t.setTile(tiles[i],tx);
		tileDefinitions.push_back(t);
	}
	

	return true;
}*/



bool Tilemap::loadTileset(std::string location)
{
	VertexTileMap tm;
	TextFileData file;

	Logger::i("Loading tileset definition in \"" + location + "\"");
	//load file
	file.load_file(location);





	//set vtm data
	auto tileset = file.get_first_element_by_name("TILESET");
	auto texture = tileset->get_variable_by_name("Texture")->to_string(0);

	tm.name = tileset->get_variable_by_name("Name")->to_string(0);
	tm.textureName = texture;


	if (getTexture == NULL)
	{
		Logger::e("Function getTexture for Tilemap is not set!. Fatal error.");
		return false;
	}
	tm.texture = getTexture(texture);
	//tm.texture = World::getTexture(texture);



	// set tile definitions data

	auto tiles = file.get_all_elements_by_name("TILE");
	for (int i = 0; i < tiles.size();i++)
	{
		TileDefinition t;
		t.setTile(tiles[i], tm.texture, texture);
		tm.definitions.push_back(t);
	}




	//set vertex array
	sf::VertexArray ar(sf::Quads, 16 * mapSize.x * mapSize.y);
	sf::VertexArray ar2(sf::Quads, 16 * mapSize.x * mapSize.y);
	/*sf::Vector2u tileSize(32, 32);
	for (unsigned int x = 0; x < mapSize.x; ++x)
		for (unsigned int y = 0; y < mapSize.y; ++y)
		{

			// get a pointer to the current tile's quad
			sf::Vertex* tile = &ar[(x + y * mapSize.x) * 16];

			// define its 4 corners
			quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
			quad[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
			quad[2].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f();
			quad[1].texCoords = sf::Vector2f();
			quad[2].texCoords = sf::Vector2f();
			quad[3].texCoords = sf::Vector2f();
		}*/

	tm.vmap = ar;
	tm.backgroundvmap = ar2;
	this->vtm.push_back(tm);
	return true;
}

bool Tilemap::loadMap(TextElement * tm)
{
	
	auto size = tm->get_variable_by_name("Size");

	mapSize.y = size->to_int(1);
	mapSize.x = size->to_int(0);

	Logger::i("Map size: " + std::to_string(this->mapSize.x) + " " + std::to_string(this->mapSize.y));



	std::string tilesetName = tm->get_variable_by_name("Tilesets")->var[0];
	auto vertexTileMapPointer = getVertexTileMap(tilesetName);
	if (vertexTileMapPointer == nullptr)
	{
		Logger::e("Cant find tilemap pointer");
		return false;
	}
	vertexTileMapPointer->vmap.resize((mapSize.x + mapSize.y * mapSize.x)*16);
	vertexTileMapPointer->backgroundvmap.resize((mapSize.x + mapSize.y * mapSize.x) * 16);
	tilemap.clear();


	for (int y = 0;y < mapSize.y;y++)
	{
		auto tile = tm->get_variable_by_name("X" + std::to_string(y));
		for (int x = 0; x < mapSize.x;x++)
		{

			auto b = this->getTileDefinition(tile->var[x], tilesetName);
			//Set tile if not found
			if (b == nullptr)
			{
				this->tilemap.push_back(Tile());
				this->bgtilemap.push_back(Tile());
			}
			else
			{
				auto vtm = getVertexTileMapByTextureName(b->texture_name);
				//set tile if found and blocking
				if (b->is_blocking)
				{
					auto c = this->getTileDefinition(b->backgroundTile, tilesetName);
					// set tile if noto found background one
					if (c==nullptr)
					{
						this->tilemap.push_back(Tile(b, vtm->getTileAt(x + y * mapSize.x), sf::Vector2f(x * 32 + 16, y * 32 + 16)));
						this->bgtilemap.push_back(Tile());
					}
					else //set tile normal
					{
						this->tilemap.push_back(Tile(b, vtm->getTileAt(x + y * mapSize.x), sf::Vector2f(x * 32 + 16, y * 32 + 16)));
						this->bgtilemap.push_back(Tile(c, vtm->getBackgroundTileAt(x + y * mapSize.x), sf::Vector2f(x * 32 + 16, y * 32 + 16)));
					}

	
				}
				else // set tile if it not blocking
				{
					this->tilemap.push_back(Tile());
					this->bgtilemap.push_back(Tile(b, vtm->getBackgroundTileAt(x + y * mapSize.x), sf::Vector2f(x * 32 + 16, y * 32 + 16)));
				}
			}
		}

	}
	refreashMap();
	return false;
}

void Tilemap::createMap(unsigned int width, unsigned int height)
{
	loadTileset("bin/graphics/tileset/tileset1.txt");

	this->mapSize.x = width;
	this->mapSize.y = height;

	/*for (int x = 0; x < mapSize.x;x++)
	{

		auto b = this->getTileDefinition(tile->var[x], tilesetName);
		//Set tile if not found
		if (b == nullptr)
		{
			this->tilemap.push_back(Tile());
			this->bgtilemap.push_back(Tile());
		}
		else
		{
			auto vtm = getVertexTileMapByTextureName(b->texture_name);
			//set tile if found and blocking
			if (b->is_blocking)
			{
				auto c = this->getTileDefinition(b->backgroundTile, tilesetName);
				// set tile if noto found background one
				if (c == nullptr)
				{
					this->tilemap.push_back(Tile(b, vtm->getTileAt(x + y * mapSize.x), sf::Vector2f(x * 32 + 16, y * 32 + 16)));
					this->bgtilemap.push_back(Tile());
				}
				else //set tile normal
				{
					this->tilemap.push_back(Tile(b, vtm->getTileAt(x + y * mapSize.x), sf::Vector2f(x * 32 + 16, y * 32 + 16)));
					this->bgtilemap.push_back(Tile(c, vtm->getBackgroundTileAt(x + y * mapSize.x), sf::Vector2f(x * 32 + 16, y * 32 + 16)));
				}


			}
			else // set tile if it not blocking
			{
				this->tilemap.push_back(Tile());
				this->bgtilemap.push_back(Tile(b, vtm->getBackgroundTileAt(x + y * mapSize.x), sf::Vector2f(x * 32 + 16, y * 32 + 16)));
			}
		}
	}*/

//}
//refreashMap();
}

VertexTileMap * Tilemap::getVertexTileMapByTextureName(std::string name)
{
	for (size_t i = 0; i < this->vtm.size(); i++)
	{
		if (vtm.at(i).textureName == name)
		{
			return &vtm.at(i);
		}
	}

	Logger::i("Vertextilemap with texture name  " + name + " not found.");
	return nullptr;
}

VertexTileMap * Tilemap::getVertexTileMap(std::string name)
{
	for (size_t i = 0; i < this->vtm.size(); i++)
	{
		if (vtm.at(i).name == name)
		{
			return &vtm.at(i);
		}
	}
	return nullptr;
}

/*
bool Tilemap::loadMap(TextElement * tm)
{

	loadTileset("bin/graphics/tileset/tileset1.txt");

	auto size = tm->get_variable_by_name("Size");
	this->mapSize.x = size->to_int(0);
	this->mapSize.y = size->to_int(1);

	tilemap = new Tile[mapSize.x*mapSize.y];

	
	for (int y = 0;y < mapSize.y;y++)
	{
		auto tile = tm->get_variable_by_name("X" + std::to_string(y));
		for (int x = 0; x < mapSize.x;x++)
		{
			auto b = this->getTileDefinitiom(tile->var[x]);
			*this->getTile(x,y) = Tile(b, sf::Vector2f(x * 32 + 16, y * 32 +16));
		}
		
	}
	refreashMap();
	return false;
}*/

/*VertexTileMap * Tilemap::getVertexTileMap(std::string name)
{
	for (size_t i = 0; i < this->vtm.size(); i++)
	{
		if (vtm.at(i).name == name)
		{
			return &vtm.at(i);
		}
	}
	return nullptr;
}*/

Tile * Tilemap::getTile(int x, int y)
{
	if (x<0 || y<0 || x >= mapSize.x || y >= mapSize.y)return nullptr;
	return &tilemap.at(x + y * mapSize.x);
}

Tile * Tilemap::getTile(sf::Vector2i id)
{
	return getTile(id.x,id.y);
}

Tile * Tilemap::getTile(sf::Vector2f position)
{
	return getTile(getTileId(position));
}

Tile * Tilemap::getBackgroundTile(int x, int y)
{
	if (x<0 || y<0 || x >= mapSize.x || y >= mapSize.y)return nullptr;
	return &bgtilemap.at(x + y * mapSize.x);
}

TileDefinition * Tilemap::getTileDefinition(std::string tileName, std::string tilesetName)
{
	VertexTileMap * vtmPointer = nullptr;
	for (int x = 0; x < vtm.size(); x++)
	{
		if (vtm.at(x).name == tilesetName) vtmPointer = &vtm.at(x);
		break;
	}
	if (vtmPointer == nullptr) 
	{
		Logger::e("Critical error! Can't find tile definition. - " + tilesetName);
		return nullptr;
	}
	if (vtmPointer->definitions.size() == 0)Logger::e("No tile definitions in " + vtmPointer->name);
	for (int x = 0; x < vtmPointer->definitions.size(); x++)
	{
		if (vtmPointer->definitions.at(x).name == tileName) return &vtmPointer->definitions.at(x);
	}
	
	Logger::i("Tile \"" + tileName + "\" not found!");

	return nullptr;
}

sf::Vector2i Tilemap::getTileId(sf::Vector2f v)
{
	int x = v.x / 32;
	int y =v.y / 32;
	return sf::Vector2i(x,y);
}

sf::Vector2f Tilemap::getMapSize()
{
	return sf::Vector2f(mapSize.x*32,mapSize.y*32);
}

bool Tilemap::isTileBlocking(int x, int y)
{
	if (x<0 || y<0 || x>=mapSize.x || y>=mapSize.y)return false;
	else return getTile(x, y)->isBlocking();
}

bool Tilemap::isTileBlocking(sf::Vector2i id)
{
	return isTileBlocking(id.x,id.y);
}

bool Tilemap::isSameTile(int x, int y,Tile * tile)
{
	if (x<0 || y<0 || x >= mapSize.x || y >= mapSize.y)return false;
	else
	{
		return getTile(x, y)->isSameGroup(*tile) && getTile(x, y)->isBlocking();
	} 
}

bool Tilemap::isSameBackgroundTile(int x, int y, Tile * tile)
{
	if (x<0 || y<0 || x >= mapSize.x || y >= mapSize.y)return false;
	else return getBackgroundTile(x, y)->isSameGroup(*tile);
}

void Tilemap::draw(sf::RenderTarget & window)
{
	/*for (int i = 0; i < mapSize.x *mapSize.y;i++)
	{
		tilemap[i].draw(window);
	}*/

	for (int i = 0; i < vtm.size();i++)
	{
		window.draw(vtm.at(i).vmap, vtm.at(i).texture);
	}
}

void Tilemap::drawBackground(sf::RenderTarget & window)
{
	for (int i = 0; i < vtm.size();i++)
	{
		window.draw(vtm.at(i).backgroundvmap, vtm.at(i).texture);
	}
}

void Tilemap::drawEditor(sf::RenderTarget & window)
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(mapSize.x*32, mapSize.y * 32));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(5);
	rectangle.setPosition(0, 0);
	window.draw(rectangle);
}

void Tilemap::refreashMap()
{
	for (int x = 0; x < mapSize.x; x++)
	{
		for (int y = 0; y < mapSize.y; y++)
		{
			refreashTile(x, y);
			refreashBackgroundTile(x, y);
		}
	}
}

void Tilemap::refreashBackgroundTile(int x, int y)
{
	if (this->getBackgroundTile(x, y) == nullptr) return;
	auto tile = this->getBackgroundTile(x, y);
	tile->setDisplayType(
		this->isSameBackgroundTile(x - 1, y - 1, tile), this->isSameBackgroundTile(x, y - 1, tile), this->isSameBackgroundTile(x + 1, y - 1, tile),
		this->isSameBackgroundTile(x - 1, y, tile), this->isSameBackgroundTile(x + 1, y, tile),
		this->isSameBackgroundTile(x - 1, y + 1, tile), this->isSameBackgroundTile(x, y + 1, tile), this->isSameBackgroundTile(x + 1, y + 1, tile));
}

void Tilemap::refreashTile(int x, int y)
{
	if (this->getTile(x, y)==nullptr) return;
	/*if(this->getTile(x, y)->isConnectToAllTiles())
	{
		this->getTile(x, y)->setDisplayType(
		this->isTileBlocking(x - 1, y - 1), this->isTileBlocking(x, y - 1), this->isTileBlocking(x + 1, y - 1),
		this->isTileBlocking(x - 1, y), this->isTileBlocking(x + 1, y),
		this->isTileBlocking(x - 1, y + 1), this->isTileBlocking(x, y + 1), this->isTileBlocking(x + 1, y + 1));
	}
	else
	{
		auto tile = this->getTile(x, y);
		tile->setDisplayType(
		this->isSameTile(x - 1, y - 1, tile), this->isSameTile(x, y - 1, tile), this->isSameTile(x + 1, y - 1, tile),
		this->isSameTile(x - 1, y, tile), this->isSameTile(x + 1, y, tile),
		this->isSameTile(x - 1, y + 1, tile), this->isSameTile(x, y + 1, tile), this->isSameTile(x + 1, y + 1, tile));
	}*/
	auto tile = this->getTile(x, y);
	tile->setDisplayType(
		this->isSameTile(x - 1, y - 1, tile), this->isSameTile(x, y - 1, tile), this->isSameTile(x + 1, y - 1, tile),
		this->isSameTile(x - 1, y, tile), this->isSameTile(x + 1, y, tile),
		this->isSameTile(x - 1, y + 1, tile), this->isSameTile(x, y + 1, tile), this->isSameTile(x + 1, y + 1, tile));
}

void Tilemap::refreashNearTiles(int x, int y)
{
	/*refreashTile(x-1,y-1)*/;refreashTile(x, y-1);//refreashTile(x+1,y-1);
	refreashTile(x - 1, y);refreashTile(x, y);refreashTile(x + 1, y);
	/*refreashTile(x - 1, y + 1);*/refreashTile(x, y + 1);//refreashTile(x + 1, y + 1);
}

void Tilemap::getTilesFromLine(sf::Vector2f start, sf::Vector2f end)
{
	auto tileStart = this->getTileId(start);
	auto tileEnd = this->getTileId(end);

}

std::function<sf::Texture*(std::string)>& Tilemap::getFunctionGetTexture()
{
	return this->getTexture;
}

TileDefinition * VertexTileMap::getTileDefinition(std::string name)
{
	if (this->definitions.size() == 0)Logger::e("Critical error! No tile definitions in " + this->name);
	for (size_t i = 0; i < this->definitions.size(); i++)
	{
		if (definitions.at(i).name == name)
		{
			return &definitions.at(i);
		}
	}
	Logger::i("Tile definition " + name + " not found. Returning first definition.");

	return &definitions.at(0);
}

std::vector<sf::Vertex *> VertexTileMap::getTileAt(int x)
{
	std::vector<sf::Vertex *> tile;
	tile.push_back(&this->vmap[x * 16]);
	tile.push_back(&this->vmap[x * 16+1]);
	tile.push_back(&this->vmap[x * 16+2]);
	tile.push_back(&this->vmap[x * 16+3]);

	tile.push_back(&this->vmap[x * 16+4]);
	tile.push_back(&this->vmap[x * 16+5]);
	tile.push_back(&this->vmap[x * 16+6]);
	tile.push_back(&this->vmap[x * 16+7]);

	tile.push_back(&this->vmap[x * 16+8]);
	tile.push_back(&this->vmap[x * 16+9]);
	tile.push_back(&this->vmap[x * 16+10]);
	tile.push_back(&this->vmap[x * 16+11]);

	tile.push_back(&this->vmap[x * 16 + 12]);
	tile.push_back(&this->vmap[x * 16 + 13]);
	tile.push_back(&this->vmap[x * 16 + 14]);
	tile.push_back(&this->vmap[x * 16 + 15]);
	return tile;
}

std::vector<sf::Vertex*> VertexTileMap::getBackgroundTileAt(int x)
{
	std::vector<sf::Vertex *> tile;
	tile.push_back(&this->backgroundvmap[x * 16]);
	tile.push_back(&this->backgroundvmap[x * 16 + 1]);
	tile.push_back(&this->backgroundvmap[x * 16 + 2]);
	tile.push_back(&this->backgroundvmap[x * 16 + 3]);

	tile.push_back(&this->backgroundvmap[x * 16 + 4]);
	tile.push_back(&this->backgroundvmap[x * 16 + 5]);
	tile.push_back(&this->backgroundvmap[x * 16 + 6]);
	tile.push_back(&this->backgroundvmap[x * 16 + 7]);

	tile.push_back(&this->backgroundvmap[x * 16 + 8]);
	tile.push_back(&this->backgroundvmap[x * 16 + 9]);
	tile.push_back(&this->backgroundvmap[x * 16 + 10]);
	tile.push_back(&this->backgroundvmap[x * 16 + 11]);

	tile.push_back(&this->backgroundvmap[x * 16 + 12]);
	tile.push_back(&this->backgroundvmap[x * 16 + 13]);
	tile.push_back(&this->backgroundvmap[x * 16 + 14]);
	tile.push_back(&this->backgroundvmap[x * 16 + 15]);
	return tile;
}
