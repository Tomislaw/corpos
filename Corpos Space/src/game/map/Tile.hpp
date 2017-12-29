#include <SFML\Graphics.hpp>
#include "game\utility\TextFileData.hpp"
#include "game\engine\Entity.hpp"
#include "game\graphics\Particle.hpp"
#ifndef	TILE_HPP
#define TILE_HPP

//Struct with single tile definition
struct TileDefinition
{
	//Name used for comparing if tiles are same
	std::string name = "0";

	//TExture name used in creating vertex tile ma[
	std::string texture_name = "";

	// Health, -1 is indestructabl
	float health = - 1;

	//contains diffirent parts of tile
	//left top
	std::vector<sf::IntRect>LT;
	//top
	std::vector<sf::IntRect>T;
	//right top
	std::vector<sf::IntRect>RT;
	//left
	std::vector<sf::IntRect>L;
	//center
	std::vector<sf::IntRect>C;
	//right
	std::vector<sf::IntRect>R;
	//left bottom
	std::vector<sf::IntRect>LB;
	//bottom
	std::vector<sf::IntRect>B;
	//right bottom
	std::vector<sf::IntRect>RB;
	//inner right bottom
	std::vector<sf::IntRect>IRB;
	//inner right top
	std::vector<sf::IntRect>IRT;
	//inner left top
	std::vector<sf::IntRect>ILT;
	//inner left bottom
	std::vector<sf::IntRect>ILB;
	//single whole tile
	std::vector<sf::IntRect>inner;

	// is blocking player and bullets
	bool is_blocking = false;
	// is using only "inner" for viewing tile
	bool singleImage = true;
	//tile group where they connect each other, -1 means to nothing
	std::string connectGroup = "";
	//background tile
	std::string backgroundTile = "";

	void setTile(TextElement *t, const sf::Texture * texture,std::string textureName);
	sf::IntRect getLTRect(bool L, bool LT, bool T);
	sf::IntRect getRTRect(bool T, bool TR, bool R);
	sf::IntRect getRBRect(bool R, bool RB, bool B);
	sf::IntRect getLBRect(bool B, bool LB,bool L);
	sf::IntRect getInnerRect();
	const sf::Color & getRandomColor();
	const sf::Texture * texture = nullptr;
	sf::IntRect tileRect;
	std::string toString();

	std::vector<sf::Color> destroyParticleColors;
};

struct Particle;

class Tile : public Entity
{
	public:
	Tile();
	Tile(TileDefinition * tiledef, std::vector<sf::Vertex*> tile, sf::Vector2f pos);
	//~Tile();

	void changeTile(TileDefinition * tiledef, std::vector<sf::Vertex*> tile, sf::Vector2f pos);
	bool isBlocking() { return is_blocking; };
	bool isSameGroup(Tile & tile);
	bool isDestroyed() { return is_destroyed; };
	Particle getRandomParticle();
	sf::Color getRandomParticleColor();

	//bool isConnectToAllTiles() { return connectAll; };
	void setDisplayType(bool LT, bool T, bool TR,
		bool L, bool R,
		bool LB, bool B, bool BR);
	void setPosition(sf::Vector2f pos);

	void damage(int health);
	void destroy();
	private:

	TileDefinition * definition;
	std::vector<sf::Vertex*> tile;
	sf::IntRect tileRect;

	float health;
	float maxHealth;
	int display_type = 0;
	bool is_blocking = false;
	bool singleImage = false;
	bool is_destroyed = false;
	std::string connectGroup = "";

};



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

