#ifndef ENTITYLIST_HPP
#define ENTITYLIST_HPP

#include <vector>
#include "Characters\CharacterCreator.hpp"
#include "game\engine\Prop.hpp"
#include "game\engine\Player.hpp"
#include "game\graphics\ParticleSystem.hpp"
#include "game\engine\logic\Camera.hpp"
class Tilemap; 
class EntityList
{
public:
	EntityList();
	~EntityList();

	// find & add
	// add character from smart pointer
	void addCharacter(std::shared_ptr<Character> & ent);
	// add prop from smart pointer
	void addProp(std::shared_ptr<Prop> & ent);
	// add bullet
	void addBullet(std::shared_ptr<Bullet>& bullet);
	// find entity, nullptr if not found
	Entity* findEntity(std::string name);
	// find entites by name, TODO: change pointer to reference
	std::vector<Entity*> findEntities(std::string name);

	// return sprite definition TODO: maybe make singleton class with all textures&sprite definitions
	static GameSprite* getSpriteDefinition(std::string name);
	// load sprite definitions
	static void loadSpriteDefinition(std::string location);

	// keyboard-mouse events
	void events(sf::Event & e);
	// update it
	void update(float time);
	// draw it
	void draw(sf::RenderWindow& window);

	// check bullet collision with all props
	bool checkBulletCollision(Bullet * bullet);

	//
	Camera & getCurrentCamera();

	//setters
	// set player entity for player class
	void setPlayerEntity(std::string name);
	// set tilemap pointer used in detecting collision
	void setTilemapPtr(Tilemap * ptr);
	//objects
	
private:
	static std::vector <GameSprite> game_sprite_definitions;
	std::vector<std::shared_ptr <Character>> characters;
	std::vector<std::shared_ptr <Prop>> props;
	std::vector<std::shared_ptr <Bullet>> bullets;
	ParticleSystem particleSystem;

	Camera camera;
	Player player;

	Tilemap * tilemapPtr =nullptr;
};

#endif
