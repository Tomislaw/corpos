#ifndef	TILEMAP_HPP
#define TILEMAP_HPP
#include "Tile.hpp"

class EntityList;
//Struct with all tilemap graphic related studd
// 
struct VertexTileMap
{
	//Vertex tilemap name
	std::string name;
	//Vertex tilemap texture name
	std::string textureName;
	// foreground vertex array - used for drawing
	sf::VertexArray vmap;
	// background vertex array - used for drawing
	sf::VertexArray backgroundvmap;
	// pointer to texture of tilemap
	const sf::Texture *texture;
	// tile defintions related to this tilemap
	std::vector<TileDefinition> definitions;
	// return pointer to tile definition with chosen name, nullptr if ont found
	TileDefinition * getTileDefinition(std::string name);
	// return tile at position in vector - have to know exact value
	std::vector<sf::Vertex *> VertexTileMap::getTileAt(int x);
	// return tile at position in vector - have to know exact value
	std::vector<sf::Vertex *> VertexTileMap::getBackgroundTileAt(int x);
	// TODO: add gettile function with x and y values as parameters
};

// Main tilemap class, manages loading maps and creating vertex tile maps
class Tilemap
{
public:
	Tilemap();
	~Tilemap();

	// set entity list pointer, used for creating particles after destroying tiles
	void setEntityListPtr(EntityList * ptr);

	// load tileset from given location - tileset is list of tile definitons
	bool loadTileset(std::string location);
	// load map from text element
	bool loadMap(TextElement * tm);
	// create map used in map editor- TODO: finish create map function
	void createMap(unsigned int width, unsigned int height);
	// return first vtm from list
	VertexTileMap * getVertexTileMapByTextureName(std::string name);
	// return first vtm from list
	VertexTileMap * getVertexTileMap(std::string name);
	// return vertex tile map
	std::vector<VertexTileMap> & getVertexTileMapVector();
	// return pointer to tile
	Tile * getTile(int x, int y);
	// return pointer to tile
	Tile * getTile(sf::Vector2i id);
	// return pointer to tile
	Tile * getTile(sf::Vector2f position);
	// return pointer to background tile
	Tile * getBackgroundTile(int x, int y);

	// sets tile or background tile
	void setTile(TileDefinition * , size_t x, size_t y);

	// return tile definition from chosen vertex tile map, nullptr if not found
	TileDefinition * getTileDefinition(std::string tile, std::string tilesetName);
	// change position to tile id
	sf::Vector2i getTileId(sf::Vector2f position);
	sf::Vector2i getTileId(float x, float y);
	//return map size
	sf::Vector2f getMapSize();

	// return is tile collidable
	bool isTileBlocking(int x, int y);
	// return is tile collidable
	bool isTileBlocking(sf::Vector2i id);
	// return is chosen tile is same group TODO: return false if one is background tile and other one is not
	bool isSameTile(int x, int y,Tile * tile);
	// return is chosen tile is same group TODO: return false if one is background tile and other one is not
	bool isSameBackgroundTile(int x, int y, Tile * tile);
	// draw it
	void draw(sf::RenderTarget &window);
	// draw background tiles
	void drawBackground(sf::RenderTarget &window);
	// draw map editor related stuff
	void drawEditor(sf::RenderTarget &window);
	// set all tiles to merge with other tiles, it should be used only once at start
	void refreashMap();
	// refreash tile at selected pos
	void refreashBackgroundTile(int x, int y);
	// refreash tile at selected pos
	void refreashTile(int x, int y);
	// refreash near tiles, used after tile is destroyed
	void refreashNearTiles(int x,int y);
	// get all tiles in line, TODO: finish getTilesFromLine function
	std::vector<Tile*> getTilesFromLine(sf::Vector2f start, sf::Vector2f end);

	TextElement generateTextElement();
	// return pointer to function GetTExture. 
	std::function<sf::Texture*(std::string)> &getFunctionGetTexture();
private:
	sf::Vector2i mapSize;
	//TODO: maybe change it to std::map instead of vector?
	std::vector<VertexTileMap> vtm;
	//std::vector<TileDefinition> tileDefinitions;
	std::vector<Tile> tilemap;
	std::vector<Tile> bgtilemap;
	//Tile *tilemap;
	EntityList * entityListPtr = nullptr;

	std::function<sf::Texture*(std::string)> getTexture;
	sf::FloatRect mapFrame;
};

#endif
