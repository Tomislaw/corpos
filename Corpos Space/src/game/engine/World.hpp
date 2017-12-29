#ifndef	WORLD_HPP
#define WORLD_HPP

#include <SFML\Graphics.hpp>
#include "game\utility\Logger.hpp"
#include "game\utility\TextFileData.hpp"
#include "game\engine\EntityList.hpp"
#include "game\map\Tilemap.hpp"
#include <functional>
//One of the main classes that contains EntityList(enitity container) and tilemap.
//
class World
{
public:
	World();
	~World();

	// load text file with location to all textures we want to load. Using it again will destroy all previously loaded textures
	//TODO: support loading from multiple text files - make texture list instead table?
	static bool loadTextures(std::string location);

	// load 
	bool loadEntitylist(std::string location);
	static sf::Texture* getTexture(std::string name);

	void update(float delta);
	void draw(sf::RenderWindow & window);
	void events(sf::Event e);
	void loadMap(std::string map);
protected:

	EntityList entitylist;
	Tilemap tilemap;
	sf::Sprite background;
private:
	static std::string *texture_names;
	static sf::Texture *texture;
	static int textureArraySize;

	


};

#endif