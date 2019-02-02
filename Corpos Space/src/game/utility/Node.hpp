#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <functional>
#include <set>
#include <list>
#include <algorithm>
#include <queue>
#include "game\engine\Character.hpp"

class MapTile;

namespace AStar {

	using GetTile = std::function<MapTile*(int x, int y)>;
	static GetTile getTile;

	class Node
	{
	public:
		Node(sf::Vector2i coord_, Node *parent_ = nullptr, int type = 0);
		Node(int x, int y, Node *parent_ = nullptr);

		std::vector<Node> getSuccesors();

		bool isReached(Character & character);
		bool isSame(Node * node);
		unsigned int getScore();
		unsigned int getCost(Node * node);

		unsigned int G, H, F;
		sf::Vector2i coordinates;

		Node *parent;
		unsigned int jumpDistancePassed;
		unsigned int type;
		enum Type { CENTER_POSITION, FLY, JUMP, WALK, CLIMB, FALL, BEFORE_JUMP, AFTER_JUMP };

		// how much time character have left to reach node
		float timeSpend = 3;
	};

	class NodeCompare_F
	{
	public:

		bool operator() (const Node *x, const Node *y) const
		{
			return x->F > y->F;
		}
	};

	class Sucessors {
	public:
		virtual std::vector<Node> getSuccesors(Node * node) = 0;
	};

	class GroundWalkingSucessors : public Sucessors {
		std::vector<Node> getSuccesors(Node * node);
	};

	class GroundJumpingSucessors : public Sucessors{
		std::vector<Node> getSuccesors(Node * node);
	};

	class PathfindUtils {
	public:
		static bool canFitInTile(sf::Vector2i tileId, NavigationNodeCharacterData character = NavigationNodeCharacterData());
		static bool canStandOnTile(sf::Vector2i tileId, NavigationNodeCharacterData character = NavigationNodeCharacterData());
		static bool canMoveToTile(sf::Vector2i startTileId, sf::Vector2i endTileId, NavigationNodeCharacterData character = NavigationNodeCharacterData());
		static bool canMoveToTileWhileWalking(sf::Vector2i startTileId, sf::Vector2i endTileId, NavigationNodeCharacterData character = NavigationNodeCharacterData());
	
	private: 
		static bool isTileBlocking(sf::Vector2i subTileId);
	};
}

#endif