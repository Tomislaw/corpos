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
#include "Node.hpp"
#include <atomic>

namespace corpos 
{
	class MapTile;
}


namespace AStar
{
	using uint = unsigned int;
	using HeuristicFunction = std::function<uint(sf::Vector2i, sf::Vector2i)>;
	using CoordinateList = std::list<sf::Vector2i>;

	using NodeSet = std::set<Node*>;
	using NodeDeque = std::deque<Node>;
	using NodeVector = std::vector<Node*>;
	class PathFind
	{
	public:
		PathFind(const NavigationNodeCharacterData character = NavigationNodeCharacterData());
		void setHeuristic(HeuristicFunction heuristic_);
		NodeDeque findPath(Node source_, sf::Vector2i target_);
		//Check if can still walk this path
		bool checkPath(NodeDeque & path);

		NavigationNodeCharacterData character;
		GroundJumpingSucessors succesorsOfNode;

		void releaseNodes();
		void stop() { isStopped = true; };
	private:
		HeuristicFunction heuristic;
		void releaseNodes(NodeSet& nodes_);
		void releaseNodes(NodeVector& nodes_);
		Node* findNodeOnList(NodeSet& nodes_, sf::Vector2i coordinates_);
		Node* findNodeOnList(NodeVector& nodes_, Node & node);
		std::atomic<bool> isStopped = false;
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