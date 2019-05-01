#include <SFML\Graphics.hpp>
#include "game\engine\Entity.hpp"
#include "TileDefinition.hpp"

#ifndef	TILE_HPP
#define TILE_HPP

// main tile entity

namespace corpos
{
	struct TileDefinition;
	struct Particle;

	class Tile : public Entity
	{
	public:
		//creates air tile
		Tile();
		Tile(TileDefinition * tiledef, std::vector<sf::Vertex*> tile, sf::Vector2f pos);
		//~Tile();

		// change tile, used in constructor and in future in map editor
		void changeTile(TileDefinition * tiledef, std::vector<sf::Vertex*> tile, sf::Vector2f pos);
		// return is tile collidable
		bool isBlocking() { return is_blocking; };
		// return true if tile is same group
		bool isSameGroup(Tile & tile);
		// retur true when destroyed
		bool isDestroyed() { return is_destroyed; };
		// used for creating debris
		Particle getRandomParticle();
		// used for creating debris
		sf::Color getRandomParticleColor();

		sf::FloatRect getCollisionBox();
		// previous attempt for merging tiles
		//bool isConnectToAllTiles() { return connectAll; };

		// set all 4 parts of tile to merge into other tile
		void setDisplayType(bool LT, bool T, bool TR,
			bool L, bool R,
			bool LB, bool B, bool BR);

		// set tile position
		void setPosition(sf::Vector2f pos);

		// damage tile TODO: look for errors in damage function, tile is destroyed when it haves some hp left
		void damage(int health);
		// destroy tile
		void destroy();

		void resetVertexPosition();

		int getHealth() { return health; }
		int getMaxHealth() { return maxHealth; }

		TileDefinition * getTileDefinition() {
			return definition
				;
		}
	private:

		// pointer to tile definition
		TileDefinition * definition;

		//vector of pointers to vertex
		std::vector<sf::Vertex*> tile;

		//used in creating drawable vertex
		sf::IntRect tileRect;

		int health;
		int maxHealth;
		int display_type = 0;
		bool is_blocking = false;
		bool singleImage = false;
		bool is_destroyed = false;
		//used in merging tiles together
		std::string connectGroup = "";
	};
}
//tile class 17.11.2017
/*
class Tile :
	public Entity
{
public:
	Tile();
	Tile(TileDefinition * tiledef, sf::Vector2f pos);
	~Tile();

	void draw(sf::RenderTarget & window) override;
	void setPosition(sf::Vector2f pos) override;
	bool isBlocking() {return is_blocking; };
	void setDisplayType(bool LT, bool T, bool TR,
		bool L, bool R,
		bool LB, bool B, bool BR);
private:
	TileDefinition * definition;

	sf::VertexArray tilevertex;
	float health;
	float maxHealth;
	int display_type = 0;
	bool is_blocking = false;
	bool singleImage = false;
};//*/

#endif