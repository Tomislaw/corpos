#ifndef AIBASIC_HPP
#define AIBASIC_HPP
#include "game\engine\Character.hpp"
#include "NavigationNode.hpp"
#include <queue>
#include "game\utility\Pathfind.hpp"
#include <thread>

class AiBasic
{
public:
	AiBasic(Character & character);

	virtual void update(float delta);
	~AiBasic();

	virtual void think()
	{

	}

	virtual void drawDebugData(sf::RenderTarget &target);

	enum Behavior { IDLE, ALERTED, ENGAGE, SUSPICIOUS, PANIC };

	void moveToTile(sf::Vector2i tile);

	void getPath(sf::Vector2i tile);

protected:
	//class object used for pathfinding
	AStar::PathFind pathfind = AStar::PathFind();
	AStar::NodeDeque path;


	Character & character;
	EntityList * entityListPtr = nullptr;
	TileMap * tilemapPtr = nullptr;

	int behavior = 0;
	bool isInitialized = false;
	sf::Text entityDebugText;
};

class AiAction {
public:
	virtual void update(float delta) = 0;
	virtual void calculate(const Character & character) = 0;
};

class MoveToTile : AiAction {
public:
	void update(float delta) override {

	}
	void calculate(const Character & character) override {
		if (false);
	}
private:
	bool isRouteCalculated = false;
};


#endif;