#ifndef AIBASIC_HPP
#define AIBASIC_HPP
#include "game\engine\Character.hpp"
#include "NavigationNode.hpp"
#include <queue>




struct NavNode
{
	sf::Vector2i tilePosition;
	int type;
	float timeToSpendOn = 2;

	bool isReached(Character & character)
	{
		return character.getStandingTileId() == tilePosition;
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

	void addNode(sf::Vector2i tileId, int type)
	{
		NavNode node;
		node.tilePosition = tileId;
		node.type = type;
		navigationNodes.push(node);
	}
	void getPath(sf::Vector2i tile);

protected:
	


	AStarSearch<NavigationNode> astarsearch;
	Character & character;
	EntityList * entityListPtr = nullptr;
	Tilemap * tilemapPtr = nullptr;

	std::queue<NavNode> navigationNodes;
	



	int behavior = 0;
	bool isInitialized = false;
	sf::Text entityDebugText;


};

#endif;