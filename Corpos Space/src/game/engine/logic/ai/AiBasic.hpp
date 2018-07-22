#ifndef AIBASIC_HPP
#define AIBASIC_HPP
#include "game\engine\Character.hpp"
#include "NavigationNode.hpp"
#include <queue>
#include "game\utility\Pathfind.hpp"



struct NavNode
{
	sf::Vector2i tilePosition;
	int type;
	float timeToSpendOn = 2;
	int debugType = 0;
	bool isReached(Character & character)
	{
		auto charTilePos = character.getStandingTileId();
		if (!character.isStanding() && charTilePos.y >= tilePosition.y && type == WALK)
		{
			return (charTilePos.y > tilePosition.y);
		}
		else return charTilePos == tilePosition;
	}
	enum Type {LADDER, WALK, JUMP };
};



class AiBasic
{
public:
	AiBasic(Character & character);

	virtual void update(float delta);
	~AiBasic();

	virtual void think()
	{
		;
	}

	virtual void drawDebugData(sf::RenderTarget &target);

	enum Behavior { IDLE, ALERTED,ENGAGE,SUSPICIOUS,PANIC };


	void getPath(sf::Vector2i tile);

protected:
	//class object used for pathfinding
	AStar::PathFind pathfind;
	AStar::NodeDeque path;

	Character & character;
	EntityList * entityListPtr = nullptr;
	Tilemap * tilemapPtr = nullptr;





	int behavior = 0;
	bool isInitialized = false;
	sf::Text entityDebugText;


};

#endif;