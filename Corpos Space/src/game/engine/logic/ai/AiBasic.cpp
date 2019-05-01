#include "AiBasic.hpp"
#include "game\map\Tilemap.h"
#include "game\engine\EntityList.hpp"

using namespace corpos;

AiBasic::AiBasic(Character & character) : character(character)
{
	entityListPtr = character.getEntityListPtr();
	if (entityListPtr != nullptr)tilemapPtr = entityListPtr->getTileMapPtr();
}

void AiBasic::update(float delta)
{
	if (action != nullptr) {
		action->update(delta);
		if (action->status() != AiAction::NOT_FINISHED) action = nullptr;
	}
}

AiBasic::~AiBasic()
{
	if (action != nullptr)action->stop();
}

void AiBasic::drawDebugData(sf::RenderTarget & target)
{
	if (action != nullptr)action->drawDebugData(target);
}

void MoveToTile::drawDebugData(sf::RenderTarget & target)
{
	if (!isRouteCalculated) return;

	auto debugColor = sf::Color::Red;

	sf::Text entityDebugText;

	entityDebugText.setFont(TextContainer::getInstance()->getBasicFont());
	entityDebugText.setColor(sf::Color::Red);
	entityDebugText.setCharacterSize(6);

	sf::VertexArray line(sf::LinesStrip, 2);

	auto starttile = character.getStandingTileId() * 2;
	line[0].position = sf::Vector2f(starttile.x * TILE_SIZE / 2, starttile.y * TILE_SIZE / 2);

	for each (auto node in path)
	{
		auto tile = node.coordinates;
		line[1].position = sf::Vector2f(tile.x * TILE_SIZE / 2, tile.y * TILE_SIZE / 2);

		//draw debug text
		entityDebugText.setPosition(line[1].position);
		switch (node.type)
		{
		case AStar::Node::WALK:
			entityDebugText.setString("walk");
			debugColor = sf::Color::White;
			break;
		case AStar::Node::JUMP:
			entityDebugText.setString("jump");
			debugColor = sf::Color::Blue;
			break;
		case AStar::Node::AFTER_JUMP:
			entityDebugText.setString("after_jump");
			debugColor = sf::Color::Cyan;
			break;
		case  AStar::Node::BEFORE_JUMP:
			entityDebugText.setString("before_jump");
			debugColor = sf::Color::Red;
			break;
		case  AStar::Node::CENTER_POSITION:
			entityDebugText.setString("center_position");
			debugColor = sf::Color::Red;
			break;
		case AStar::Node::CLIMB:
			entityDebugText.setString("climb");
			debugColor = sf::Color::Green;
			break;
		case  AStar::Node::FLY:
			entityDebugText.setString("fly");
			debugColor = sf::Color::Yellow;
			break;
		case  AStar::Node::FALL:
			entityDebugText.setString("fall");
			debugColor = sf::Color::Magenta;
			break;
		default:
			entityDebugText.setString("ERROR");
			debugColor = sf::Color::Red;
			break;
		}
		line[0].color = debugColor;
		line[1].color = debugColor;
		entityDebugText.setColor(debugColor);
		target.draw(line);
		target.draw(entityDebugText);

		line[0].position = line[1].position;
	}
}

void AiBasic::moveToTile(sf::Vector2i tile)
{
}

void AiBasic::getPath(sf::Vector2i tile)
{
	if (!character.isStanding())return;
	if (action != nullptr)action->stop();
	action = std::make_shared<MoveToTile>(character, tile);
	action->start();
}