#ifndef ENTITYLIST_HPP
#define ENTITYLIST_HPP

#include <vector>
#include "Characters\CharacterCreator.hpp"
#include "game\engine\Prop.hpp"
#include "game\engine\Player.hpp"
#include "game\graphics\ParticleSystem.hpp"
class Tilemap; 
class EntityList
{
public:
	EntityList();
	~EntityList();

	// find & add
	void addCharacter(std::shared_ptr<Character> & ent);
	void addProp(std::shared_ptr<Prop> & ent);
	void addBullet(std::shared_ptr<Bullet>& bullet);
	Entity* findEntity(std::string name);
	std::vector<Entity*> findEntities(std::string name);

	// getSpriteDefinition & loadSpriteDefinitions
	static GameSprite* getSpriteDefinition(std::string name);
	static void loadSpriteDefinition(std::string location);


	void events(sf::Event & e);
	void update(float time);
	void draw(sf::RenderWindow& window);


	bool checkBulletCollision(Bullet * bullet);

	//setters
	void setPlayerEntity(std::string name);
	void setTilemapPtr(Tilemap * ptr);
	//objects
	
private:
	static std::vector <GameSprite> game_sprite_definitions;
	std::vector<std::shared_ptr <Character>> characters;
	std::vector<std::shared_ptr <Prop>> props;
	std::vector<std::shared_ptr <Bullet>> bullets;
	ParticleSystem particleSystem;
	Player player;
	Tilemap * tilemapPtr;
};

#endif
