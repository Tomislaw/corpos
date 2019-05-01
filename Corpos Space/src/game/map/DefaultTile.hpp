#include <SFML\Graphics.hpp>
#include "AbstractTile.hpp"
#include "game\utility\Intersection.hpp"

#ifndef	DEFAULT_TILE_HPP
#define DEFAULT_TILE_HPP

namespace corpos
{
	class DefaultTile : public AbstractTile, public Damageable
	{
	public:
		DefaultTile(std::shared_ptr<TileDefinition> definition, sf::Vector2i position);

		void destroy() override
		{
			AbstractTile::destroy();
			Damageable::destroy();
		}

		virtual bool collide(sf::Vector2f & before, sf::Vector2f & after, sf::Vector2f & collidePoint) override
		{
			if (!isBlocking())return false;
			auto id = this->getId();
			return Intersection::LineSegRectIntersectionPoint(before, after, sf::FloatRect(id.x*TILE_SIZE, id.y*TILE_SIZE, TILE_SIZE, TILE_SIZE), collidePoint);
		}
	private:
	};
}
#endif