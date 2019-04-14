#include "Pathfind.hpp"
#include <algorithm>
#include "game\map\MapTile\MapTile.hpp"

using namespace std::placeholders;
using namespace AStar;

PathFind::PathFind(NavigationNodeCharacterData character)
{
	setHeuristic(&Heuristic::octagonal);
	this->character = character;
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
		if (isStopped) {
			releaseNodes();
			return NodeDeque();
		}
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

		auto succesors = succesorsOfNode.getSuccesors(current, character);
		for each (auto newNode in succesors)
		{
			if (isStopped) {
				releaseNodes();
				return NodeDeque();
			}

			uint totalCost = current->G + current->getCost(&newNode);

			Node *successor = findNodeOnList(OpenSet, newNode);
			if (successor == nullptr)
			{
				successor = findNodeOnList(ClosedSet, newNode);
				if (successor != nullptr)
				{
					if (totalCost < successor->G)
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
		path.push_front(Node(*current));
		path.front().parent == nullptr;
		current = current->parent;
	}
	releaseNodes();

	return path;
}

bool AStar::PathFind::checkPath(NodeDeque & path)
{
	for (int i = 0; i < path.size() - 1; i++)
	{
		bool founddNode = false;
		auto nodes = succesorsOfNode.getSuccesors(&path[i], character);
		for each (auto node in nodes)
		{
			if (path[i + 1].isSame(&node))
			{
				founddNode = true;
				break;
			}
		}
		if (founddNode)continue;
		else return false;
	}
	return true;
}

Node* PathFind::findNodeOnList(NodeSet& nodes_, sf::Vector2i coordinates_)
{
	for each (auto node in nodes_)
		if (node->coordinates == coordinates_) return node;

	return nullptr;
}

Node* PathFind::findNodeOnList(NodeVector& nodes_, Node & pathnode)
{
	for each (auto node in nodes_)
		if (node->isSame(&pathnode)) return node;

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