#include <SFML\Graphics.hpp>
#include "AbstractTile.hpp"


#ifndef	DEFAULT_TILE_HPP
#define DEFAULT_TILE_HPP

class DefaultTile : public AbstractTile, public Damageable
{
public:
	DefaultTile(std::shared_ptr<TileDefinition> definition, sf::Vector2i position);

	void destroy() override
	{
		AbstractTile::destroy();
		Damageable::destroy();
	}
private:
	
};

#endif