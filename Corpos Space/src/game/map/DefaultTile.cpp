#include "DefaultTile.hpp"

DefaultTile::DefaultTile(std::shared_ptr<TileDefinition> definition, sf::Vector2i position) : AbstractTile(definition, position)
{
	health = definition->health;
	maxHealth = definition->health;
}