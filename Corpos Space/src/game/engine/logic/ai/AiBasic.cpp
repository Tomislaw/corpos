#include "AiBasic.hpp"
#include "game\map\Tilemap.hpp"
#include "game\engine\EntityList.hpp"




AiBasic::AiBasic(Character & character) : character(character)
{
	entityListPtr = character.getEntityListPtr();
	if (entityListPtr != nullptr)tilemapPtr = entityListPtr->getTilemapPtr();
}

void AiBasic::update(float delta)
{
	if (!navigationNodes.empty())
	{
		// delete node if reached

		auto node = &navigationNodes.front();
		if (node->isReached(character))
		{
			navigationNodes.pop();
			if (navigationNodes.empty())
			{
				character.stop();
				return;
			}
			else
			{
				node = &navigationNodes.front();
			}
		}
		
		

		node->timeToSpendOn -= delta;
		//clear queue if reaching takes too much time
		if (node->timeToSpendOn < 0)
		{
			while (!navigationNodes.empty()) navigationNodes.pop();
			character.stop();
			return;
		}

		int type = node->type;

		switch (type)
		{
		case NavNode::WALK:
			if (character.getStandingTileId().x > node->tilePosition.x)
			{
				 character.walkLeft();
			}
			
			if (character.getStandingTileId().x< node->tilePosition.x) 
			{ 
				 character.walkRight();
			}

			if (character.getStandingTileId().x == node->tilePosition.x) 
				character.stop();
			break;
		case NavNode::JUMP:
			if (character.getStandingTileId().x > node->tilePosition.x)
			{
				character.walkLeft();
			}
			
			if (character.getStandingTileId().x< node->tilePosition.x) 
			{ 
				character.walkRight();
			}
			if (character.getStandingTileId().x == node->tilePosition.x) character.stop();
			character.jump();
			break;
		case NavNode::LADDER:
			if (character.getStandingTileId().y > node->tilePosition.y)
				character.walkUp();
			else character.walkDown();
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


	if (navigationNodes.empty())return;

	if (isInitialized == false)
	{
		entityDebugText.setFont(TextContainer::getInstance()->getBasicFont());
		isInitialized = true;
		entityDebugText.setCharacterSize(6);
	}
	
	


	//not efficent, but only used in debug so it is not important
	std::queue<NavNode>test = std::queue<NavNode>(navigationNodes);
	sf::VertexArray line(sf::LinesStrip, 2);

	auto starttile = character.getStandingTileId();
	line[0].position = sf::Vector2f(starttile.x * 32 + 16, starttile.y * 32 + 16);

	while (!test.empty())
	{
		auto tile = test.front().tilePosition;
		line[1].position = sf::Vector2f(tile.x * 32 + 16, tile.y * 32 + 16);

		target.draw(line);

		//draw debug text
		entityDebugText.setPosition(line[1].position);

		switch (test.front().type)
		{
		case NavNode::WALK:
			entityDebugText.setString("walk");
			break;
		case NavNode::JUMP:
			entityDebugText.setString("jump");
			break;
		case NavNode::LADDER:
			entityDebugText.setString("ladder");
			break;
		default:
			entityDebugText.setString("ERROR");
			break;
		}
		target.draw(entityDebugText);

		line[0].position = line[1].position;

		test.pop();
	}
}
