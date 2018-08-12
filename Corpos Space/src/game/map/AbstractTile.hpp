#include <SFML\Graphics.hpp>
#include "game\engine\Collideable.hpp"
#include "TileDefinition.hpp"
#ifndef	ABSTRACT_TILE_HPP
#define ABSTRACT_TILE_HPP

#define TILE_SIZE 32.f

struct TileDefinition;

class AbstractTile //: public Collideable
{
public:

	AbstractTile(std::shared_ptr<TileDefinition> tiledef, sf::Vector2i pos);

	void load(sf::VertexArray& array);
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
	bool isSameGroup(AbstractTile & tile);
	bool isSameGroup(std::shared_ptr<AbstractTile> tile);
	bool isDestroyed();;

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
	__int8 alignTiles = 0;
	bool destroyed = false;

	std::vector<sf::Vertex * > tile;
	std::shared_ptr<TileDefinition> definition;


};

#endif