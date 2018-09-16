#include <SFML\Graphics.hpp>
#include "DefaultTile.hpp"

#ifndef	TILE_FACTORY_HPP
#define TILE_FACTORY_HPP

class TileFactory
{
public:

	static std::shared_ptr<AbstractTile > create(std::weak_ptr<TileDefinition> definition, sf::Vector2i position)
	{
		if (definition.expired()) return nullptr;
		auto ptr = definition.lock();
		return findAndCreate(ptr, position);
	}

	static std::shared_ptr<AbstractTile > create(std::shared_ptr<TileDefinition> definition, sf::Vector2i position)
	{
		return findAndCreate(definition, position);
	}

private:
	static std::shared_ptr<AbstractTile > findAndCreate(std::shared_ptr<TileDefinition> definition, sf::Vector2i position)
	{
		if (definition == nullptr) return nullptr;
		return std::make_shared<DefaultTile >(definition, position);
	}
};
#endif
