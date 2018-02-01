#ifndef AIBASIC_HPP
#define AIBASIC_HPP
#include "game\engine\Character.hpp"
#include <queue>

struct NavigationNode
{
	sf::Vector2f position;
	int type;
	float timeToSpendOn = 2;

	bool isReached(Character & character)
	{
		auto rect = sf::FloatRect(position - sf::Vector2f(10, 10), sf::Vector2f(20, 20));
		return character.intersects(rect);
	}
	enum Type { MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, JUMP };
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

	enum Behavior { IDLE, ALERTED,ENGAGE,SUSPICIOUS,PANIC };

	void addNode(sf::Vector2i tileId, int type)
	{
		NavigationNode node;
		node.position = sf::Vector2f(tileId.x * 32 + 16, tileId.y * 32 + 16);
		node.type = type;
		navigationNodes.push(node);
	}
protected:
	Character & character;
	EntityList * entityListPtr = nullptr;
	Tilemap * tilemapPtr = nullptr;

	std::queue<NavigationNode> navigationNodes;

	int behavior = 0;



};

#endif;