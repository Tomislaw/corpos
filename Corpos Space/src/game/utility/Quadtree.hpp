#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>
#include "game\engine\Entity.hpp"
#include <iostream>
#include <sstream>




class Quadtree
{
public:
	Quadtree();
	Quadtree(sf::Vector2f lefttop, sf::Vector2f size, int level, int maxlevel, int capacity);
	~Quadtree();

	void AddObject(Entity *object);
	std::vector<Entity*> GetObjectsAt(sf::Vector2f pos);
	void Clear();


	void draw(sf::RenderTarget &canvas);
	void subdivide();

private:

	int	level;
	int	maxlevel;
	int	capacity;
	sf::Vector2f lefttop;
	sf::Vector2f size;
	sf::FloatRect rect;
	std::vector<Entity*> objects;

	bool is_last;
	Quadtree *	NW;
	Quadtree *	NE;
	Quadtree *	SW;
	Quadtree *	SE;

	sf::VertexArray	shape;

	bool Contains(Entity *object);
	bool Contains(sf::Vector2f vec);
	bool addToChildren(Entity *object);
};

#endif

