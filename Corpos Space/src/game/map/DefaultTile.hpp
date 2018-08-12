#include <SFML\Graphics.hpp>
#include "AbstractTile.hpp"


#ifndef	DEFAULT_TILE_HPP
#define DEFAULT_TILE_HPP

class DefaultTile : public AbstractTile
{
public:
	DefaultTile(std::shared_ptr<TileDefinition> definition, sf::Vector2i position);

	void damage(int damage);

	bool collide(sf::Vector2f & before, sf::Vector2f & after, sf::Vector2f * collidePoint);

private:


	int health = 0;
	int maxHealth = 0;
};

#endif