#include "Pathfind.hpp"
#include <algorithm>
#include "game\map\Tile.hpp"

using namespace std::placeholders;
using namespace AStar;
GetTile AStar::PathFind::getTile = nullptr;;


Node::Node(sf::Vector2i coordinates_, Node *parent_)
{
	parent = parent_;
	coordinates = coordinates_;
	G = H = F= 0;
	type = jumpDistancePassed = 0;
}

AStar::Node::Node(int x, int y, Node * parent_)
{
	parent = parent_;
	coordinates = sf::Vector2i(x, y);
	F = G = H = 0;
	type = jumpDistancePassed = 0;
}

uint AStar::Node::getScore()
{
	return G + H;
}

bool Node::isSame(Node * node)
{
	return (node->coordinates==coordinates&&node->type==type);
}

uint AStar::Node::getCost(Node * node)
{
	if (node->coordinates.x == coordinates.x || node->coordinates.y == coordinates.y)return 10;
	return 14;
}


PathFind::PathFind()
{
	setHeuristic(&Heuristic::octagonal);

	character.characterHeight = 2;
	character.characterWidth = 2;
	character.characterJumpHeight = 1;

}



void PathFind::setHeuristic(HeuristicFunction heuristic_)
{
	heuristic = std::bind(heuristic_, _1, _2);
}


NodeDeque PathFind::findPath(Node source_, sf::Vector2i target_)
{
	Node *current = nullptr;
	source_.H = heuristic(source_.coordinates, target_);
	OpenSet.push_back(new Node(source_));
	push_heap(OpenSet.begin(), OpenSet.end(), NodeCompare_F());

	bool pathFound = false;

	while (!OpenSet.empty()) 
	{


		current = OpenSet.front();


		//if its goal
		if (current->coordinates == target_) 
		{
			pathFound = true;
			break;
		}


		ClosedSet.push_back(current);
		pop_heap(OpenSet.begin(), OpenSet.end(), NodeCompare_F());
		OpenSet.pop_back();



		auto succesors = getSuccesors(current);
		for each (auto newNode in succesors)
		{
			uint totalCost = current->G + current->getCost(&newNode);

			Node *successor = findNodeOnList(OpenSet, newNode);
			if (successor == nullptr)
			{
				successor = findNodeOnList(ClosedSet, newNode);
				if (successor != nullptr)
				{
					if (totalCost< successor->G)
					{
						OpenSet.push_back(successor);
						push_heap(OpenSet.begin(), OpenSet.end(), NodeCompare_F());

						ClosedSet.erase(std::find(ClosedSet.begin(), ClosedSet.end(), successor));
					}

				}
				else
				{ 

					successor = new Node(newNode);
					successor->G = totalCost;
					successor->H = heuristic(successor->coordinates, target_);
					successor->F = successor->G + successor->H;
					OpenSet.push_back(successor);
					push_heap(OpenSet.begin(), OpenSet.end(), NodeCompare_F());
				}
			}
			else if (totalCost < successor->G)
			{
				successor->parent = current;
				successor->G = totalCost;
			}
		}

	}

	//get current path
	NodeDeque path;

	if (!pathFound)
	{
		current = ClosedSet.back();
		for each (auto node in ClosedSet)
		{
			if (current->H >= node->H)
			{
				if (current->H == node->H)
				{
					if (current->F > node->F)current = node;
				}
				else current = node;
			}


		}
	}

	while (current != nullptr) 
	{
		path.push_front(current);
		current = current->parent;
	}



	return path;
}

Node* PathFind::findNodeOnList(NodeSet& nodes_, sf::Vector2i coordinates_)
{
	for each (auto node in nodes_) 
	{
		if (node->coordinates == coordinates_) 
		{
			return node;
		}
	}
	return nullptr;
}

Node* PathFind::findNodeOnList(NodeVector& nodes_, Node & pathnode)
{
	for each (auto node in nodes_) 
	{
		if (node->isSame(&pathnode)) 
		{
			return node;
		}
	}
	return nullptr;
}

void AStar::PathFind::releaseNodes()
{
	releaseNodes(OpenSet);
	releaseNodes(ClosedSet);
}

void PathFind::releaseNodes(NodeSet& nodes_)
{
	for (auto it = nodes_.begin(); it != nodes_.end();) {
		delete *it;
		it = nodes_.erase(it);
	}
}

void AStar::PathFind::releaseNodes(NodeVector & nodes_)
{


	for (auto it = nodes_.begin(); it != nodes_.end();) {
		delete *it;
		it = nodes_.erase(it);
	}
}

bool PathFind::canWalkToTile(Node * node,int x, int y)
{
	int characterWidth = character.characterWidth;


	if (characterWidth <= 1)
	{
		Tile * tile = getTile(x, y + 1);
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
				Tile * tile = getTile(i, y + 1);
				if (tile == nullptr)continue;
				else if (tile->isBlocking())return true;
			}
			return false;

		}
		else // for 2,4,6,...,2n width characters
		{
			sideSize = character.characterWidth / 2;

			int dir = node->coordinates.x - x;
			if (node->coordinates.y == y && (dir != 1 || dir != -1))
			{
				int start = x;
				if (dir == 1)start = node->coordinates.x;


				for (int i = start - sideSize; i < start + sideSize; i++)
				{
					Tile * tile = getTile(i, y + 1);
					if (tile != nullptr)
						if (tile->isBlocking())return true;
				}

			}
			else
			{
				for (int i = x - sideSize; i <= x + sideSize; i++)
				{
					Tile * tile = getTile(i, y + 1);
					if (tile == nullptr)continue;
					else if (tile->isBlocking())return true;
				}
				return false;
			}
			return false;
		}


	}

}

bool AStar::PathFind::canStandOnTile(int x, int y)
{
	int characterWidth = character.characterWidth;

	if (characterWidth <= 1)
	{
		Tile * tile = getTile(x, y + 1);
		if (tile == nullptr)return false;
		else return tile->isBlocking();
	}
	else
	{
		int sideSize = 0;
		sideSize = (characterWidth - 1) / 2;

		for (int i = x - sideSize; i <= x + sideSize; i++)
		{
			Tile * tile = getTile(i, y + 1);
			if (tile == nullptr)continue;
			else if (tile->isBlocking())return true;
		}
		return false;

		}
		
}





bool PathFind::canMoveToTile(Node * node, int x, int y)
{

	int characterWidth = character.characterWidth;
	int characterHeight = character.characterHeight;

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
			Tile * tile = getTile(x, i);
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
			Tile * tile = getTile(i, j);
			if (tile != nullptr)
			{

				if (tile->isBlocking())return false;
			}
			else return false;
		}
	}
	return true;

}

std::vector<Node> AStar::PathFind::getSuccesors(Node * node)
{
	return getGroundSuccesors(node);
}

std::vector<Node> AStar::PathFind::getGroundSuccesors(Node * node)
{
	std::vector<Node> astarsearch;

	int parent_x = -1;
	int parent_y = -1;

	int x = node->coordinates.x;
	int y = node->coordinates.y;

	Node Succesor(-1, -1);


	if (node->parent)
	{
		if (node->parent->type != Node::CENTER_POSITION)
		{
			//parent_x = parent_node->x;
			//parent_y = parent_node->y;
		}
	}
	else
	{
		if (!canWalkToTile(node,x, y))
		{
			node->type = Node::CENTER_POSITION;
			

			//LEFT
			if (canMoveToTile(node, x - 1, y) && canWalkToTile(node, x - 1, y))
			{
				Succesor = Node(sf::Vector2i(x - 1, y), node);
				Succesor.type = Node::WALK;
				astarsearch.push_back(Succesor);
			}
			//RIGHT

			if (canMoveToTile(node, x + 1, y) && canWalkToTile(node, x + 1, y))
			{
				Succesor = Node(x + 1, y,node);
				Succesor.type = Node::WALK;
				astarsearch.push_back(Succesor);
			}
			if(astarsearch.size()!=0)
			return astarsearch;
		}		
		node->type = Node::WALK;
	}



	
	// Normal walking
	if (node->type == Node::WALK)
	{
		//LEFT
		if (!((parent_x == x - 1) && (parent_y == y)))
		{
			if (canMoveToTile(node, x - 1, y))
			{
				Succesor = Node(x - 1, y, node);
				if (canWalkToTile(node, x - 1, y))
				{
					Succesor.type = Node::WALK;
					Succesor.jumpDistancePassed = 0;
					astarsearch.push_back(Succesor);
				}
				else
				{
					if (character.characterWidth == 1)
					{
						Succesor.type = Node::FALL;
						Succesor.jumpDistancePassed = character.characterJumpHeight + 1;
						astarsearch.push_back(Succesor);

						Succesor.type = Node::BEFORE_JUMP;
						Succesor.jumpDistancePassed = 0;
						astarsearch.push_back(Succesor);
					}
				}
			}

		}
		//RIGHT
		if (!((parent_x == x + 1) && (parent_y == y)))
		{
			if (canMoveToTile(node, x + 1, y))
			{
				Succesor = Node(x + 1, y, node);

				if (canWalkToTile(node, x + 1, y))
				{
					Succesor.type = Node::WALK;
					Succesor.jumpDistancePassed = 0;
					astarsearch.push_back(Succesor);
				}
				else
				{
					if (character.characterWidth == 1)
					{
						Succesor.type = Node::FALL;
						Succesor.jumpDistancePassed = character.characterJumpHeight + 1;
						astarsearch.push_back(Succesor);

						Succesor.type = Node::BEFORE_JUMP;
						Succesor.jumpDistancePassed = 0;
						astarsearch.push_back(Succesor);
					}

				}

			}

			// RIGHT BOTTOM
			if (!((parent_x == x + 1) && (parent_y == y + 1)))
			{
				if (canMoveToTile(node, x + 1, y + 1))
				{
					Succesor = Node(x + 1, y + 1, node);

					if (canWalkToTile(node, x + 1, y + 1))
						Succesor.type = Node::WALK;
					else
					{
						Succesor.type = Node::FALL;
						Succesor.jumpDistancePassed = node->jumpDistancePassed + 2;
					}
					astarsearch.push_back(Succesor);
				}
			}

			// LEFT BOTTOM
			if (!((parent_x == x - 1) && (parent_y == y + 1)))
			{
				if (canMoveToTile(node, x - 1, y + 1))
				{
					Succesor = Node(x - 1, y + 1, node);
					if (canWalkToTile(node, x - 1, y + 1))
						Succesor.type = Node::WALK;
					else
					{
						Succesor.type = Node::FALL;
						Succesor.jumpDistancePassed = node->jumpDistancePassed + 2;
					}
					astarsearch.push_back(Succesor);
				}
			}
		}

		//TOP
		if (!((parent_x == x) && (parent_y == y - 1)))
		{
			if (canMoveToTile(node, x, y - 1))
			{
				Succesor = Node(x, y - 1, node);
				Succesor.type = Node::JUMP;
				Succesor.jumpDistancePassed = 1;
				astarsearch.push_back(Succesor);

			}
		}

		//LEFT TOP
		if (!((parent_x == x - 1) && (parent_y == y - 1)))
		{
			if (canMoveToTile(node, x - 1, y - 1))
			{
				Succesor = Node(x - 1, y - 1, node);

				Succesor.type = Node::JUMP;
				Succesor.jumpDistancePassed = 1;
				astarsearch.push_back(Succesor);
			}
		}

		//RIGHT TOP
		if (!((parent_x == x + 1) && (parent_y == y - 1)))
		{
			if (canMoveToTile(node, x + 1, y - 1))
			{
				Succesor = Node(x + 1, y - 1, node);

				Succesor.type = Node::JUMP;
				Succesor.jumpDistancePassed = 1;
				astarsearch.push_back(Succesor);
			}
		}
	}
	//only for 1 width characters
	if (node->type == Node::BEFORE_JUMP)
	{
		//TOP
		if (!((parent_x == x) && (parent_y == y - 1)))
		{
			if (canMoveToTile(node, x, y - 1))
			{
				Succesor = Node(x, y - 1, node);

				Succesor.type = Node::JUMP;
				Succesor.jumpDistancePassed = 1;
				astarsearch.push_back(Succesor);

			}
		}

		//LEFT TOP
		if (!((parent_x == x - 1) && (parent_y == y - 1)))
		{
			if (canMoveToTile(node, x - 1, y - 1))
			{
				Succesor = Node(x - 1, y - 1, node);

				Succesor.type = Node::JUMP;
				Succesor.jumpDistancePassed = 1;
				astarsearch.push_back(Succesor);
			}
		}

		//RIGHT TOP
		if (!((parent_x == x + 1) && (parent_y == y - 1)))
		{
			if (canMoveToTile(node, x + 1, y - 1))
			{
				Succesor = Node(x + 1, y - 1, node);

				Succesor.type = Node::JUMP;
				Succesor.jumpDistancePassed = 1;
				astarsearch.push_back(Succesor);
			}
		}
	}
	// while jumping
	if (node->type == Node::JUMP || node->type == Node::AFTER_JUMP)
	{
		// while increasing height
		if (node->jumpDistancePassed != character.characterJumpHeight)
		{
			//TOP
			if (!((parent_x == x) && (parent_y == y - 1)))
			{
				if (canMoveToTile(node, x, y - 1))
				{
					Succesor = Node(x, y - 1,node);

					Succesor.type = Node::AFTER_JUMP;
					Succesor.jumpDistancePassed = node->jumpDistancePassed + 1;
					astarsearch.push_back(Succesor);
				}
			}
			//LEFT TOP
			if (!((parent_x == x - 1) && (parent_y == y - 1)))
			{
				if (canMoveToTile(node, x - 1, y - 1))
				{
					Succesor = Node(x - 1, y - 1, node);

					Succesor.type = Node::AFTER_JUMP;
					Succesor.jumpDistancePassed = node->jumpDistancePassed + 1;
					astarsearch.push_back(Succesor);
				}
			}

			//RIGHT TOP
			if (!((parent_x == x + 1) && (parent_y == y - 1)))
			{
				if (canMoveToTile(node, x + 1, y - 1))
				{
					Succesor = Node(x + 1, y - 1, node);

					Succesor.type = Node::AFTER_JUMP;
					Succesor.jumpDistancePassed = node->jumpDistancePassed + 1;
					astarsearch.push_back(Succesor);
				}
			}
		}
		else //while at top
		{
			//BOTTOM
			if (!((parent_x == x) && (parent_y == y + 1)))
			{
				if (canMoveToTile(node, x, y + 1))
				{
					Succesor = Node(x, y + 1, node);
					if (canWalkToTile(node, x, y + 1))
						Succesor.type = Node::WALK;
					else
					{
						Succesor.type = Node::FALL;
						Succesor.jumpDistancePassed = node->jumpDistancePassed + 1;
					}
					astarsearch.push_back(Succesor);
				}
			}

			// RIGHT BOTTOM
			if (!((parent_x == x + 1) && (parent_y == y + 1)))
			{
				if (canMoveToTile(node, x + 1, y + 1))
				{
					Succesor = Node(x + 1, y + 1, node);

					if (canWalkToTile(node, x + 1, y + 1))
						Succesor.type = Node::WALK;
					else
					{
						Succesor.type = Node::FALL;
						Succesor.jumpDistancePassed = node->jumpDistancePassed + 1;
					}
					astarsearch.push_back(Succesor);
				}
			}

			// LEFT BOTTOM
			if (!((parent_x == x - 1) && (parent_y == y + 1)))
			{
				if (canMoveToTile(node, x - 1, y + 1))
				{
					Succesor = Node( x - 1, y + 1, node);
					Succesor.jumpDistancePassed = node->jumpDistancePassed + 1;
					if (canWalkToTile(node, x - 1, y + 1))
						Succesor.type = Node::WALK;
					else
					{
						Succesor.type = Node::FALL;
						Succesor.jumpDistancePassed = node->jumpDistancePassed + 1;
					}
					astarsearch.push_back(Succesor);
				}
			}

			//LEFT
			if (!((parent_x == x - 1) && (parent_y == y)))
			{
				//if (canMoveToTile(node, x - 1, y))
				if (canStandOnTile(x - 1, y))
				{
					Succesor = Node(x - 1, y, node);

					if (canWalkToTile(node, x - 1, y))
					{
						Succesor.type = Node::WALK;
					}

					else
					{
						Succesor.type = Node::FALL;
						Succesor.jumpDistancePassed = node->jumpDistancePassed + 1;
					}
					astarsearch.push_back(Succesor);
				}

			}
			//RIGHT
			if (!((parent_x == x + 1) && (parent_y == y)))
			{
				if (canStandOnTile(x + 1, y))
				{
					Succesor = Node(x + 1, y, node);

					if (canWalkToTile(node, x + 1, y))
						Succesor.type = Node::WALK;
					else
					{
						Succesor.type = Node::FALL;
						Succesor.jumpDistancePassed = node->jumpDistancePassed + 1;
					}
					astarsearch.push_back(Succesor);
				}
			}
		}
	}
	// while failing
	if (node->type == Node::FALL)
	{
		//BOTTOM
		if (!((parent_x == x) && (parent_y == y + 1)))
		{
			if (canMoveToTile(node, x, y + 1))
			{
				Succesor = Node(x, y + 1, node);

				if (canWalkToTile(node, x, y + 1))
					Succesor.type = Node::WALK;
				else
				{
					Succesor.type = Node::FALL;
					Succesor.jumpDistancePassed = node->jumpDistancePassed + 1;
				}
				astarsearch.push_back(Succesor);
			}
		}

		if (node->jumpDistancePassed < character.characterJumpHeight + 3)// if fall to much, cant go to left and right (to much fall speed)
		{
			// RIGHT BOTTOM
			if (!((parent_x == x + 1) && (parent_y == y + 1)))
			{
				if (canMoveToTile(node, x + 1, y + 1))
				{
					Succesor = Node(x + 1, y + 1, node);

					if (canWalkToTile(node, x + 1, y + 1))
						Succesor.type = Node::WALK;
					else
					{
						Succesor.type = Node::FALL;
						Succesor.jumpDistancePassed = node->jumpDistancePassed + 1;
					}
					astarsearch.push_back(Succesor);
				}
			}

			// LEFT BOTTOM
			if (!((parent_x == x - 1) && (parent_y == y + 1)))
			{
				if (canMoveToTile(node, x - 1, y + 1))
				{
					Succesor = Node(x - 1, y + 1, node);

					if (canWalkToTile(node, x - 1, y + 1))
						Succesor.type = Node::WALK;
					else
					{
						Succesor.type = Node::FALL;
						Succesor.jumpDistancePassed = node->jumpDistancePassed + 1;
					}
					astarsearch.push_back(Succesor);
				}
			}
		}
	}


	return astarsearch;
}

/*bool AStar::PathFind::detectCollision(sf::Vector2i coordinates_)
{
	if (coordinates_.x < 0 || coordinates_.x >= worldSize.x ||
		coordinates_.y < 0 || coordinates_.y >= worldSize.y ||
		std::find(walls.begin(), walls.end(), coordinates_) != walls.end()) {
		return true;
	}
	return false;
}*/

sf::Vector2i Heuristic::getDelta(sf::Vector2i source_, sf::Vector2i target_)
{
	return{ abs(source_.x - target_.x),  abs(source_.y - target_.y) };
}

uint AStar::Heuristic::manhattan(sf::Vector2i source_, sf::Vector2i target_)
{
	auto delta = std::move(getDelta(source_, target_));
	return static_cast<uint>(10 * (delta.x + delta.y));
}

uint AStar::Heuristic::euclidean(sf::Vector2i source_, sf::Vector2i target_)
{
	auto delta = std::move(getDelta(source_, target_));
	return static_cast<uint>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}

uint AStar::Heuristic::octagonal(sf::Vector2i source_, sf::Vector2i target_)
{
	auto delta = std::move(getDelta(source_, target_));
	return 10 * (delta.x + delta.y) + (-6) * std::min(delta.x, delta.y);
}