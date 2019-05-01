#include <SFML\Graphics.hpp>
#include "game\engine\Collideable.hpp"
#include "TileDefinition.hpp"
#include "game\utility\Flags.h"
#include "game\graphics\Particle.hpp"
#include "game\engine\Damageable.hpp"

#define TILE_SIZE 32.f

#ifndef	ABSTRACT_TILE_HPP
#define ABSTRACT_TILE_HPP

namespace corpos
{
	struct TileDefinition;

	class AbstractTile : public Destructable, public Collideable
	{
	public:
		AbstractTile() {};
		AbstractTile(std::shared_ptr<TileDefinition> tiledef, sf::Vector2i pos);

		virtual void load(std::shared_ptr<sf::VertexArray> array);
		virtual void unload();

		virtual void replace(std::shared_ptr<TileDefinition> tiledef);

		virtual void updateTextureCoords(bool LT, bool T, bool TR,
			bool L, bool R,
			bool LB, bool B, bool BR);

		virtual void updatePositionCoords(sf::Vector2i pos);
		virtual void update();

		virtual bool isBlocking();
		virtual bool isBackground();
		virtual bool isShowTilesBehind();
		virtual bool isConnectingToTile(AbstractTile & tile);
		virtual bool isConnectingToTile(std::shared_ptr<AbstractTile> tile);

		std::shared_ptr<TileDefinition> getTileDefinitionPtr() { return definition; };
		const TileDefinition & getTileDefinition() { return *definition.get(); };
		std::weak_ptr<TileDefinition> getBackgroundTileDefinition() { return definition->backgroundTileDefinition; }

		sf::Vector2i getId() { return id; };
		sf::Vector2f getPosition()
		{
			return sf::Vector2f(id.x*TILE_SIZE + TILE_SIZE / 2,
				id.y*TILE_SIZE + TILE_SIZE / 2);
		}

		//For drawing order
		bool operator < (AbstractTile& right)
		{
			if (isShowTilesBehind() && right.isShowTilesBehind()
				|| !isShowTilesBehind() && !right.isShowTilesBehind()
				)
			{
				//return false;
				//if (a->getTileDefinition().value == b->getTileDefinition().value)
				{
					return getTileDefinition().name < right.getTileDefinition().name;
				}
				//else
				//{
				//return a->getTileDefinition().value < b->getTileDefinition().value;
				//}
			}
			else
			{
				return !isShowTilesBehind() && right.isShowTilesBehind();
			}
		}

		virtual std::string toString()
		{
			std::string str;
			str += "id: x" + std::to_string(id.x) + " y" + std::to_string(id.x)
				+ ", definition: " + definition->toString();
			return str;
		}

		void destroy() override;

	private:

		sf::Vector2i id;

		//flags
		Flags8 alignTiles = 0;

		unsigned int startingPos;
		__int8 vertexCount = 0;
		std::shared_ptr<sf::VertexArray> array;
		std::shared_ptr<TileDefinition> definition;

		sf::Vertex & vertex(unsigned int id)
		{
			return (*array)[id + startingPos];
		}
	};
}
#endif