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


			if (false)
			{

				if (character.getCenteredPosition().x > node->tilePosition.x * 32+16)
				{
					character.walkLeft();
				}
				else if (character.getCenteredPosition().x < node->tilePosition.x * 32+16)
				{
					character.walkRight();
				}

				if (character.getCenteredPosition().y + character.getVelocity().y > node->tilePosition.y * 32 + 32)
				{
					if (character.getCenteredPosition().x + character.getVelocity().x> node->tilePosition.x * 32 + 16)
					{
						character.walkLeft();
					}
					else if (character.getCenteredPosition().x + character.getVelocity().x< node->tilePosition.x * 32 + 16)
					{
						character.walkRight();
					}
				}

			}
			//	character.stop();



			if (character.getCenteredPosition().x > node->tilePosition.x)
			{
				 character.walkLeft();
			}
			
			if (character.getStandingTileId().x< node->tilePosition.x) 
			{ 
				 character.walkRight();
			}

			//if (character.getStandingTileId().x == node->tilePosition.x) 
				//character.stop();
			break;
		case NavNode::JUMP:
			if (character.isJumping() || character.isStanding())
			{
				if (character.getStandingTileId().x > node->tilePosition.x)
				{
					character.walkLeft();
				}

				if (character.getStandingTileId().x < node->tilePosition.x)
				{
					character.walkRight();
				}
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

		switch (test.front().debugType)
		{
		case NavigationNode::WALK:
			entityDebugText.setString("walk");
			break;
		case NavigationNode::JUMP:
			entityDebugText.setString("jump");
			break;
		case NavigationNode::AFTER_JUMP:
			entityDebugText.setString("after_jump");
			break;
		case NavigationNode::BEFORE_JUMP:
			entityDebugText.setString("before_jump");
			break;
		case NavigationNode::CENTER_POSITION:
			entityDebugText.setString("center_position");
			break;
		case NavigationNode::CLIMB:
			entityDebugText.setString("climb");
			break;
		case NavigationNode::FLY:
			entityDebugText.setString("fly");
			break;
		case NavigationNode::FALL:
			entityDebugText.setString("fall");
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

void AiBasic::getPath(sf::Vector2i tile)
{
		AStar::Node startNode(character.getStandingTileId());

		if (character.getNavigationNodeCharacterData().isFlyingOne)
		{
			startNode.type = AStar::Node::FLY;
		}
		else
		{
			if (!character.isStanding())return;

			startNode.type = AStar::Node::WALK;

		}


		auto p = pathfind.findPath(startNode, tile);
		
		for each (auto var in p)
		{
			if (var->type == NavigationNode::WALK || var->type == NavigationNode::FALL || var->type == NavigationNode::BEFORE_JUMP || var->type == NavigationNode::AFTER_JUMP)
			{
				addNode(var->coordinates, NavNode::WALK);
				navigationNodes.back().debugType = var->type;
			}
			else if (var->type == NavigationNode::JUMP)
			{
				addNode(var->coordinates, NavNode::JUMP);
				navigationNodes.back().debugType = var->type;
			}
		}
		pathfind.releaseNodes();
		return;

		/*std::vector<sf::Vector2i> path;


		auto tilePtr = character.getTilemapPtr();
		if (tilePtr == nullptr)return;

		auto getTile = [&](sf::Vector2i id) { return tilePtr->getTile(id); };

		unsigned int SearchCount = 0;

		const unsigned int NumSearches = 1;

		while (SearchCount < NumSearches)
		{

			// Create a start state
			NavigationNode nodeStart;
			nodeStart.x = character.getStandingTileId().x;
			nodeStart.y = character.getStandingTileId().y;
			nodeStart.setCharacterData(&character.getNavigationNodeCharacterData());
			nodeStart.setFunctionGetTile(std::bind(getTile, std::placeholders::_1));


			if (character.getNavigationNodeCharacterData().isFlyingOne)
			{
				nodeStart.type = NavigationNode::FLY;
			}
			else
			{
				if (!character.isStanding())return;

				nodeStart.type = NavigationNode::WALK;

			}

			// Define the goal state
			NavigationNode nodeEnd;
			nodeEnd.x = tile.x;
			nodeEnd.y = tile.y;
			nodeEnd.type = NavigationNode::WALK;
			nodeEnd.setCharacterData(&character.getNavigationNodeCharacterData());
			nodeEnd.setFunctionGetTile(std::bind(getTile, std::placeholders::_1));

			if (!nodeEnd.canMoveToTile(tile.x, tile.y))
			{
				std::cout << "Cant fit here" << std::endl;
				return;
			}


			// Set Start and goal states

			astarsearch.SetStartAndGoalStates(nodeStart, nodeEnd);

			unsigned int SearchState;
			unsigned int SearchSteps = 0;

			do
			{
				SearchState = astarsearch.SearchStep();

				SearchSteps++;



			} while (SearchState == AStarSearch<NavigationNode>::SEARCH_STATE_SEARCHING);

			if (SearchState == AStarSearch<NavigationNode>::SEARCH_STATE_SUCCEEDED)
			{
				//	cout << "Search found goal state\n";

				NavigationNode *node = astarsearch.GetSolutionStart();

				int steps = 0;

				//	node->PrintNodeInfo();
				path.push_back(sf::Vector2i(node->x, node->y));

				for (;; )
				{
					node = astarsearch.GetSolutionNext();

					if (!node)
					{
						break;
					}

					path.push_back(sf::Vector2i(node->x, node->y));

					node->PrintNodeInfo();
					int t = 0;
					if (node->type == NavigationNode::WALK || node->type == NavigationNode::FALL || node->type == NavigationNode::BEFORE_JUMP || node->type == NavigationNode::AFTER_JUMP)
					{
						addNode(sf::Vector2i(node->x, node->y),NavNode::WALK);
						navigationNodes.back().debugType = node->type;
					}
					else if (node->type == NavigationNode::JUMP)
					{
						addNode(sf::Vector2i(node->x, node->y), NavNode::JUMP);
						navigationNodes.back().debugType = node->type;
					}
					
						//node->PrintNodeInfo();
					steps++;

				};

				//cout << "Solution steps " << steps << endl;

				// Once you're done with the solution you can free the nodes up
				astarsearch.FreeSolutionNodes();


			}
			else if (SearchState == AStarSearch<NavigationNode>::SEARCH_STATE_FAILED)
			{
				//	cout << "Search terminated. Did not find goal state\n";

			}

			// Display the number of loops the search went through
			//cout << "SearchSteps : " << SearchSteps << "\n";

			SearchCount++;

			astarsearch.EnsureMemoryFreed();
		}



		//return path;*/

}
