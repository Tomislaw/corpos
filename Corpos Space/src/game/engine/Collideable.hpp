#ifndef COLLIDEABLE_HPP
#define COLLIDEABLE_HPP

#include <SFML\Graphics.hpp>

class Collideable
{
public:
	virtual bool collide(sf::Vector2f & before, sf::Vector2f & after, sf::Vector2f & collidePoint) { return false; }
};

#endif