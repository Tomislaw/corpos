#include "Node.hpp"
#include <algorithm>
#include "game\map\MapTile\MapTile.hpp"

using namespace std::placeholders;
using namespace AStar;

GetTile PathfindUtils::getTile = nullptr;

Node::Node(sf::Vector2i coordinates_, Node *parent_, int type, int fallDistanceLeft, int jumpDistanceLeft)
{
	parent = parent_;
	coordinates = coordinates_;
	G = H = F = 0;
	this->type = type;
	this->fallDistanceLeft = fallDistanceLeft;
	this->jumpDistanceLeft = jumpDistanceLeft;
}

AStar::Node::Node(sf::Vector2f pos, Node * parent_)
{
	coordinates = sf::Vector2i(pos.x / (TILE_SIZE)*2, pos.y / (TILE_SIZE)*2);
	F = G = H = 0;
	type = Type::WALK;
	jumpDistanceLeft = 0;
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

sf::Vector2f AStar::Node::getPosition()
{
	return sf::Vector2f(coordinates.x * TILE_SIZE/2, coordinates.y * TILE_SIZE / 2);
}

bool AStar::Node::isReached(Character & character)
{
	auto charPos =  character.getCenteredPosition();
	auto pos = getPosition();

	int horizontalRange = TILE_SIZE / 2;
	int verticalBottomRange = 0;
	int verticalToppRange = 0;
	switch (type) {
	FALL:
		horizontalRange = TILE_SIZE;
		verticalBottomRange = TILE_SIZE * 4;
		verticalToppRange = TILE_SIZE * 2;
		break;
	JUMP:
	AFTER_JUMP:
		verticalBottomRange = TILE_SIZE ;
		verticalToppRange = TILE_SIZE * 1.5;
		break;
	default:
		verticalBottomRange = TILE_SIZE/2;
		verticalToppRange = TILE_SIZE;
		break;
	}
	return (pos.x - horizontalRange < charPos.x && charPos.x < pos.x + horizontalRange)
		&& (pos.y - verticalBottomRange < charPos.y && charPos.y < pos.y + verticalToppRange);

}

std::vector<Node> AStar::GroundWalkingSucessors::getSuccesors(Node * node, NavigationNodeCharacterData &character)
{
	auto succesors = std::vector<Node>();
	if (node == nullptr)return succesors;

	auto parentCoord = sf::Vector2i(-1, -1);

	if (node->parent != nullptr) {
		parentCoord = node->parent->coordinates;
	};

	if (node->type == Node::Type::WALK) {
		for (int x = -1; x <= 1; x++)
		{
			if (x == 0)continue;
			for (int y = -1; y <= 1; y++) {
				auto newCoord = sf::Vector2i(x + node->coordinates.x, y + node->coordinates.y);

				if (newCoord == parentCoord)continue;
				if (!PathfindUtils::canMoveToTile(node->coordinates, newCoord, character)) continue;

				int type = Node::Type::FALL;
				if (PathfindUtils::canStandOnTile(newCoord, character)) type = Node::Type::WALK;
				else if (y == 1) continue;

				succesors.push_back(Node(newCoord, node, type));
			}
		}
	}
	else if (node->type == Node::Type::FALL) {

		if (node->fallDistanceLeft <= 0) {
			auto newCoord = sf::Vector2i(node->coordinates.x, node->coordinates.y + 1);

			if (!PathfindUtils::canMoveToTile(node->coordinates, newCoord, character)) return succesors;

			int type = Node::Type::FALL;
			if (PathfindUtils::canStandOnTile(newCoord, character)) type = Node::Type::WALK;

			succesors.push_back(Node(newCoord, node, type, node->fallDistanceLeft--));
		}else {
			for (int x = -1; x <= 1; x++) {
				auto newCoord = sf::Vector2i(node->coordinates.x + x, node->coordinates.y + 1);

				if (!PathfindUtils::canMoveToTile(node->coordinates, newCoord, character)) continue;
				int type = Node::Type::FALL;
				if (PathfindUtils::canStandOnTile(newCoord, character)) type = Node::Type::WALK;
				succesors.push_back(Node(newCoord, node, type));
			}
		}
	}

	return succesors;
}

std::vector<Node> AStar::GroundJumpingSucessors::getSuccesors(Node * node, NavigationNodeCharacterData &character)
{
	auto succesors = GroundWalkingSucessors::getSuccesors(node,character);
	if (node == nullptr)return succesors;

	auto parentCoord = sf::Vector2i(-1, -1);

	if (node->parent != nullptr) {
		parentCoord = node->parent->coordinates;
	};

	if (node->type == Node::Type::WALK) {
		for (int x = -1; x <= 1; x++)
			for (int y = -1; y <= 0; y++) {
				if (x == 0)continue;
				auto newCoord = sf::Vector2i(x + node->coordinates.x, y + node->coordinates.y);
				if (newCoord == parentCoord)continue;
				if (!PathfindUtils::canMoveToTile(node->coordinates, newCoord, character)) continue;
				succesors.push_back(Node(newCoord, node, Node::Type::JUMP, node->fallDistanceLeft, 3));
			}
	}
	else if (node->type == Node::Type::JUMP || node->type == Node::Type::AFTER_JUMP) {
		if (node->jumpDistanceLeft <= 0) {
			for (int x = -1; x <= 1; x++)
				for (int y = 0; y <= 1; y++) {
					auto newCoord = sf::Vector2i(x + node->coordinates.x, y + node->coordinates.y);
					if (newCoord == parentCoord)continue;

					if (!PathfindUtils::canMoveToTile(node->coordinates, newCoord, character)) continue;
					int type = Node::Type::FALL;
					if (PathfindUtils::canStandOnTile(newCoord, character)) type = Node::Type::WALK;
					succesors.push_back(Node(newCoord, node, type, node->fallDistanceLeft, 3));
				}
		}
		else {
			for (int x = -1; x <= 1; x++) {
				auto newCoord = sf::Vector2i(x + node->coordinates.x, node->coordinates.y - 1);
				if (!PathfindUtils::canMoveToTile(node->coordinates, newCoord, character)) continue;

				succesors.push_back(Node(newCoord, node, Node::Type::AFTER_JUMP, node->fallDistanceLeft, node->jumpDistanceLeft--));
			}
		}
	}

	return succesors;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// Pathfinding utils                  ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AStar::PathfindUtils::canFitInTile(sf::Vector2i tileId, NavigationNodeCharacterData &character)
{
	for (int x = 0; x < character.characterWidth; x++)
		for (int y = 0; y < character.characterHeight; y++) {
			int posX = tileId.x + x - character.characterWidth/2 +1;
			int posY = tileId.y - y;
			if (isTileBlocking(sf::Vector2i(posX, posY))) return false;
		}
	return true;
	/*
	bool canFitVerticaly = false;
	bool canFiHorizontaly = false;

	for (int x = 0; x < character.characterWidth; x++)
		for (int y = 0; y < character.characterHeight; y++) {
			int posX = (tileId.x - character.characterWidth + x)/2;
			int posY = (tileId.y - character.characterHeight + y)/2;
			if (isTileBlocking(sf::Vector2i(posX, posY))) return false;
		}

	return true;*/
}

bool AStar::PathfindUtils::canStandOnTile(sf::Vector2i tileId, NavigationNodeCharacterData &character)
{
	for (int x = 0; x < character.characterWidth; x++) {
		int posX = tileId.x - character.characterWidth / 2 + x;
		if (isTileBlocking(sf::Vector2i(posX, tileId.y+1))) return true;
	}

	return false;
}

bool AStar::PathfindUtils::canMoveToTile(sf::Vector2i startTileId, sf::Vector2i endTileId, NavigationNodeCharacterData &character)
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

bool AStar::PathfindUtils::canMoveToTileWhileWalking(sf::Vector2i startTileId, sf::Vector2i endTileId, NavigationNodeCharacterData &character)
{
	if (!canStandOnTile(startTileId, character) || !canStandOnTile(startTileId, character)) return false;
	return canMoveToTile(startTileId, endTileId, character);
}

bool AStar::PathfindUtils::isTileBlocking(sf::Vector2i subTileId)
{
	int x = subTileId.x / 2;
	int y = subTileId.y/2;

	auto tile = getTile(x, y);
	if (tile == nullptr || tile->isBlocking()) return true;

	return false;
}