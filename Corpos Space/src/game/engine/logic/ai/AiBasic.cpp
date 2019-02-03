#include "AiBasic.hpp"
#include "game\map\Tilemap.h"
#include "game\engine\EntityList.hpp"

AiBasic::AiBasic(Character & character) : character(character)
{
	entityListPtr = character.getEntityListPtr();
	if (entityListPtr != nullptr)tilemapPtr = entityListPtr->getTileMapPtr();
}

void AiBasic::update(float delta)
{
	if (!path.empty())
	{
		// delete node if reached

		auto node = &path.front();
		if (node->isReached(character))
		{
			path.pop_front();
			if (path.empty())
			{
				character.stop();
				return;
			}
			else
			{
				node = &path.front();
			}
		}

		node->timeSpend -= delta;
		//clear queue if reaching takes too much time
		if (node->timeSpend < 0)
		{
			while (!path.empty()) path.pop_front();
			character.stop();
			return;
		}

		int type = node->type;

		switch (type)
		{
		case AStar::Node::WALK:
		case AStar::Node::BEFORE_JUMP:
		case AStar::Node::CENTER_POSITION:
			if (character.isStanding())
			{
				if (character.getStandingTileId().x > node->coordinates.x/2)
					character.walkLeft();
				else if (character.getStandingTileId().x < node->coordinates.x/2)
					character.walkRight();
			}
			else
			{
				float xpos = character.getCenteredPosition().x + character.getVelocity().x * delta * 10;
				if (xpos < node->coordinates.x/2 * TILE_SIZE)character.walkRight();
				else if (xpos > node->coordinates.x/2 * TILE_SIZE + TILE_SIZE)character.walkLeft();
				else if (character.getStandingTileId().x > node->coordinates.x/2)
					character.walkLeft();
				else if (character.getStandingTileId().x < node->coordinates.x/2)
					character.walkRight();
			}
			break;
		case AStar::Node::FALL:
		case AStar::Node::AFTER_JUMP:

			if (character.getStandingTileId().x > node->coordinates.x/2)
				character.walkLeft();
			else if (character.getStandingTileId().x < node->coordinates.x/2)
				character.walkRight();

			break;

		case NavNode::JUMP:
			if (character.isJumping() || character.isStanding())
			{
				if (character.getStandingTileId().x > node->coordinates.x)
				{
					character.walkLeft();
				}

				if (character.getStandingTileId().x < node->coordinates.x)
				{
					character.walkRight();
				}
			}

			character.jump();
			break;

		default:
			//navigationNodes.p
			break;
		}
	}
}

AiBasic::~AiBasic()
{
}

void AiBasic::drawDebugData(sf::RenderTarget & target)
{
	if (path.empty()) {
		auto a = character.getNavigationNodeCharacterData();
		auto b = AStar::Node(character.getCenteredPosition());
		auto c = AStar::GroundWalkingSucessors().getSuccesors(&b,a);

		Logger::d("",c);
		
		return;
	}


	auto debugColor = sf::Color::Red;

	if (isInitialized == false)
	{
		entityDebugText.setFont(TextContainer::getInstance()->getBasicFont());
		entityDebugText.setColor(sf::Color::Red);
		isInitialized = true;
		entityDebugText.setCharacterSize(6);
	}

	sf::VertexArray line(sf::LinesStrip, 2);

	auto starttile = character.getStandingTileId()*2;
	line[0].position = sf::Vector2f(starttile.x * TILE_SIZE/2 + TILE_SIZE/4, starttile.y * TILE_SIZE/2 + TILE_SIZE/4);

	for each (auto node in path)
	{
		auto tile = node.coordinates;
		line[1].position = sf::Vector2f(tile.x * TILE_SIZE/2 + TILE_SIZE/4, tile.y * TILE_SIZE/2 + TILE_SIZE/4);

		

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

void AiBasic::getPath(sf::Vector2i tile)
{
	if (!character.isStanding())return;
	AStar::Node startNode(character.getCenteredPosition());
	
	path = pathfind.findPath(startNode, tile*2);
}