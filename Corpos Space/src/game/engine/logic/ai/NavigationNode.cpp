#include "NavigationNode.hpp"



Tile * NavigationNode::GetTile(int x, int y)
{
	return getTile(sf::Vector2i(x, y));
}




bool NavigationNode::IsSameState(NavigationNode &rhs)
{

	// same state in a maze search is simply when (x,y) are the same
	if ((x == rhs.x) &&
		(y == rhs.y))
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
	char str[100];
//	sprintf(str, "Node position : (%d,%d)\n", x, y);

	cout << str;
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

	int parent_x = -1;
	int parent_y = -1;

	if (parent_node)
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}


	NavigationNode NewNode;
	//NewNode.setFunctionGetMap(getMap);

	Tile * tile = nullptr;

	tile = GetTile(x - 1, y);
	// push each possible move except allowing the search to go backwards
	if (tile!=nullptr && !((parent_x == x - 1) && (parent_y == y)))
	{
		if (!tile->isBlocking())
		{
			NewNode = NavigationNode(x - 1, y);
			NewNode.setFunctionGetTile(getTile);
			astarsearch->AddSuccessor(NewNode);
		}

	}

	tile = GetTile(x, y - 1);
	if (tile != nullptr && !((parent_x == x) && (parent_y == y - 1)))
	{
		if (!tile->isBlocking())
		{
			NewNode = NavigationNode(x, y - 1);

			NewNode.setFunctionGetTile(getTile);
			astarsearch->AddSuccessor(NewNode);
		}
	}

	tile = GetTile(x + 1, y);
	if (tile != nullptr && !((parent_x == x + 1) && (parent_y == y)))
	{
		if (!tile->isBlocking())
		{
			NewNode = NavigationNode(x + 1, y);
			NewNode.setFunctionGetTile(getTile);
			astarsearch->AddSuccessor(NewNode);
		}
	}

	tile = GetTile(x, y + 1);
	if (tile != nullptr && !((parent_x == x) && (parent_y == y + 1)))
	{
		if (!tile->isBlocking())
		{
			NewNode = NavigationNode(x, y + 1);
			NewNode.setFunctionGetTile(getTile);
			astarsearch->AddSuccessor(NewNode);
		}
	}



	/*

	if ((GetTile(x - 1, y)) && (GetTile(x, y - 1)) && (GetTile(x - 1, y - 1)) && !((parent_x == x - 1) && (parent_y == y - 1)))
	{

		NewNode = NavigationNode(x - 1, y - 1);
		//NewNode.setFunctionGetMap(getMap);
		astarsearch->AddSuccessor(NewNode);
	}

	if ((GetTile(x, y - 1)) && (GetTile(x + 1, y)) && (GetTile(x + 1, y - 1)) && !((parent_x == x + 1) && (parent_y == y - 1)))
	{
		NewNode = NavigationNode(x + 1, y - 1);
		//NewNode.setFunctionGetMap(getMap);
		astarsearch->AddSuccessor(NewNode);
	}

	if ((GetTile(x, y + 1)) && (GetTile(x + 1, y)) && (GetTile(x + 1, y + 1)) && !((parent_x == x + 1) && (parent_y == y + 1)))
	{
		NewNode = NavigationNode(x + 1, y + 1);
		//NewNode.setFunctionGetMap(getMap);
		astarsearch->AddSuccessor(NewNode);
	}


	if ((GetTile(x, y + 1)) && (GetTile(x - 1, y)) && (GetTile(x - 1, y + 1)) && !((parent_x == x - 1) && (parent_y == y + 1)))
	{
		NewNode = NavigationNode(x - 1, y + 1);
		//NewNode.setFunctionGetMap(getMap);
		astarsearch->AddSuccessor(NewNode);
	}*/

	return true;
}

bool NavigationNode::GetSuccesorsGroundNode(AStarSearch<NavigationNode>* astarsearch, NavigationNode * parent_node)
{
	int parent_x = -1;
	int parent_y = -1;

	if (parent_node)
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}



	return true;
}

bool NavigationNode::canStand(int x, int y)
{
	if (data == nullptr)return false;
	int characterWidth = data->characterWidth;
	
	

	if (characterWidth <= 1)
	{
		Tile * tile = GetTile(x, y+1);
		if (tile == nullptr)return false;
		else return tile->isBlocking();
	}
	else
	{;
		if (characterWidth % 2 == 1)
		{
			int sideSize = (characterWidth - 1) / 2;

			for (int i = x- sideSize; i <= x+ sideSize; i++)
			{
				Tile * tile = GetTile(i, y + 1);
				if (tile == nullptr)continue;
				else if (tile->isBlocking())return true;
			}
			return false;
		}
		else
		{
			int sideSize = (characterWidth) / 2;


			/*
			* Check if cant stand here
			*        x
			*     ><><
			* [][][]    [][]
			*/
			bool can_standLeft = false;
			for (int i = x - sideSize; i < x + sideSize; i++)
			{
				Tile * tile = GetTile(i, y + 1);
				if (tile != nullptr)
				{
					if (tile->isBlocking())
					{
						can_standLeft = true;
						break;
					}
				}
			}
			if (!can_standLeft)return false;


			/*
			* Check if cant stand here
			*        x
			*       ><><
			* [][][]    [][]
			*/

			bool can_standRight = false;
			for (int i = x - sideSize + 1; i < x + sideSize+1; i++)
			{
				Tile * tile = GetTile(i, y + 1);
				if (tile != nullptr)
				{
					if (tile->isBlocking())
					{
						can_standRight = true;
						break;
					}
				}
			}
			if (!can_standRight)return false;
			return true;
		}
	}



	return false;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is 
// conceptually where we're moving

bool NavigationNode::canWalk(int x, int y)
{
	if (data == nullptr)return false;
	int characterWidth = data->characterWidth;
	int characterHeight = data->characterHeight;


	/*
	* Check if can stand here
	*     ><[][]][]
	*     ><><
	* [][][]   [][]
	*/

	// if character have width 1
	if (characterWidth <= 1)
	{
		for (int i = y - characterHeight+1; i < y; i++)
		{
			Tile * tile = GetTile(x, i);
			if (tile != nullptr)
				if(tile->isBlocking())return false;
		}
		return true;
	}

	int sideSize = 0;
	if (characterWidth % 2 == 1)
	 sideSize = (characterWidth - 1) / 2;
	else
		sideSize = characterWidth  / 2;

	for (int i = x - sideSize; i <= x + sideSize; i++)
	{
		for (int j = y - characterHeight + 1; j < y; j++)
		{
			Tile * tile = GetTile(i, j);
			if (tile != nullptr)
				if (tile->isBlocking())return false;
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