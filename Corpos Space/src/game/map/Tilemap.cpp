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
	file.loadFile(location);

	auto tileset = file.getFirstElementByName("TILESET");
	auto texture = tileset->getVariableByName("Texture")->var[0];
	auto tx = World::getTexture(texture);

	auto tiles = file.getAllElementsByName("TILE");
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
	file.loadFile(location);





	//set vtm data
	auto tileset = file.getFirstElementByName("TILESET");
	if (tileset == nullptr)
	{
		Logger::e("Tileset in " + location +" is not defined, tileset is not loaded");
		return false;
	}


	std::string texture = "";
	auto varTexture = tileset->getVariableByName("Texture");
	if (varTexture != nullptr)
		texture = varTexture->toString(0);
	else 
	{
		Logger::e("Texture in " + location + " is not defined, tileset is not loaded");
		return false;
	}

	auto varName = tileset->getVariableByName("Name");
	if (varName != nullptr)
		tm.name = tileset->getVariableByName("Name")->toString(0);
	else
	{
		Logger::e("Tileset in " + location + " have no name!");
	}
	
	tm.textureName = texture;


	if (getTexture == NULL)
	{
		Logger::e("Function getTexture for Tilemap is not set!. Fatal error.");
		return false;
	}
	tm.texture = getTexture(texture);
	//tm.texture = World::getTexture(texture);



	// set tile definitions data

	auto tiles = file.getAllElementsByName("TILE");
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
	
	auto size = tm->getVariableByName("Size");
	if(size != nullptr)
	{ 
		mapSize.y = size->toInt(1);
		mapSize.x = size->toInt(0);
	}
	else
	{
		Logger::e("Map have no size");
		return false;
	}
	Logger::i("Map size: " + std::to_string(this->mapSize.x) + " " + std::to_string(this->mapSize.y));



	std::string tilesetName = "";
	auto varTilesets = tm->getVariableByName("Tilesets");
	if (varTilesets != nullptr)
	{
		tilesetName = varTilesets->toString(0);
	}
	else tilesetName = "tileset1";

	/*auto varTilesets = tm->getVariableByName("Tilesets");
	if (varTilesets != nullptr)
	{
		for each (std::string var in varTilesets->var)
		{

		}
	}*/


	auto vertexTileMapPointer = getVertexTileMap(tilesetName);
	if (vertexTileMapPointer == nullptr)
	{
		Logger::e("Cant find tilemap pointer");
		return false;
	}
	vertexTileMapPointer->vmap.resize((mapSize.x + mapSize.y * mapSize.x)*16);
	vertexTileMapPointer->backgroundvmap.resize((mapSize.x + mapSize.y * mapSize.x) * 16);
	tilemap.clear();
	bgtilemap.clear();

	for (int y = 0;y < mapSize.y;y++)
	{
		auto tile = tm->getVariableByName("X" + std::to_string(y));
		if (tile == nullptr)
		{
			Logger::e("X" + std::to_string(y) + " is missing, map is not created");
			return false;
		}
		for (int x = 0; x < mapSize.x;x++)
		{
	
			TileDefinition *b = nullptr;
			if(tile->toString(x)!="0")b = this->getTileDefinition(tile->var[x], tilesetName);

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
	//loadTileset("bin/graphics/tileset/tileset1.txt");


	mapSize.y = height;
	mapSize.x = width;

	Logger::i("Map size: " + std::to_string(this->mapSize.x) + " " + std::to_string(this->mapSize.y));



	if(vtm.size() == 0)
	{
		Logger::e("Tileset not loaded. Cannot create map.");
		return;
	}
	auto vertexTileMapPointer = &vtm.at(0);

	vertexTileMapPointer->vmap.resize((mapSize.x + mapSize.y * mapSize.x) * 16);
	vertexTileMapPointer->backgroundvmap.resize((mapSize.x + mapSize.y * mapSize.x) * 16);

	tilemap.clear();
	bgtilemap.clear();

	this->mapSize.x = width;
	this->mapSize.y = height;

	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{


			this->tilemap.push_back(Tile());
			this->bgtilemap.push_back(Tile());

		}
	}
	refreashMap();
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

std::vector<VertexTileMap>& Tilemap::getVertexTileMapVector()
{
	return vtm;
}

/*
bool Tilemap::loadMap(TextElement * tm)
{

	loadTileset("bin/graphics/tileset/tileset1.txt");

	auto size = tm->getVariableByName("Size");
	this->mapSize.x = size->toInt(0);
	this->mapSize.y = size->toInt(1);

	tilemap = new Tile[mapSize.x*mapSize.y];

	
	for (int y = 0;y < mapSize.y;y++)
	{
		auto tile = tm->getVariableByName("X" + std::toString(y));
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
	if (tilemap.size() < x + y * mapSize.x)return nullptr;
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
	if (bgtilemap.size() < x + y * mapSize.x)return nullptr;
	if (x<0 || y<0 || x >= mapSize.x || y >= mapSize.y)return nullptr;
	return &bgtilemap.at(x + y * mapSize.x);
	
}

void Tilemap::setTile(TileDefinition * definition, size_t x, size_t y)
{
	

	auto bg_tile = this->getBackgroundTile(x, y);
	auto tile = this->getTile(x, y);

	if (bg_tile == nullptr || tile == nullptr) return;
	bg_tile->resetVertexPosition();
	tile->resetVertexPosition();
	
	//Set tile if not found
	if (definition == nullptr)
	{

		*tile = Tile();
		*bg_tile = Tile();
		return;
	}

	auto vtm = getVertexTileMapByTextureName(definition->texture_name);

		
		//set tile if found and blocking
		if (definition->is_blocking)
		{
			
			auto background = vtm->getTileDefinition(definition->backgroundTile);
			// set tile if noto found background one
			if (background == nullptr)
			{
				*tile = Tile(definition, vtm->getTileAt(x + y * mapSize.x), sf::Vector2f(x * 32 + 16, y * 32 + 16));
				*bg_tile = Tile();
			}
			else //set tile normal
			{
				*tile = Tile(definition, vtm->getTileAt(x + y * mapSize.x), sf::Vector2f(x * 32 + 16, y * 32 + 16));
				*bg_tile = Tile(background, vtm->getBackgroundTileAt(x + y * mapSize.x), sf::Vector2f(x * 32 + 16, y * 32 + 16));
			}


		}
		else // set tile if it not blocking
		{
			*tile = Tile();
			*bg_tile = Tile(definition, vtm->getBackgroundTileAt(x + y * mapSize.x), sf::Vector2f(x * 32 + 16, y * 32 + 16));
		}

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

sf::Vector2i Tilemap::getTileId(float x, float y)
{
	return getTileId(sf::Vector2f(x,y));
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
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(2);
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
	auto tile = this->getTile(x, y);
	if (tile==nullptr) return;

	
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

std::vector<Tile*> Tilemap::getTilesFromLine(sf::Vector2f start, sf::Vector2f end)
{

	int tile_size = 32;

	std::vector<sf::Vector2i> tile_ids;

	auto tileStart = this->getTileId(start);
	auto tileEnd = this->getTileId(end);

	//make sure if we re npt adding additional tiles - -2,0 etc
	if (end.x < 0) tileStart.x = -1;
	if (end.y < 0) tileEnd.y = -1;
	
	//return one tile if started out of map
	if (tileStart == tileEnd || tileStart.x < 0 || tileStart.y < 0)
	{
		tile_ids.push_back(tileStart);

		//return tile_ids;
	}

		// Creating line to get tiles from
		float divide = end.x - start.x;
		float a = (end.y - start.y) / divide;
		float b = end.y - a*end.x;
		// change to infinity if dividing by zero
		if (!(divide>0.0000001 || divide<-0.0000001)) { a = INFINITY; }

		// start x and y counters
		int x_count = abs(tileStart.x - tileEnd.x);
		int y_count = abs(tileStart.y - tileEnd.y);


		// set adding or decrementing
		int operation_x = 1;
		int operation_y = 1;

		if (start.x > end.x)
		{
			operation_x = -1;
		}
		if (start.y > end.y)
		{
			operation_y = -1;
		}

		// ad start tile
		tile_ids.push_back(tileStart);
		// check if have to increment y or x more often
		if (a<1 && a>-1)
		{
			int current_x = tileStart.x;

			for (int i = 0; i < x_count; i++)
			{



				float value_x = current_x * tile_size + operation_x / 10.f + tile_size / 2 * (1 + operation_x);
				sf::Vector2f function_pos_x = sf::Vector2f(value_x, a*(value_x)+b);
				sf::Vector2i id_x = getTileId(function_pos_x);

				if (id_x.x != tile_ids.back().x && id_x.y != tile_ids.back().y)
				{
					float value_y = tile_ids.back().y * tile_size + tile_size / 2 * (1 + operation_y) + operation_y / 10.f;
					sf::Vector2f function_pos_y((sf::Vector2f((value_y - b) / a, value_y)));
					sf::Vector2i id_y(getTileId(function_pos_y));

					if (id_y != tile_ids.back())tile_ids.push_back(id_y);
					if (id_y.x < 0) break;
				}


				if (id_x != tile_ids.back())tile_ids.push_back(id_x);
				if (id_x.x < 0) break;
				current_x += operation_x;
			}
			sf::Vector2i id_last(getTileId(end));
			if (id_last != tile_ids.back())
			{
				if (id_last.x != tile_ids.back().x && id_last.y != tile_ids.back().y)
				{
					float value_y = tile_ids.back().y * tile_size + tile_size / 2 * (1 + operation_y) + operation_y / 10.f;
					sf::Vector2f function_pos_y((sf::Vector2f((value_y - b) / a, value_y)));
					sf::Vector2i id_y(getTileId(function_pos_y));

					if (id_y != tile_ids.back())tile_ids.push_back(id_y);

				}

				if (id_last != tile_ids.back())tile_ids.push_back(id_last);
			}
		}
		else
		{
			if (a != INFINITY)
			{
				int current_x = tileStart.x;
				int current_y = tileStart.y;


				for (int i = 0; i < y_count; i++)
				{

					float value_y = tile_ids.back().y * tile_size + tile_size / 2 * (1 + operation_y) + operation_y / 10.f;

					sf::Vector2f function_pos_y((sf::Vector2f((value_y - b) / a, value_y)));
					sf::Vector2i id_y(getTileId(function_pos_y));


					if (id_y.x != tile_ids.back().x && id_y.y != tile_ids.back().y)
					{
						float value_x = current_x * tile_size + operation_x / 10.f + tile_size / 2 * (1 + operation_x);
						sf::Vector2f function_pos_x = sf::Vector2f(value_x, a*value_x + b);
						sf::Vector2i id_x(getTileId(function_pos_x));
						if (id_x != tile_ids.back())tile_ids.push_back(id_x);
						if (id_x.x < 0)break;

						current_x += operation_x;

					}

					if (id_y != tile_ids.back())tile_ids.push_back(id_y);
					if (id_y.x < 0)break;
					current_y += operation_y;
				}
			}
			else
			{
				for (int i = 0; i < y_count; i++)
				{
					sf::Vector2i startvector = getTileId(start + sf::Vector2f(0, (i + 1)*tile_size));
					tile_ids.push_back(startvector);
					if (startvector.y < 0) break;
				}
			}


		}

		std::vector<Tile*> tiles;
		for each (sf::Vector2i var in tile_ids)
		{
			tiles.push_back(getTile(var));
		}
		return tiles;
}

TextElement Tilemap::generateTextElement()
{
	TextElement map;
	map.name = "TILEMAP";


	Variable name;
	name.name = "Name";
	name.var.push_back("name");
	map.variable.push_back(name);

	Variable size;
	size.name = "Size";
	size.var.push_back(std::to_string(mapSize.x));
	size.var.push_back(std::to_string(mapSize.y));
	map.variable.push_back(size);

	Variable tiles;
	tiles.name = "Tilesets";
	for (int i = 0; i < vtm.size(); i++)
	{
		tiles.var.push_back(vtm[i].name);
	}
	map.variable.push_back(tiles);

	for (int i = 0; i < mapSize.y; i++)
	{
		Variable v;
		v.name = "X" + std::to_string(i);
		for (int j = 0; j < mapSize.x; j++)
		{
			std::string name = getTile(j, i)->getName();
			if (name == "0")name = getBackgroundTile(j, i)->getName();
			v.var.push_back(name);
		}
		map.variable.push_back(v);
	}
	
	return map;
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
