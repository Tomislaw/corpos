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


		int type = node->type;

		switch (type)
		{
		case NavigationNode::MOVE_LEFT:
			character.walkLeft();
			break;
		case NavigationNode::MOVE_RIGHT:
			character.walkRight();
			break;
		case NavigationNode::MOVE_UP:
			break;
		case NavigationNode::MOVE_DOWN:
			break;
		case NavigationNode::JUMP:
			character.jump();
			break;
		default:
			//navigationNodes.p
			break;
		}
		

		if (node->isReached(character))
		{
			navigationNodes.pop();
			std::cout << "Nav passed ";
			if (navigationNodes.empty())
			{
				character.stop();
				std::cout << "Stop ";
			}
		}

		node->timeToSpendOn -= delta;
		//clear queue if reaching takes too much time
		if (node->timeToSpendOn < 0)
		{
			while (!navigationNodes.empty()) navigationNodes.pop();
		}

	}
}

AiBasic::~AiBasic()
{
}
