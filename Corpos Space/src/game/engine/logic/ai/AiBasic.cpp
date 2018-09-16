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
				if (character.getStandingTileId().x > node->coordinates.x)
					character.walkLeft();
				else if (character.getStandingTileId().x < node->coordinates.x)
					character.walkRight();
			}
			else
			{
				float xpos = character.getCenteredPosition().x + character.getVelocity().x * delta * 10;
				if(xpos < node->coordinates.x * 32)character.walkRight();
				else if (xpos > node->coordinates.x * 32 +32 )character.walkLeft();
				else if (character.getStandingTileId().x > node->coordinates.x)
					character.walkLeft();
				else if (character.getStandingTileId().x < node->coordinates.x)
					character.walkRight();
			}
			break;
		case AStar::Node::FALL:
		case AStar::Node::AFTER_JUMP:

				if (character.getStandingTileId().x > node->coordinates.x)
					character.walkLeft();
				else if (character.getStandingTileId().x < node->coordinates.x)
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


	if (path.empty())return;

	if (isInitialized == false)
	{
		entityDebugText.setFont(TextContainer::getInstance()->getBasicFont());
		entityDebugText.setColor(sf::Color::Red);
		isInitialized = true;
		entityDebugText.setCharacterSize(6);
	}
	
	
	sf::VertexArray line(sf::LinesStrip, 2);

	auto starttile = character.getStandingTileId();
	line[0].position = sf::Vector2f(starttile.x * 32 + 16, starttile.y * 32 + 16);

	for each (auto node in path)
	{
		auto tile = node.coordinates;
		line[1].position = sf::Vector2f(tile.x * 32 + 16, tile.y * 32 + 16);

		target.draw(line);

		//draw debug text
		entityDebugText.setPosition(line[1].position);
		switch (node.type)
		{
		case AStar::Node::WALK:
			entityDebugText.setString("walk");
			break;
		case AStar::Node::JUMP:
			entityDebugText.setString("jump");
			break;
		case AStar::Node::AFTER_JUMP:
			entityDebugText.setString("after_jump");
			break;
		case  AStar::Node::BEFORE_JUMP:
			entityDebugText.setString("before_jump");
			break;
		case  AStar::Node::CENTER_POSITION:
			entityDebugText.setString("center_position");
			break;
		case AStar::Node::CLIMB:
			entityDebugText.setString("climb");
			break;
		case  AStar::Node::FLY:
			entityDebugText.setString("fly");
			break;
		case  AStar::Node::FALL:
			entityDebugText.setString("fall");
			break;
		default:
			entityDebugText.setString("ERROR");
			break;
		}
		target.draw(entityDebugText);

		line[0].position = line[1].position;

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


		path = pathfind.findPath(startNode, tile);


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
