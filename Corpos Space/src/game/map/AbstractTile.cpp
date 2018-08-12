#include "AbstractTile.hpp"

AbstractTile::AbstractTile(std::shared_ptr<TileDefinition> tiledef, sf::Vector2i pos)
{
	this->position = pos;
	definition = tiledef;
}

void AbstractTile::load(sf::VertexArray & vertexArray)
{
	if (destroyed)return;
	int vertexCount = 0;

	if (definition->singleImage) vertexCount = 4;
	else vertexCount = 16;
	
	for (int i = 0; i < vertexCount; i++)
	{
		vertexArray.append(sf::Vertex(sf::Vector2f(), sf::Vector2f()));
		tile.push_back(&vertexArray[vertexArray.getVertexCount() - 1]);
	}

}

void AbstractTile::unload()
{
	tile.clear();
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
	if (destroyed)return;
	alignTiles = 0;
	alignTiles |= LT << 0; alignTiles |= T << 1; alignTiles |= RT << 2;
	alignTiles |= L << 3; /*------------------*/ alignTiles |= R << 4;
	alignTiles |= LB << 5; alignTiles |= B << 6; alignTiles |= RB << 7;

	if (tile.size()==0)
	{
		return;
	}

	if (tile.size() == 4)
	{
		auto r = definition->getInnerRect();
		tile.at(0)->texCoords = sf::Vector2f(r.left, r.top);
		tile.at(1)->texCoords = sf::Vector2f(r.left + r.width, r.top);
		tile.at(2)->texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
		tile.at(3)->texCoords = sf::Vector2f(r.left, r.top + r.height);
		return;
	}
	if (tile.size() == 16)
	{
		auto r = definition->getLTRect(L, LT, T);
		tile.at(0)->texCoords = sf::Vector2f(r.left, r.top);
		tile.at(1)->texCoords = sf::Vector2f(r.left + r.width, r.top);
		tile.at(2)->texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
		tile.at(3)->texCoords = sf::Vector2f(r.left, r.top + r.height);

		r = definition->getRTRect(T, RT, R);
		tile.at(4)->texCoords = sf::Vector2f(r.left, r.top);
		tile.at(5)->texCoords = sf::Vector2f(r.left + r.width, r.top);
		tile.at(6)->texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
		tile.at(7)->texCoords = sf::Vector2f(r.left, r.top + r.height);

		r = definition->getLBRect(B, LB, L);
		tile.at(8)->texCoords = sf::Vector2f(r.left, r.top);
		tile.at(9)->texCoords = sf::Vector2f(r.left + r.width, r.top);
		tile.at(10)->texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
		tile.at(11)->texCoords = sf::Vector2f(r.left, r.top + r.height);

		r = definition->getRBRect(R, RB, B);
		tile.at(12)->texCoords = sf::Vector2f(r.left, r.top);
		tile.at(13)->texCoords = sf::Vector2f(r.left + r.width, r.top);
		tile.at(14)->texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
		tile.at(15)->texCoords = sf::Vector2f(r.left, r.top + r.height);
		return;
	}
	Logger::e("Invalid vertex count in tile.");
	throw std::runtime_error("Invalid vertex count in tile");

}

void AbstractTile::updatePositionCoords(sf::Vector2i pos)
{
	if (destroyed)return;
	this->position = pos;
	if (tile.size() == 0)
	{
		return;
	}
	auto tileRect = definition->tileRect;
	if (tile.size() == 4)
	{
		auto r = definition->getInnerRect();
		tile.at(0)->position = sf::Vector2f(pos.x * TILE_SIZE + tileRect.left, pos.y * TILE_SIZE + tileRect.top);
		tile.at(1)->position = sf::Vector2f(pos.x * TILE_SIZE + tileRect.left + tileRect.width, pos.y * TILE_SIZE + tileRect.top);
		tile.at(2)->position = sf::Vector2f(pos.x * TILE_SIZE + tileRect.left + tileRect.width, pos.y * TILE_SIZE + tileRect.top + tileRect.height);
		tile.at(3)->position = sf::Vector2f(pos.x * TILE_SIZE + tileRect.left, pos.y * TILE_SIZE + tileRect.top + tileRect.height);
		return;
	}
	if (tile.size() == 16)
	{
		tile.at(0)->position = sf::Vector2f(pos.x* TILE_SIZE + tileRect.left, pos.y* TILE_SIZE + tileRect.top);
		tile.at(1)->position = sf::Vector2f(pos.x* TILE_SIZE, pos.y* TILE_SIZE + tileRect.top);
		tile.at(2)->position = sf::Vector2f(pos.x* TILE_SIZE, pos.y* TILE_SIZE);
		tile.at(3)->position = sf::Vector2f(pos.x* TILE_SIZE + tileRect.left, pos.y* TILE_SIZE);

		tile.at(4)->position = sf::Vector2f(pos.x* TILE_SIZE, pos.y * TILE_SIZE + tileRect.top);
		tile.at(5)->position = sf::Vector2f(pos.x* TILE_SIZE + tileRect.left + tileRect.width, pos.y* TILE_SIZE + tileRect.top);
		tile.at(6)->position = sf::Vector2f(pos.x* TILE_SIZE + tileRect.left + tileRect.width, pos.y* TILE_SIZE);
		tile.at(7)->position = sf::Vector2f(pos.x* TILE_SIZE, pos.y* TILE_SIZE);

		tile.at(8)->position = sf::Vector2f(pos.x* TILE_SIZE + tileRect.left, pos.y* TILE_SIZE);
		tile.at(9)->position = sf::Vector2f(pos.x* TILE_SIZE, pos.y* TILE_SIZE);
		tile.at(10)->position = sf::Vector2f(pos.x* TILE_SIZE, pos.y* TILE_SIZE + tileRect.top + tileRect.height);
		tile.at(11)->position = sf::Vector2f(pos.x * TILE_SIZE + tileRect.left, pos.y * TILE_SIZE + tileRect.top + tileRect.height);

		tile.at(12)->position = sf::Vector2f(pos.x* TILE_SIZE, pos.y* TILE_SIZE);
		tile.at(13)->position = sf::Vector2f(pos.x * TILE_SIZE + tileRect.left + tileRect.width, pos.y* TILE_SIZE);
		tile.at(14)->position = sf::Vector2f(pos.x * TILE_SIZE + tileRect.left + tileRect.width, pos.y * TILE_SIZE + tileRect.top + tileRect.height);
		tile.at(15)->position = sf::Vector2f(pos.x* TILE_SIZE, pos.y + tileRect.top + tileRect.height);
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
		alignTiles & (1 >> 0) == 1, alignTiles & (2 >> 1) == 1, alignTiles & (4 >> 2) == 1,
		alignTiles & (8 >> 3) == 1, /*------------------------*/ alignTiles & (16 >> 4) == 1,
		alignTiles & (32 >> 5) == 1, alignTiles & (64 >> 6) == 1, alignTiles & (128 >> 7) == 1
	);
}

bool AbstractTile::isBlocking() { return definition->is_blocking && !destroyed; }

bool AbstractTile::isBackground() { return definition->is_blocking; }

bool AbstractTile::isShowTilesBehind()
{
	return !alignTiles != 0; // || definition.isShowTilesBehind;
}


bool AbstractTile::isSameGroup(std::shared_ptr<AbstractTile> tile)
{
	if (tile == nullptr)return false;
	return isSameGroup(*tile.get());
}

bool AbstractTile::isSameGroup(AbstractTile & tile)
{

	if (tile.definition->connectGroup == "-1")
	{
		return tile.definition->name == this->definition->name;
	}
	else return tile.definition->connectGroup == this->definition->connectGroup;
}

bool AbstractTile::isDestroyed() { return destroyed; }

void AbstractTile::destroy() { 
	destroyed = true;
	for each (sf::Vertex * v in tile)
	{
		v->position = sf::Vector2f();
	}
	unload();
}
