#include <SFML\Graphics.hpp>
#include "game\utility\TextFileData.hpp"
#include <memory>

#ifndef	TILE_DEFINITION_HPP
#define TILE_DEFINITION_HPP
//Struct with single tile definition
struct TileDefinition
{
public:
	//Name used for comparing if tiles are same
	std::string name = "0";

	//TExture name used in creating vertex tile ma[
	std::string texture_name = "";

	// Health, -1 is indestructabl
	int health = -1;

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

	bool showBackground = false;

	//tile group where they connect each other, -1 means to nothing
	std::string connectGroup = "";
	//background tile
	std::string backgroundTile = "";
	std::weak_ptr<TileDefinition> backgroundTileDefinition;

	void setTile(TextElement *t, const sf::Texture * texture, std::string textureName);
	sf::IntRect getLTRect(bool L, bool LT, bool T);
	sf::IntRect getRTRect(bool T, bool TR, bool R);
	sf::IntRect getRBRect(bool R, bool RB, bool B);
	sf::IntRect getLBRect(bool B, bool LB, bool L);
	sf::IntRect getInnerRect();
	const sf::Color & getRandomColor();
	const sf::Texture * texture = nullptr;
	sf::IntRect tileRect;
	std::string toString();

	std::vector<sf::Color> destroyParticleColors;

	TextElement generateTextElement();
};

#endif