#include "DefaultTile.hpp"

DefaultTile::DefaultTile(std::shared_ptr<TileDefinition> definition, sf::Vector2i position) : AbstractTile(definition, position)
{
	health = definition->health;
	maxHealth = definition->health;
}

void DefaultTile::damage(int damage)
{
	if (isDestroyed())return;
	health -= damage;
	if (health <= 0)destroy();
}

bool DefaultTile::collide(sf::Vector2f & before, sf::Vector2f & after, sf::Vector2f * collidePoint)
{
	if (isBlocking())return false;
}
