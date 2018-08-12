#include <SFML\Graphics.hpp>
#include "DefaultTile.hpp"

#ifndef	TILE_FACTORY_HPP
#define TILE_FACTORY_HPP

namespace TileFactory
{
	static std::shared_ptr<AbstractTile > create(std::shared_ptr<TileDefinition> definition, sf::Vector2i position)
	{
		return std::make_shared<DefaultTile >(definition, position);
	}
}
#endif
