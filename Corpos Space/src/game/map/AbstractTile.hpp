#include <SFML\Graphics.hpp>
#include "game\engine\Collideable.hpp"
#include "TileDefinition.hpp"
#include "game\utility\Flags.h"
#ifndef	ABSTRACT_TILE_HPP
#define ABSTRACT_TILE_HPP

#define TILE_SIZE 32.f

struct TileDefinition;

class AbstractTile //: public Collideable
{
public:

	AbstractTile(std::shared_ptr<TileDefinition> tiledef, sf::Vector2i pos);

	void load(std::shared_ptr<sf::VertexArray> array);
	void unload();

	void replace(std::shared_ptr<TileDefinition> tiledef);

	void updateTextureCoords(bool LT, bool T, bool TR,
		bool L, bool R,
		bool LB, bool B, bool BR);

	void updatePositionCoords(sf::Vector2i pos);
	void update();

	bool isBlocking();
	bool isBackground();
	bool isShowTilesBehind();
	bool isConnectingToTile(AbstractTile & tile);
	bool isConnectingToTile(std::shared_ptr<AbstractTile> tile);
	bool isDestroyed();;

	std::shared_ptr<TileDefinition> getTileDefinitionPtr() { return definition; };
	const TileDefinition & getTileDefinition() { return *definition.get(); };

	sf::Vector2i getId() { return position; };
	sf::Vector2f getPosition()
	{
		return sf::Vector2f(position.x*TILE_SIZE + TILE_SIZE / 2, 
			position.y*TILE_SIZE + TILE_SIZE / 2);
	}

	void destroy();
	//virtual void damage(int damage) = 0;
	//virtual void collide(sf::Vector2f point) = 0;

	private:

	sf::Vector2i position;

		//flags
	Flags8 alignTiles = 0;
	bool destroyed = false;

	unsigned int startingPos;
	__int8 vertexCount = 0;
	std::shared_ptr<sf::VertexArray> array;
	std::shared_ptr<TileDefinition> definition;

	sf::Vertex & vertex(unsigned int id)
	{
		return (*array)[id + startingPos];
	}

};

#endif