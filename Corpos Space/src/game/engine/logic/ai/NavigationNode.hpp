#pragma once
#include "game\utility\AStarSearch.hpp"
#include "game\map\Tile.hpp"
#include "game\engine\Character.hpp"
class NavigationNode
{
public:
	int x;	 // the (x,y) positions of the node
	int y;

	NavigationNode() { x = y = 0; }
	NavigationNode(int px, int py) { x = px; y = py; }
	NavigationNode(sf::Vector2i tile_id) { x = tile_id.x; y = tile_id.y; }

	//heuristic functions
	float GoalDistanceEstimate(NavigationNode &nodeGoal);
	bool IsGoal(NavigationNode &nodeGoal);
	bool GetSuccessors(AStarSearch<NavigationNode> *astarsearch, NavigationNode *parent_node);
	bool GetSuccesorsGroundNode(AStarSearch<NavigationNode> *astarsearch, NavigationNode *parent_node);
	bool GetSuccesorsAirNode(AStarSearch<NavigationNode> *astarsearch, NavigationNode *parent_node);

	// return true if character can stand on tile
	bool canStand(int x, int y);

	// return false if character is too big to be here
	bool canWalk(int x, int y);

	float GetCost(NavigationNode &successor);
	bool IsSameState(NavigationNode &rhs);

	void PrintNodeInfo();

	Tile * GetTile(int x, int y);
	//void setMap(Vector2i &size, std::vector <Tile> &map) { map_size = &size; tilemap = &map; };



	void setFunctionGetTile(std::function < Tile*(sf::Vector2i)> get)
	{
		getTile = get;

	};
	void setCharacterData(const NavigationNodeCharacterData * d) {data = d ; };

	void setJumpHeight(unsigned int height) { jumpHeight = height;};
	unsigned int getJumpHeight() { return jumpHeight; }
private:

	unsigned int jumpHeight = 0;

	//	Vector2i *map_size;
	//std::vector <Tile> *tilemap;
	std::function < Tile*(sf::Vector2i)> getTile;

	const NavigationNodeCharacterData * data;
	//bool IsCharacter
};