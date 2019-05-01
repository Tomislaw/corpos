#include "NavigationNode.hpp"

using namespace corpos;

Tile * NavigationNode::GetTile(int x, int y)
{
	return getTile(sf::Vector2i(x, y));
}

bool NavigationNode::IsSameState(NavigationNode &rhs)
{
	// same state in a maze search is simply when (x,y) are the same
	if ((x == rhs.x) &&
		(y == rhs.y) && rhs.type == type)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void NavigationNode::PrintNodeInfo()
{
	std::string str = "";
	switch (type)
	{
	case NavigationNode::JUMP:
		str = "JUMP";
		break;
	case NavigationNode::FALL:
		str = "FALL";
		break;
	case NavigationNode::AFTER_JUMP:
		str = "AFTER_JUMP";
		break;
	case NavigationNode::WALK:
		str = "WALK";
		break;
	case NavigationNode::FLY:
		str = "FLY";
		break;
	case NavigationNode::CLIMB:
		str = "CLIMB";
		break;
	default:
		str = "ERROR";
		break;
	}
	std::cout << str + " : " << x << " " << y << "\n";
}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal.

float NavigationNode::GoalDistanceEstimate(NavigationNode &nodeGoal)
{
	return fabsf(x - nodeGoal.x) + fabsf(y - nodeGoal.y);
}

bool NavigationNode::IsGoal(NavigationNode &nodeGoal)
{
	if ((x == nodeGoal.x) &&
		(y == nodeGoal.y))
	{
		return true;
	}

	return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool NavigationNode::GetSuccessors(AStarSearch<NavigationNode> *astarsearch, NavigationNode *parent_node)
{
	if (data == nullptr)return false;
	if (data->isFlyingOne)
		return GetSuccesorsAirNode(astarsearch, parent_node);
	else return GetSuccesorsGroundNode(astarsearch, parent_node);
}

bool NavigationNode::GetSuccesorsGroundNode(AStarSearch<NavigationNode>* astarsearch, NavigationNode * parent_node)
{
	int parent_x = -1;
	int parent_y = -1;

	if (parent_node)
	{
		if (parent_node->type != CENTER_POSITION)
		{
			//parent_x = parent_node->x;
			//parent_y = parent_node->y;
		}
	}
	else
	{
		if (!canWalkToTile(x, y))
		{
			type = NavigationNode::CENTER_POSITION;
			NavigationNode NewNode;

			//LEFT
			if (canMoveToTile(x - 1, y) && canWalkToTile(x - 1, y))
			{
				NewNode = NavigationNode(x - 1, y);
				NewNode.setFunctionGetTile(getTile);
				NewNode.setCharacterData(data);
				NewNode.type = NavigationNode::WALK;
				astarsearch->AddSuccessor(NewNode);
			}
			//RIGHT

			if (canMoveToTile(x + 1, y) && canWalkToTile(x + 1, y))
			{
				NewNode = NavigationNode(x + 1, y);
				NewNode.setFunctionGetTile(getTile);
				NewNode.setCharacterData(data);
				NewNode.type = NavigationNode::WALK;
				astarsearch->AddSuccessor(NewNode);
			}
			return true;
		}
	}

	NavigationNode NewNode;
	// Normal walking
	if (type == NavigationNode::WALK)
	{
		//LEFT
		if (!((parent_x == x - 1) && (parent_y == y)))
		{
			if (canMoveToTile(x - 1, y))
			{
				NewNode = NavigationNode(x - 1, y);
				NewNode.setFunctionGetTile(getTile);
				NewNode.setCharacterData(data);
				if (canWalkToTile(x - 1, y))
				{
					NewNode.type = NavigationNode::WALK;
					astarsearch->AddSuccessor(NewNode);
				}

				else
				{
					if (data->characterWidth == 1)
					{
						NewNode.type = NavigationNode::FALL;
						NewNode.jumpDistancePassed = data->characterJumpHeight + 1;
						astarsearch->AddSuccessor(NewNode);
						NewNode.type = NavigationNode::BEFORE_JUMP;
						NewNode.jumpDistancePassed = 0;
						astarsearch->AddSuccessor(NewNode);
					}
				}
				//astarsearch->AddSuccessor(NewNode);
			}
		}
		//RIGHT
		if (!((parent_x == x + 1) && (parent_y == y)))
		{
			if (canMoveToTile(x + 1, y))
			{
				NewNode = NavigationNode(x + 1, y);
				NewNode.setFunctionGetTile(getTile);
				NewNode.setCharacterData(data);
				if (canWalkToTile(x + 1, y))
				{
					NewNode.type = NavigationNode::WALK;
					astarsearch->AddSuccessor(NewNode);
				}
				else
				{
					if (data->characterWidth == 1)
					{
						NewNode.type = NavigationNode::FALL;
						NewNode.jumpDistancePassed = data->characterJumpHeight + 1;
						astarsearch->AddSuccessor(NewNode);
						NewNode.type = NavigationNode::BEFORE_JUMP;
						NewNode.jumpDistancePassed = 0;
						astarsearch->AddSuccessor(NewNode);
					}
				}
			}

			// RIGHT BOTTOM
			if (!((parent_x == x + 1) && (parent_y == y + 1)))
			{
				if (canMoveToTile(x + 1, y + 1))
				{
					NewNode = NavigationNode(x + 1, y + 1);
					NewNode.setFunctionGetTile(getTile);
					NewNode.setCharacterData(data);
					if (canWalkToTile(x + 1, y + 1))
						NewNode.type = NavigationNode::WALK;
					else
					{
						NewNode.type = NavigationNode::FALL;
						NewNode.jumpDistancePassed = jumpDistancePassed + 2;
					}
					astarsearch->AddSuccessor(NewNode);
				}
			}

			// LEFT BOTTOM
			if (!((parent_x == x - 1) && (parent_y == y + 1)))
			{
				if (canMoveToTile(x - 1, y + 1))
				{
					NewNode = NavigationNode(x - 1, y + 1);
					NewNode.setFunctionGetTile(getTile);
					NewNode.setCharacterData(data);
					if (canWalkToTile(x - 1, y + 1))
						NewNode.type = NavigationNode::WALK;
					else
					{
						NewNode.type = NavigationNode::FALL;
						NewNode.jumpDistancePassed = jumpDistancePassed + 2;
					}
					astarsearch->AddSuccessor(NewNode);
				}
			}
		}

		//TOP
		if (!((parent_x == x) && (parent_y == y - 1)))
		{
			if (canMoveToTile(x, y - 1))
			{
				NewNode = NavigationNode(x, y - 1);
				NewNode.setFunctionGetTile(getTile);
				NewNode.setCharacterData(data);
				NewNode.type = NavigationNode::JUMP;
				NewNode.jumpDistancePassed = 1;
				astarsearch->AddSuccessor(NewNode);
			}
		}

		//LEFT TOP
		if (!((parent_x == x - 1) && (parent_y == y - 1)))
		{
			if (canMoveToTile(x - 1, y - 1))
			{
				NewNode = NavigationNode(x - 1, y - 1);
				NewNode.setFunctionGetTile(getTile);
				NewNode.setCharacterData(data);
				NewNode.type = NavigationNode::JUMP;
				NewNode.jumpDistancePassed = 1;
				astarsearch->AddSuccessor(NewNode);
			}
		}

		//RIGHT TOP
		if (!((parent_x == x + 1) && (parent_y == y - 1)))
		{
			if (canMoveToTile(x + 1, y - 1))
			{
				NewNode = NavigationNode(x + 1, y - 1);
				NewNode.setFunctionGetTile(getTile);
				NewNode.setCharacterData(data);
				NewNode.type = NavigationNode::JUMP;
				NewNode.jumpDistancePassed = 1;
				astarsearch->AddSuccessor(NewNode);
			}
		}
	}
	//only for 1 width characters
	if (type == NavigationNode::BEFORE_JUMP)
	{
		//TOP
		if (!((parent_x == x) && (parent_y == y - 1)))
		{
			if (canMoveToTile(x, y - 1))
			{
				NewNode = NavigationNode(x, y - 1);
				NewNode.setFunctionGetTile(getTile);
				NewNode.setCharacterData(data);
				NewNode.type = NavigationNode::JUMP;
				NewNode.jumpDistancePassed = 1;
				astarsearch->AddSuccessor(NewNode);
			}
		}

		//LEFT TOP
		if (!((parent_x == x - 1) && (parent_y == y - 1)))
		{
			if (canMoveToTile(x - 1, y - 1))
			{
				NewNode = NavigationNode(x - 1, y - 1);
				NewNode.setFunctionGetTile(getTile);
				NewNode.setCharacterData(data);
				NewNode.type = NavigationNode::JUMP;
				NewNode.jumpDistancePassed = 1;
				astarsearch->AddSuccessor(NewNode);
			}
		}

		//RIGHT TOP
		if (!((parent_x == x + 1) && (parent_y == y - 1)))
		{
			if (canMoveToTile(x + 1, y - 1))
			{
				NewNode = NavigationNode(x + 1, y - 1);
				NewNode.setFunctionGetTile(getTile);
				NewNode.setCharacterData(data);
				NewNode.type = NavigationNode::JUMP;
				NewNode.jumpDistancePassed = 1;
				astarsearch->AddSuccessor(NewNode);
			}
		}
	}
	// while jumping
	if (type == NavigationNode::JUMP || type == NavigationNode::AFTER_JUMP)
	{
		// while increasing height
		if (jumpDistancePassed != data->characterJumpHeight)
		{
			//TOP
			if (!((parent_x == x) && (parent_y == y - 1)))
			{
				if (canMoveToTile(x, y - 1))
				{
					NewNode = NavigationNode(x, y - 1);
					NewNode.setFunctionGetTile(getTile);
					NewNode.setCharacterData(data);
					NewNode.type = NavigationNode::AFTER_JUMP;
					NewNode.jumpDistancePassed = jumpDistancePassed + 1;
					astarsearch->AddSuccessor(NewNode);
				}
			}
			//LEFT TOP
			if (!((parent_x == x - 1) && (parent_y == y - 1)))
			{
				if (canMoveToTile(x - 1, y - 1))
				{
					NewNode = NavigationNode(x - 1, y - 1);
					NewNode.setFunctionGetTile(getTile);
					NewNode.setCharacterData(data);
					NewNode.type = NavigationNode::AFTER_JUMP;
					NewNode.jumpDistancePassed = jumpDistancePassed + 1;
					astarsearch->AddSuccessor(NewNode);
				}
			}

			//RIGHT TOP
			if (!((parent_x == x + 1) && (parent_y == y - 1)))
			{
				if (canMoveToTile(x + 1, y - 1))
				{
					NewNode = NavigationNode(x + 1, y - 1);
					NewNode.setFunctionGetTile(getTile);
					NewNode.setCharacterData(data);
					NewNode.type = NavigationNode::AFTER_JUMP;
					NewNode.jumpDistancePassed = jumpDistancePassed + 1;
					astarsearch->AddSuccessor(NewNode);
				}
			}
		}
		else //while at top
		{
			//BOTTOM
			if (!((parent_x == x) && (parent_y == y + 1)))
			{
				if (canMoveToTile(x, y + 1))
				{
					NewNode = NavigationNode(x, y + 1);
					NewNode.setFunctionGetTile(getTile);
					NewNode.setCharacterData(data);
					if (canWalkToTile(x, y + 1))
						NewNode.type = NavigationNode::FALL;
					else
					{
						NewNode.type = NavigationNode::FALL;
						NewNode.jumpDistancePassed = jumpDistancePassed + 1;
					}
					astarsearch->AddSuccessor(NewNode);
				}
			}

			// RIGHT BOTTOM
			if (!((parent_x == x + 1) && (parent_y == y + 1)))
			{
				if (canMoveToTile(x + 1, y + 1))
				{
					NewNode = NavigationNode(x + 1, y + 1);
					NewNode.setFunctionGetTile(getTile);
					NewNode.setCharacterData(data);
					if (canWalkToTile(x + 1, y + 1))
						NewNode.type = NavigationNode::FALL;
					else
					{
						NewNode.type = NavigationNode::FALL;
						NewNode.jumpDistancePassed = jumpDistancePassed + 1;
					}
					astarsearch->AddSuccessor(NewNode);
				}
			}

			// LEFT BOTTOM
			if (!((parent_x == x - 1) && (parent_y == y + 1)))
			{
				if (canMoveToTile(x - 1, y + 1))
				{
					NewNode = NavigationNode(x - 1, y + 1);
					NewNode.setFunctionGetTile(getTile);
					NewNode.setCharacterData(data);
					NewNode.jumpDistancePassed = jumpDistancePassed + 1;
					if (canWalkToTile(x - 1, y + 1))
						NewNode.type = NavigationNode::FALL;
					else
					{
						NewNode.type = NavigationNode::FALL;
						NewNode.jumpDistancePassed = jumpDistancePassed + 1;
					}
					astarsearch->AddSuccessor(NewNode);
				}
			}

			//LEFT
			if (!((parent_x == x - 1) && (parent_y == y)))
			{
				if (canMoveToTile(x - 1, y))
				{
					NewNode = NavigationNode(x - 1, y);
					NewNode.setFunctionGetTile(getTile);
					NewNode.setCharacterData(data);
					if (canWalkToTile(x - 1, y))
					{
						NewNode.type = NavigationNode::WALK;
					}

					else
					{
						NewNode.type = NavigationNode::FALL;
						NewNode.jumpDistancePassed = jumpDistancePassed + 1;
					}
					astarsearch->AddSuccessor(NewNode);
				}
			}
			//RIGHT
			if (!((parent_x == x + 1) && (parent_y == y)))
			{
				if (canMoveToTile(x + 1, y))
				{
					NewNode = NavigationNode(x + 1, y);
					NewNode.setFunctionGetTile(getTile);
					NewNode.setCharacterData(data);
					if (canWalkToTile(x + 1, y))
						NewNode.type = NavigationNode::WALK;
					else
					{
						NewNode.type = NavigationNode::FALL;
						NewNode.jumpDistancePassed = jumpDistancePassed + 1;
					}
					astarsearch->AddSuccessor(NewNode);
				}
			}
		}
	}
	// while failing
	if (type == NavigationNode::FALL)
	{
		//BOTTOM
		if (!((parent_x == x) && (parent_y == y + 1)))
		{
			if (canMoveToTile(x, y + 1))
			{
				NewNode = NavigationNode(x, y + 1);
				NewNode.setFunctionGetTile(getTile);
				NewNode.setCharacterData(data);

				if (canWalkToTile(x, y + 1))
					NewNode.type = NavigationNode::FALL;
				else
				{
					NewNode.type = NavigationNode::FALL;
					NewNode.jumpDistancePassed = jumpDistancePassed + 1;
				}
				astarsearch->AddSuccessor(NewNode);
			}
		}

		if (jumpDistancePassed < data->characterJumpHeight + 3)// if fall to much, cant go to left and right (to much fall speed)
		{
			// RIGHT BOTTOM
			if (!((parent_x == x + 1) && (parent_y == y + 1)))
			{
				if (canMoveToTile(x + 1, y + 1))
				{
					NewNode = NavigationNode(x + 1, y + 1);
					NewNode.setFunctionGetTile(getTile);
					NewNode.setCharacterData(data);
					if (canWalkToTile(x + 1, y + 1))
						NewNode.type = NavigationNode::FALL;
					else
					{
						NewNode.type = NavigationNode::FALL;
						NewNode.jumpDistancePassed = jumpDistancePassed + 1;
					}
					astarsearch->AddSuccessor(NewNode);
				}
			}

			// LEFT BOTTOM
			if (!((parent_x == x - 1) && (parent_y == y + 1)))
			{
				if (canMoveToTile(x - 1, y + 1))
				{
					NewNode = NavigationNode(x - 1, y + 1);
					NewNode.setFunctionGetTile(getTile);
					NewNode.setCharacterData(data);
					if (canWalkToTile(x - 1, y + 1))
						NewNode.type = NavigationNode::FALL;
					else
					{
						NewNode.type = NavigationNode::FALL;
						NewNode.jumpDistancePassed = jumpDistancePassed + 1;
					}
					astarsearch->AddSuccessor(NewNode);
				}
			}
		}
	}

	return true;
}

bool NavigationNode::GetSuccesorsAirNode(AStarSearch<NavigationNode>* astarsearch, NavigationNode * parent_node)
{
	int parent_x = -1;
	int parent_y = -1;

	if (parent_node)
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}

	NavigationNode NewNode;

	//LEFT
	if (!((parent_x == x - 1) && (parent_y == y)))
	{
		if (canMoveToTile(x - 1, y))
		{
			NewNode = NavigationNode(x - 1, y);
			NewNode.setFunctionGetTile(getTile);
			NewNode.setCharacterData(data);
			NewNode.type = NavigationNode::FLY;
			astarsearch->AddSuccessor(NewNode);
		}
	}

	//TOP
	if (!((parent_x == x) && (parent_y == y - 1)))
	{
		if (canMoveToTile(x, y - 1))
		{
			NewNode = NavigationNode(x, y - 1);
			NewNode.setFunctionGetTile(getTile);
			NewNode.setCharacterData(data);
			NewNode.type = NavigationNode::FLY;
			astarsearch->AddSuccessor(NewNode);
		}
	}

	//RIGHT
	if (!((parent_x == x + 1) && (parent_y == y)))
	{
		if (canMoveToTile(x + 1, y))
		{
			NewNode = NavigationNode(x + 1, y);
			NewNode.setFunctionGetTile(getTile);
			NewNode.setCharacterData(data);
			NewNode.type = NavigationNode::FLY;
			astarsearch->AddSuccessor(NewNode);
		}
	}

	//BOTTOM
	if (!((parent_x == x) && (parent_y == y + 1)))
	{
		if (canMoveToTile(x, y + 1))
		{
			NewNode = NavigationNode(x, y + 1);
			NewNode.setFunctionGetTile(getTile);
			NewNode.setCharacterData(data);
			NewNode.type = NavigationNode::FLY;
			astarsearch->AddSuccessor(NewNode);
		}
	}

	//LEFT TOP
	if (!((parent_x == x - 1) && (parent_y == y - 1)))
	{
		if (canMoveToTile(x - 1, y - 1))
		{
			NewNode = NavigationNode(x - 1, y - 1);
			NewNode.setFunctionGetTile(getTile);
			NewNode.setCharacterData(data);
			NewNode.type = NavigationNode::FLY;
			astarsearch->AddSuccessor(NewNode);
		}
	}

	//RIGHT TOP
	if (!((parent_x == x + 1) && (parent_y == y - 1)))
	{
		if (canMoveToTile(x + 1, y - 1))
		{
			NewNode = NavigationNode(x + 1, y - 1);
			NewNode.setFunctionGetTile(getTile);
			NewNode.setCharacterData(data);
			NewNode.type = NavigationNode::FLY;
			astarsearch->AddSuccessor(NewNode);
		}
	}

	// RIGHT BOTTOM
	if (!((parent_x == x + 1) && (parent_y == y + 1)))
	{
		if (canMoveToTile(x + 1, y + 1))
		{
			NewNode = NavigationNode(x + 1, y + 1);
			NewNode.setFunctionGetTile(getTile);
			NewNode.setCharacterData(data);
			NewNode.type = NavigationNode::FLY;
			astarsearch->AddSuccessor(NewNode);
		}
	}

	// LEFT BOTTOM
	if (!((parent_x == x - 1) && (parent_y == y + 1)))
	{
		if (canMoveToTile(x - 1, y + 1))
		{
			NewNode = NavigationNode(x - 1, y + 1);
			NewNode.setFunctionGetTile(getTile);
			NewNode.setCharacterData(data);
			NewNode.type = NavigationNode::FLY;
			astarsearch->AddSuccessor(NewNode);
		}
	}

	return true;
}

bool NavigationNode::canWalkToTile(int x, int y)
{
	if (data == nullptr)return false;
	int characterWidth = data->characterWidth;

	if (characterWidth <= 1)
	{
		Tile * tile = GetTile(x, y + 1);
		if (tile == nullptr)return false;
		else return tile->isBlocking();
	}
	else
	{
		int sideSize = 0;
		if (characterWidth % 2 == 1) // for 3,5,7,...,2n+1 width characters
		{
			sideSize = (characterWidth - 1) / 2;

			for (int i = x - sideSize; i <= x + sideSize; i++)
			{
				Tile * tile = GetTile(i, y + 1);
				if (tile == nullptr)continue;
				else if (tile->isBlocking())return true;
			}
			return false;
		}
		else // for 2,4,6,...,2n width characters
		{
			sideSize = data->characterWidth / 2;

			int dir = this->x - x;
			if (this->y == y && (dir != 1 || dir != -1))
			{
				int start = x;
				if (dir == 1)start = this->x;

				for (int i = start - sideSize; i < start + sideSize; i++)
				{
					Tile * tile = GetTile(i, y + 1);
					if (tile != nullptr)
						if (tile->isBlocking())return true;
				}
			}
			else
			{
				for (int i = x - sideSize; i <= x + sideSize; i++)
				{
					Tile * tile = GetTile(i, y + 1);
					if (tile == nullptr)continue;
					else if (tile->isBlocking())return true;
				}
				return false;
			}
			return false;
		}
	}
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is
// conceptually where we're moving

bool NavigationNode::canMoveToTile(int x, int y)
{
	if (data == nullptr)
	{
		Logger::e("Data nullpointer in NavigationNode");
		return false;
	}
	int characterWidth = data->characterWidth;
	int characterHeight = data->characterHeight;

	//while moving crosswise
	//if (y != this->y)characterHeight += 1;

	/*
	* Check if can stand here
	*     ><[][]][]
	*     ><><
	* [][][]   [][]
	*/

	// if character have width 1
	if (characterWidth <= 1)
	{
		for (int i = y - characterHeight + 1; i <= y; i++)
		{
			Tile * tile = GetTile(x, i);
			if (tile != nullptr)
			{
				if (tile->isBlocking())return false;
			}
			else return false;
		}
		return true;
	}

	int sideSize = 0;
	if (characterWidth % 2 == 1)
		sideSize = (characterWidth - 1) / 2;
	else
		sideSize = characterWidth / 2;

	for (int i = x - sideSize; i <= x + sideSize; i++)
	{
		for (int j = y - characterHeight + 1; j <= y; j++)
		{
			Tile * tile = GetTile(i, j);
			if (tile != nullptr)
			{
				if (tile->isBlocking())return false;
			}
			else return false;
		}
	}
	return true;
}

float NavigationNode::GetCost(NavigationNode &successor)
{
	if (x == successor.x || y == successor.y)
	{
		return 1;
	}
	return 1.5;
}