#ifndef NODE_HPP
#define NODE_HPP

#pragma once

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

	class Node : public Loggable
	{
	public:
		const static int DEFAULT_FALL_DISTANCE = 6;

		Node() {}
		Node(sf::Vector2i coord_, Node *parent_ = nullptr, int type = 0, int fallDistanceLeft = DEFAULT_FALL_DISTANCE, int jumpDistanceLeft = 0);
		Node(sf::Vector2f pos_, Node *parent_ = nullptr);

		bool isReached(Character & character, Node * previousNode = nullptr);
		
		bool isSame(Node * node);
		unsigned int getScore();
		unsigned int getCost(Node * node);
		sf::Vector2f getPosition();
		unsigned int G, H, F;
		sf::Vector2i coordinates;

		Node *parent;
		unsigned int jumpDistanceLeft;
		unsigned int fallDistanceLeft = 3;
		unsigned int type;
		enum Type { CENTER_POSITION, FLY, JUMP, WALK, CLIMB, FALL, BEFORE_JUMP, AFTER_JUMP };

		float timeSpend = 3;

		std::string toString() override {
			std::string typeStr;
			switch (type)
			{
			case CENTER_POSITION: typeStr = "CENTER_POSITION"; break;
			case FLY: typeStr = "FLY"; break;
			case JUMP: typeStr = "JUMP"; break;
			case FALL: typeStr = "FALL"; break;
			case WALK: typeStr = "WALK"; break;
			case CLIMB: typeStr = "CLIMB"; break;
			case AFTER_JUMP: typeStr = "AFTER_JUMP"; break;
			default: "UNKNOWN"; break;
			}

			return  PrettyString(coordinates, typeStr).formatted("Node( coord: {}, type: {} )");
		}
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
		virtual std::vector<Node> getSuccesors(Node * node, NavigationNodeCharacterData &character) = 0;
	};

	class GroundWalkingSucessors : public Sucessors {
	public:
		std::vector<Node> getSuccesors(Node * node, NavigationNodeCharacterData &character);
	};

	class GroundJumpingSucessors : public GroundWalkingSucessors {
	public:
		//todo :  remove jumping left and right
		std::vector<Node> getSuccesors(Node * node, NavigationNodeCharacterData &character);
	};

	class PathfindUtils {
	public:
		static GetTile getTile;
		static bool canFitInTile(sf::Vector2i tileId, NavigationNodeCharacterData &character);
		static bool canStandOnTile(sf::Vector2i tileId, NavigationNodeCharacterData &character);
		static bool canMoveToTile(sf::Vector2i startTileId, sf::Vector2i endTileId, NavigationNodeCharacterData &character);
		static bool canMoveToTileWhileWalking(sf::Vector2i startTileId, sf::Vector2i endTileId, NavigationNodeCharacterData &character);
		static bool  isCanMissWhileFailing(sf::Vector2i tileId, NavigationNodeCharacterData &character);
	
	private: 
		static bool isTileBlocking(sf::Vector2i subTileId);
	};
}

#endif