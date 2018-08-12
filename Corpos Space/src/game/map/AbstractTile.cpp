#include "AbstractTile.hpp"

AbstractTile::AbstractTile(std::shared_ptr<TileDefinition> tiledef, sf::Vector2i pos)
{
	this->position = pos;
	definition = tiledef;
}

void AbstractTile::load(std::shared_ptr<sf::VertexArray> vertexArray)
{
	if (destroyed)return;
	vertexCount = 0;

	if (definition->singleImage) vertexCount = 4;
	else vertexCount = 16;
	
	startingPos = vertexArray->getVertexCount();
	for (int i = 0; i < vertexCount; i++)
	{
		vertexArray->append(sf::Vertex(sf::Vector2f(), sf::Vector2f()));
	}
	this->array = vertexArray;
	update();
}

void AbstractTile::unload()
{
	array == nullptr;
}

void AbstractTile::replace(std::shared_ptr<TileDefinition> tiledef)
{
	destroyed = false;
	this->definition = tiledef;
	update();
}

void AbstractTile::updateTextureCoords(bool LT, bool T, bool RT, 
										bool L,			 bool R, 
										bool LB, bool B, bool RB)
{
	if (destroyed) return;
	alignTiles.setFlags(0);
	alignTiles.setBit(0, LT); alignTiles.setBit(1, T); alignTiles.setBit(2, RT);
	alignTiles.setBit(3, L);						   alignTiles.setBit(4, R);
	alignTiles.setBit(5, LB); alignTiles.setBit(6, B); alignTiles.setBit(7, RB);


	if (vertexCount==0)
	{
		return;
	}

	if (vertexCount == 4)
	{
		auto r = definition->getInnerRect();
		vertex(0).texCoords = sf::Vector2f(r.left, r.top);
		vertex(1).texCoords = sf::Vector2f(r.left + r.width, r.top);
		vertex(2).texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
		vertex(3).texCoords = sf::Vector2f(r.left, r.top + r.height);
		return;
	}
	if (vertexCount == 16)
	{
		auto r = definition->getLTRect(L, LT, T);
		vertex(0).texCoords = sf::Vector2f(r.left, r.top);
		vertex(1).texCoords = sf::Vector2f(r.left + r.width, r.top);
		vertex(2).texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
		vertex(3).texCoords = sf::Vector2f(r.left, r.top + r.height);

		r = definition->getRTRect(T, RT, R);
		vertex(4).texCoords = sf::Vector2f(r.left, r.top);
		vertex(5).texCoords = sf::Vector2f(r.left + r.width, r.top);
		vertex(6).texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
		vertex(7).texCoords = sf::Vector2f(r.left, r.top + r.height);

		r = definition->getLBRect(B, LB, L);
		vertex(8).texCoords = sf::Vector2f(r.left, r.top);
		vertex(9).texCoords = sf::Vector2f(r.left + r.width, r.top);
		vertex(10).texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
		vertex(11).texCoords = sf::Vector2f(r.left, r.top + r.height);

		r = definition->getRBRect(R, RB, B);
		vertex(12).texCoords = sf::Vector2f(r.left, r.top);
		vertex(13).texCoords = sf::Vector2f(r.left + r.width, r.top);
		vertex(14).texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
		vertex(15).texCoords = sf::Vector2f(r.left, r.top + r.height);
		return;
	}
	Logger::e("Invalid vertex count in tile.");
	throw std::runtime_error("Invalid vertex count in tile");

}

void AbstractTile::updatePositionCoords(sf::Vector2i pos)
{
	if (destroyed)return;
	this->position = pos;
	if (vertexCount == 0 || array==nullptr)
	{
		return;
	}
	auto tileRect = definition->tileRect;
	if (vertexCount == 4)
	{
		auto r = definition->getInnerRect();
		vertex(0).position = sf::Vector2f(pos.x * TILE_SIZE + tileRect.left, pos.y * TILE_SIZE + tileRect.top);
		vertex(1).position = sf::Vector2f(pos.x * TILE_SIZE + tileRect.left + tileRect.width, pos.y * TILE_SIZE + tileRect.top);
		vertex(2).position = sf::Vector2f(pos.x * TILE_SIZE + tileRect.left + tileRect.width, pos.y * TILE_SIZE + tileRect.top + tileRect.height);
		vertex(3).position = sf::Vector2f(pos.x * TILE_SIZE + tileRect.left, pos.y * TILE_SIZE + tileRect.top + tileRect.height);
		return;
	}
	if (vertexCount == 16)
	{
		vertex(0).position = sf::Vector2f(pos.x* TILE_SIZE + tileRect.left, pos.y* TILE_SIZE + tileRect.top);
		vertex(1).position = sf::Vector2f(pos.x* TILE_SIZE, pos.y* TILE_SIZE + tileRect.top);
		vertex(2).position = sf::Vector2f(pos.x* TILE_SIZE, pos.y* TILE_SIZE);
		vertex(3).position = sf::Vector2f(pos.x* TILE_SIZE + tileRect.left, pos.y* TILE_SIZE);

		vertex(4).position = sf::Vector2f(pos.x* TILE_SIZE, pos.y * TILE_SIZE + tileRect.top);
		vertex(5).position = sf::Vector2f(pos.x* TILE_SIZE + tileRect.left + tileRect.width, pos.y* TILE_SIZE + tileRect.top);
		vertex(6).position = sf::Vector2f(pos.x* TILE_SIZE + tileRect.left + tileRect.width, pos.y* TILE_SIZE);
		vertex(7).position = sf::Vector2f(pos.x* TILE_SIZE, pos.y* TILE_SIZE);

		vertex(8).position = sf::Vector2f(pos.x* TILE_SIZE + tileRect.left, pos.y* TILE_SIZE);
		vertex(9).position = sf::Vector2f(pos.x* TILE_SIZE, pos.y* TILE_SIZE);
		vertex(10).position = sf::Vector2f(pos.x* TILE_SIZE, pos.y* TILE_SIZE + tileRect.top + tileRect.height);
		vertex(11).position = sf::Vector2f(pos.x * TILE_SIZE + tileRect.left, pos.y * TILE_SIZE + tileRect.top + tileRect.height);

		vertex(12).position = sf::Vector2f(pos.x* TILE_SIZE, pos.y* TILE_SIZE);
		vertex(13).position = sf::Vector2f(pos.x * TILE_SIZE + tileRect.left + tileRect.width, pos.y* TILE_SIZE);
		vertex(14).position = sf::Vector2f(pos.x * TILE_SIZE + tileRect.left + tileRect.width, pos.y * TILE_SIZE + tileRect.top + tileRect.height);
		vertex(15).position = sf::Vector2f(pos.x* TILE_SIZE, pos.y * TILE_SIZE + tileRect.top + tileRect.height);
		return;
	}
	Logger::e("Invalid vertex count in tile.");
	throw std::runtime_error("Invalid vertex count in tile");
}

void AbstractTile::update()
{
	if (destroyed)return;
	this->updatePositionCoords(position);
	this->updateTextureCoords(
		alignTiles.getBit(0), alignTiles.getBit(1), alignTiles.getBit(2),
		alignTiles.getBit(3), /*-----------------*/ alignTiles.getBit(4),
		alignTiles.getBit(5), alignTiles.getBit(6), alignTiles.getBit(7)
	);
}

bool AbstractTile::isBlocking() { return definition->is_blocking && !destroyed; }

bool AbstractTile::isBackground() { return definition->is_blocking; }

bool AbstractTile::isShowTilesBehind()
{
	return !alignTiles.noFlagsSet(); // || definition.isShowTilesBehind;
}


bool AbstractTile::isConnectingToTile(std::shared_ptr<AbstractTile> tile)
{
	if (tile == nullptr)return false;
	return isConnectingToTile(*tile.get());
}

bool AbstractTile::isConnectingToTile(AbstractTile & tile)
{
	bool isLowerInHierarchy;
	isLowerInHierarchy = tile.definition->name > this->definition->name;
	if (tile.definition->connectGroup == "-1")
	{
		return tile.definition->name == this->definition->name || isLowerInHierarchy;
	}
	else return tile.definition->connectGroup == this->definition->connectGroup || isLowerInHierarchy;
}

bool AbstractTile::isDestroyed() { return destroyed; }

void AbstractTile::destroy() { 
	destroyed = true;
	for (int i = 0; i < vertexCount;i++)
	{
		vertex(i).position = sf::Vector2f();
	}
	unload();
}
