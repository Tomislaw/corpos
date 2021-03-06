#ifndef ENTITYLIST_HPP
#define ENTITYLIST_HPP

#include <vector>
#include "Characters\CharacterFactory.hpp"
#include "game\engine\Prop.hpp"
#include "game\engine\Player.hpp"
#include "game/engine/Landscape.hpp"
#include "game\graphics\ParticleSystem.hpp"
#include "game\engine\logic\Camera.hpp"
#include "game\utility\Quadtree.hpp"
#include "game/engine/logic/Logic.h"
//class Tilemap;
namespace corpos
{
	class TileMap;
	class EntityList
	{
	public:
		EntityList();
		~EntityList();

		// find & add

		void loadMap(TextFileData & file);
		bool loadMap(json & map);
		// add character from smart pointer
		void addCharacter(std::shared_ptr<Character> & ent);
		// add prop from smart pointer
		void addProp(std::shared_ptr<Prop> & ent);
		// add landscape from smart pointer
		void addLandscape(std::shared_ptr<Landscape> & ent);
		// add bullet
		void addBullet(std::shared_ptr<Bullet>& bullet);
		// find entity, nullptr if not found
		std::shared_ptr<Entity> findEntity(std::string name);
		// find entites by name, TODO: change pointer to reference
		std::vector<std::shared_ptr<Entity>> findEntities(std::string name);

		// keyboard-mouse events
		void events(sf::Event & e);
		// update it
		void update(float time);
		// draw it
		void draw(sf::RenderWindow& window);
		// draw background elements
		void drawBackground(sf::RenderWindow& window);
		// check bullet collision with all props
		bool checkBulletCollision(Bullet * bullet);

		//
		Camera & getCurrentCamera();

		//setters
		// set player entity for player class
		void setPlayerEntity(std::string name);
		// set tilemap pointer used in detecting collision
		//void setTilemapPtr(Tilemap * ptr);
		void setTileMapPtr(TileMap * ptr);
		//Tilemap * getTilemapPtr() { return tilemapPtr; }
		TileMap * getTileMapPtr() { return tileMapPtr; }
		//objects

		ActionManager & actions() { return actionManager; }

	private:
		ActionManager actionManager;

		Quadtree tree;

		std::vector<std::shared_ptr <Entity >> entities;
		std::vector<std::shared_ptr <Character>> characters;
		std::vector<std::shared_ptr <Prop>> props;
		std::vector<std::shared_ptr <Landscape>> landscapes;
		std::vector<std::shared_ptr <Bullet>> bullets;

		ParticleSystem particleSystem;

		Camera camera;
		Player player;

		//Tilemap * tilemapPtr = nullptr;
		TileMap * tileMapPtr = nullptr;
		sf::Vector2f cursorPos;

		void resolveActions(ActionManager manager);
	};
}
#endif