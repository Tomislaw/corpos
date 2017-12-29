#ifndef	TILEMAP_HPP
#define TILEMAP_HPP
#include "Tile.hpp"

class EntityList;
struct VertexTileMap
{
	std::string name;
	std::string textureName;
	sf::VertexArray vmap;
	sf::VertexArray backgroundvmap;
	const sf::Texture *texture;
	std::vector<TileDefinition> definitions;
	TileDefinition * getTileDefinition(std::string name);
	std::vector<sf::Vertex *> VertexTileMap::getTileAt(int x);
	std::vector<sf::Vertex *> VertexTileMap::getBackgroundTileAt(int x);
};

class Tilemap
{
public:
	Tilemap();
	~Tilemap();

	void setEntityListPtr(EntityList * ptr);

	bool loadTileset(std::string location);
	bool loadMap(TextElement * tm);
	void createMap(unsigned int width, unsigned int height);
	VertexTileMap * getVertexTileMapByTextureName(std::string name);
	VertexTileMap * getVertexTileMap(std::string name);
	Tile * getTile(int x, int y);
	Tile * getTile(sf::Vector2i id);
	Tile * getTile(sf::Vector2f position);
	Tile * getBackgroundTile(int x, int y);
	TileDefinition * getTileDefinition(std::string tile, std::string tilesetName);

	sf::Vector2i getTileId(sf::Vector2f v);
	sf::Vector2f getMapSize();


	bool isTileBlocking(int x, int y);
	bool isTileBlocking(sf::Vector2i id);
	bool isSameTile(int x, int y,Tile * tile);
	bool isSameBackgroundTile(int x, int y, Tile * tile);
	void draw(sf::RenderTarget &window);
	void drawBackground(sf::RenderTarget &window);
	void drawEditor(sf::RenderTarget &window);
	void refreashMap();
	void refreashBackgroundTile(int x, int y);
	void refreashTile(int x, int y);
	void refreashNearTiles(int x,int y);
	void getTilesFromLine(sf::Vector2f start, sf::Vector2f end);

	std::function<sf::Texture*(std::string)> &getFunctionGetTexture();
private:
	sf::Vector2i mapSize;
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
