#include "Node.hpp"
#include <algorithm>
#include "game\map\MapTile\MapTile.hpp"

using namespace std::placeholders;
using namespace AStar;

GetTile AStar::getTile = nullptr;

Node::Node(sf::Vector2i coordinates_, Node *parent_, int type)
{
	parent = parent_;
	coordinates = coordinates_;
	G = H = F = 0;
	this->type = type;
	jumpDistancePassed = 0;
}

AStar::Node::Node(int x, int y, Node * parent_)
{
	parent = parent_;
	coordinates = sf::Vector2i(x, y);
	F = G = H = 0;
	type = jumpDistancePassed = 0;
}

unsigned int AStar::Node::getScore()
{
	return G + H;
}

bool Node::isSame(Node * node)
{
	return (node->coordinates == coordinates && node->type == type);
}

unsigned int AStar::Node::getCost(Node * node)
{
	if (node->coordinates.x == coordinates.x || node->coordinates.y == coordinates.y)return 10;
	return 14;
}

bool AStar::Node::isReached(Character & character)
{
	auto charTilePos = character.getStandingTileId();
	return charTilePos == coordinates;
}

std::vector<Node> AStar::GroundWalkingSucessors::getSuccesors(Node * node)
{
	auto succesors = std::vector<Node>();
	if (node == nullptr)return succesors;

	auto parentCoord = sf::Vector2i(-1, -1);

	if (node->parent != nullptr) {
		parentCoord = node->parent->coordinates;
	};

	if (node->type == Node::Type::WALK) {
		for(int x = -1; x <= 1; x++)
			for (int y = -1; y <= 1; y++) {
				auto newCoord = sf::Vector2i(x + node->coordinates.x, y + node->coordinates.y);
				if (newCoord == parentCoord)continue;

				if (PathfindUtils::canMoveToTile(node->coordinates, newCoord)) {

					int type = Node::Type::FALL;
					if(PathfindUtils::canStandOnTile(newCoord)) type = Node::Type::WALK;

					succesors.push_back(Node(newCoord, node, type));
				}
					

				if()
			}
	}

	return std::vector<Node>();
}

std::vector<Node> AStar::GroundJumpingSucessors::getSuccesors(Node * node)
{
	return std::vector<Node>();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// Pathfinding utils                  ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AStar::PathfindUtils::canFitInTile(sf::Vector2i tileId, NavigationNodeCharacterData character)
{
	bool canFitVerticaly = false;
	bool canFiHorizontaly = false;

	for (int x = 0; x < character.characterWidth; x++)
		for (int y = 0; y < character.characterHeight; y++) {
			int posX = tileId.x - character.characterWidth / 2 + x;
			int posY = tileId.y - character.characterHeight / 2 + y;
			if (isTileBlocking(sf::Vector2i(posX, posY))) return false;
		}

	return true;
}

bool AStar::PathfindUtils::canStandOnTile(sf::Vector2i tileId, NavigationNodeCharacterData character)
{
	for (int x = 0; x < character.characterWidth; x++) {
		int posX = tileId.x - character.characterWidth / 2 + x;
		if (isTileBlocking(sf::Vector2i(posX, tileId.y))) return true;
	}

	return false;
}

bool AStar::PathfindUtils::canMoveToTile(sf::Vector2i startTileId, sf::Vector2i endTileId, NavigationNodeCharacterData character)
{
	return canFitInTile(startTileId, character) && canFitInTile(endTileId, character);

	/*int lowerX = startTileId.x;
	if (endTileId.x < startTileId.x)lowerX = endTileId.x;

	int lowerY = startTileId.y;
	if (endTileId.y < startTileId.y)lowerY = endTileId.y;

	int additionalWidth = 1;
	int additionalHeight = 1;

	if (startTileId.x == endTileId.x)additionalWidth = 0;
	if (startTileId.y == endTileId.y)additionalHeight = 0;

	bool breakInCorners = (startTileId.x != endTileId.x) && (startTileId.y != endTileId.y);

	for (int x = 0; x < character.characterWidth + additionalWidth; x++)
		for (int y = 0; y < character.characterHeight + additionalHeight + 1; y++) {

			if (breakInCorners) {

			}

			int posX = lowerX - character.characterWidth / 2 + x;
			int posY = lowerY - character.characterHeight / 2 + y;
			if (isTileBlocking(sf::Vector2i(posX, posY))) return false;
		}
	return true;*/
}

bool AStar::PathfindUtils::canMoveToTileWhileWalking(sf::Vector2i startTileId, sf::Vector2i endTileId, NavigationNodeCharacterData character)
{
	if (!canStandOnTile(startTileId, character) || !canStandOnTile(startTileId, character)) return false;
	return canMoveToTile(startTileId, endTileId, character);
}

bool AStar::PathfindUtils::isTileBlocking(sf::Vector2i subTileId)
{
	int x = subTileId.x / 2;
	int y = subTileId.y / 2;

	auto tile = getTile(x, y);
	if (tile == nullptr || tile->isBlocking()) return true;

	return false;
}