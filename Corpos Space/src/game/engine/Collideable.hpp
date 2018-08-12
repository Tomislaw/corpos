#ifndef COLLIDEABLE_HPP
#define COLLIDEABLE_HPP

#include "Entity.hpp"
#include "game\graphics\GameSprite.hpp"
#include "Damageable.hpp"

class Collideable
{
public:
	virtual bool collide(sf::Vector2f & before, sf::Vector2f & after, sf::Vector2f * collidePoint) = 0;
};

#endif