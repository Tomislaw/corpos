#include "Quadtree.hpp"
using namespace std;


Quadtree::Quadtree()
{
	NW = nullptr;
	NE = nullptr;
	SW = nullptr;
	SE = nullptr;
	is_last = true;
}

Quadtree::Quadtree(sf::Vector2f lefttop, sf::Vector2f size, int level, int maxlevel, int capacity)
{

	this->lefttop = lefttop;
	this->size = size;
	this->level = level;
	this->maxlevel = maxlevel;
	this->capacity = capacity;

	NW = nullptr;
	NE = nullptr;
	SW = nullptr;
	SE = nullptr;

	rect = sf::FloatRect(lefttop, size);

	is_last = true;
	//std::cout << _width << " " << _height << std::endl;
	{
		shape = sf::VertexArray(sf::LinesStrip, 5);

		sf::Color color;
		if (level == 0)
		{
			color = sf::Color(255, 255, 255, 255);
		}
		else if (level == 1)
		{
			color = sf::Color(255, 0, 0, 200);
		}
		else if (level == 2)
		{
			color = sf::Color(0, 255, 0, 200);
		}
		else if (level == 3)
		{
			color = sf::Color(0, 0, 255, 200);
		}
		else
		{
			color = sf::Color(0, 0, 0, 200/ (-3+level));
		}
		shape[0].color = color;
		shape[1].color = color;
		shape[2].color = color;
		shape[3].color = color;
		shape[4].color = color;

		shape[0].position = lefttop;
		shape[1].position = sf::Vector2f(lefttop.x+size.x, lefttop.y);
		shape[2].position = sf::Vector2f(lefttop + size);;
		shape[3].position = sf::Vector2f(lefttop.x, lefttop.y + size.y);
		shape[4].position = lefttop;

	}


}

void Quadtree::subdivide()
{
	NW = new Quadtree(lefttop, size / 2.f, level + 1, maxlevel, capacity);
	NE = new Quadtree(lefttop + sf::Vector2f(size.x / 2, 0), size / 2.f, level + 1, maxlevel, capacity);
	SW = new Quadtree(lefttop + sf::Vector2f(0, size.y / 2), size / 2.f, level + 1, maxlevel, capacity);
	SE = new Quadtree(lefttop + size / 2.f, size / 2.f, level + 1, maxlevel, capacity);
}

void Quadtree::AddObject(Entity *object)
{
	if (is_last)
	{
		objects.push_back(object);
		if (objects.size() >= capacity && level != maxlevel)
		{
			is_last = false;
			subdivide();
		}
		return;
	}
	addToChildren(object);
}

bool Quadtree::addToChildren(Entity *object)
{
	bool entityAdded = false;
	if (NE->Contains(object))
	{
		NE->AddObject(object);
		entityAdded = true;
	}
	if (NW->Contains(object))
	{
		NW->AddObject(object);
		entityAdded = true;
	}
	if (SE->Contains(object))
	{
		SE->AddObject(object);
		entityAdded = true;
	}
	if (SW->Contains(object))
	{
		SW->AddObject(object);
		entityAdded = true;
	}
	if(!entityAdded)objects.push_back(object);
	return entityAdded;
}
bool Quadtree::Contains(Entity *object)
{
	return object->intersects(rect);
}
bool Quadtree::Contains(sf::Vector2f vec)
{
	return rect.contains(vec);
}
void Quadtree::Clear()
{
	if (!objects.empty())objects.clear();
	if (!is_last)
	{
		NW->Clear();
		NE->Clear();
		SW->Clear();
		SE->Clear();
		NW = nullptr;
		NE = nullptr;
		SW = nullptr;
		SE = nullptr;
		is_last = true;
	}
}

Quadtree::~Quadtree()
{
	if (!is_last)
	{
		delete	NW;
		delete	NE;
		delete	SW;
		delete	SE;
	}
}

void Quadtree::draw(sf::RenderTarget &canvas)
{

	if (!is_last) {
		NW->draw(canvas);
		NE->draw(canvas);
		SW->draw(canvas);
		SE->draw(canvas);
	}
	canvas.draw(shape);
}
vector<Entity*> Quadtree::GetObjectsAt(sf::Vector2f pos)
{
	if (is_last)
	{
		return objects;
	}
	vector<Entity*> returnObjects, childReturnObjects;


	if (NE->Contains(pos))
	{
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (NE->Contains(objects[i]))
				returnObjects.push_back(objects[i]);
		}
		childReturnObjects = NE->GetObjectsAt(pos);
		returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());

	}
	if (NW->Contains(pos))
	{
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (NW->Contains(objects[i]))
				returnObjects.push_back(objects[i]);
		}
		childReturnObjects = NW->GetObjectsAt(pos);
		returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
	}
	if (SE->Contains(pos))
	{
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (SE->Contains(objects[i]))
				returnObjects.push_back(objects[i]);
		}
		childReturnObjects = SE->GetObjectsAt(pos);
		returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
	}
	if (SW->Contains(pos))
	{
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (SW->Contains(objects[i]))returnObjects.push_back(objects[i]);
		}
		childReturnObjects = SW->GetObjectsAt(pos);
		returnObjects.insert(returnObjects.end(), childReturnObjects.begin(), childReturnObjects.end());
	}

	return returnObjects;
}