/*
Copyright (c) 2015, Damian Barczynski <daan.net@wp.eu>
Following tool is licensed under the terms and conditions of the ISC license.
For more information visit https://opensource.org/licenses/ISC.
*/
#ifndef PATHFIND_HPP
#define PATHFIND_HPP

#include <vector>
#include <functional>
#include <set>
#include <list>
#include <algorithm>
#include <queue>
#include "game\engine\Character.hpp"


class MapTile;

namespace AStar
{

	using uint = unsigned int;
	using HeuristicFunction = std::function<uint(sf::Vector2i, sf::Vector2i)>;
	using CoordinateList = std::list<sf::Vector2i>;
	using GetTile = std::function<MapTile*(int x,int y)>;
	


	class Node
	{
	public:
		Node(sf::Vector2i coord_, Node *parent_ = nullptr);
		Node(int x,int y, Node *parent_ = nullptr);

		bool isReached(Character & character);
		bool isSame(Node * node);
		uint getScore();
		uint getCost(Node * node);

		uint G, H, F;
		sf::Vector2i coordinates;

		Node *parent;
		uint jumpDistancePassed;
		uint type;
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


	using NodeSet = std::set<Node*>;
	using NodeDeque = std::deque<Node>;
	using NodeVector = std::vector<Node*>;
	class PathFind
	{
		//bool detectCollision(sf::Vector2i coordinates_);


	public:
		PathFind();
		void setHeuristic(HeuristicFunction heuristic_);
		NodeDeque findPath(Node source_, sf::Vector2i target_);
		//Check if can still walk this path
		bool checkPath(NodeDeque & path);

	

		NavigationNodeCharacterData character;
		static GetTile getTile;

		void releaseNodes();
	private:
		HeuristicFunction heuristic;
		void releaseNodes(NodeSet& nodes_);
		void releaseNodes(NodeVector& nodes_);
		Node* findNodeOnList(NodeSet& nodes_, sf::Vector2i coordinates_);
		Node* findNodeOnList(NodeVector& nodes_, Node & node);

		bool canWalkToTile(Node * node, int x, int y);
		bool canStandOnTile(int x, int y);
		bool canMoveToTile(Node * node, int x, int y);

		std::vector<Node> getSuccesors(Node * node);
		std::vector<Node> getGroundSuccesors(Node * node);
		std::vector<Node> getAirSuccesors(Node * node);

		NodeVector OpenSet, ClosedSet;
	};

	class Heuristic
	{
		static sf::Vector2i getDelta(sf::Vector2i source_, sf::Vector2i target_);

	public:
		static uint manhattan(sf::Vector2i source_, sf::Vector2i target_);
		static uint euclidean(sf::Vector2i source_, sf::Vector2i target_);
		static uint octagonal(sf::Vector2i source_, sf::Vector2i target_);
	};
}

#endif // __ASTAR_HPP_8F637DB91972F6C878D41D63F7E7214F__