#include "Tile.hpp"

#include "game\engine\World.hpp"

using namespace corpos;

Tile::Tile()
{
	this->name = "0";
	this->is_blocking = false;
	this->definition = nullptr;
	this->singleImage = true;
}

Tile::Tile(TileDefinition * tiledef, std::vector<sf::Vertex*> tile, sf::Vector2f pos)
{
	changeTile(tiledef, tile, pos);
}

void Tile::changeTile(TileDefinition * tiledef, std::vector<sf::Vertex*> tile, sf::Vector2f pos)
{
	//if (tile == nullptr)Logger::e("Crtitical error! Tile pointer is null!!");return;
	if (tiledef == nullptr)
	{
		this->name = "0";
		this->is_blocking = false;
		this->definition = nullptr;
		this->singleImage = true;
		this->tile = tile;
		this->tileRect = sf::IntRect();
		this->connectGroup = "";
		this->health = -1;
		return;
	}
	this->name = tiledef->name;
	this->singleImage = tiledef->singleImage;
	this->definition = tiledef;
	this->is_blocking = tiledef->is_blocking;
	this->tile = tile;
	this->tileRect = tiledef->tileRect;
	this->connectGroup = tiledef->connectGroup;
	this->health = tiledef->health;
	setPosition(pos);
}
bool Tile::isSameGroup(Tile & tile)
{
	if (tile.definition == nullptr || this->definition == nullptr)return false;

	if (tile.definition->connectGroup == "-1")
	{
		return tile.name == this->name;
	}
	else return tile.definition->connectGroup == this->definition->connectGroup;
}
Particle Tile::getRandomParticle()
{
	Particle p;
	p.lifetime = 3;

	int randx = position.x - 16 + std::rand() % 32;
	int randy = position.y - 16 + std::rand() % 32;

	p.position.x = randx;
	p.position.y = randy;

	randx = -100 + std::rand() % 200;
	randy = -100 + std::rand() % 200;

	p.velocity.x = randx;
	p.velocity.y = randy;
	return p;
}
sf::Color Tile::getRandomParticleColor()
{
	if (this->definition != nullptr) return definition->getRandomColor();
	return sf::Color();
}
sf::FloatRect Tile::getCollisionBox()
{
	return sf::FloatRect(position - sf::Vector2f(16, 16), sf::Vector2f(32, 32));
}
void Tile::setDisplayType(bool LT, bool T, bool TR, bool L, bool R, bool LB, bool B, bool RB)
{
	if (definition == nullptr)
	{
		resetVertexPosition();
		return;
	}
	if (singleImage)
	{
		auto r = definition->getInnerRect();
		tile[0]->texCoords = sf::Vector2f(r.left, r.top);
		tile[1]->texCoords = sf::Vector2f(r.left + r.width, r.top);
		tile[2]->texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
		tile[3]->texCoords = sf::Vector2f(r.left, r.top + r.height);
		return;
	}
	auto r = definition->getLTRect(L, LT, T);
	tile[0]->texCoords = sf::Vector2f(r.left, r.top);
	tile[1]->texCoords = sf::Vector2f(r.left + r.width, r.top);
	tile[2]->texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
	tile[3]->texCoords = sf::Vector2f(r.left, r.top + r.height);

	r = definition->getRTRect(T, TR, R);
	tile[4]->texCoords = sf::Vector2f(r.left, r.top);
	tile[5]->texCoords = sf::Vector2f(r.left + r.width, r.top);
	tile[6]->texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
	tile[7]->texCoords = sf::Vector2f(r.left, r.top + r.height);

	r = definition->getLBRect(B, LB, L);
	tile[8]->texCoords = sf::Vector2f(r.left, r.top);
	tile[9]->texCoords = sf::Vector2f(r.left + r.width, r.top);
	tile[10]->texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
	tile[11]->texCoords = sf::Vector2f(r.left, r.top + r.height);

	r = definition->getRBRect(R, RB, B);
	tile[12]->texCoords = sf::Vector2f(r.left, r.top);
	tile[13]->texCoords = sf::Vector2f(r.left + r.width, r.top);
	tile[14]->texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
	tile[15]->texCoords = sf::Vector2f(r.left, r.top + r.height);
}

void Tile::setPosition(sf::Vector2f pos)
{
	position = pos;
	if (tile.size() < 16)
	{
		//Logger::e("Size of tile vector is to small. Current is " + std::to_string(tile.size()));
		return;
	}
	sf::Vector2u tileSize(32, 32);

	if (singleImage)
	{
		tile[0]->position = sf::Vector2f(pos.x + tileRect.left, pos.y + tileRect.top);
		tile[1]->position = sf::Vector2f(pos.x + tileRect.left + tileRect.width, pos.y + tileRect.top);
		tile[2]->position = sf::Vector2f(pos.x + tileRect.left + tileRect.width, pos.y + tileRect.top + tileRect.height);
		tile[3]->position = sf::Vector2f(pos.x + tileRect.left, pos.y + tileRect.top + tileRect.height);
		// define its 4 corners
		/*tile[0]->position = sf::Vector2f(pos.x - tileSize.x / 2, pos.y - tileSize.y / 2);
		tile[1]->position = sf::Vector2f(pos.x + tileSize.x / 2, pos.y - tileSize.y / 2);
		tile[2]->position = sf::Vector2f(pos.x + tileSize.x / 2, pos.y + tileSize.y / 2);
		tile[3]->position = sf::Vector2f(pos.x - tileSize.x / 2, pos.y + tileSize.y / 2);*/

		tile[4]->position = sf::Vector2f(0, 0);
		tile[5]->position = sf::Vector2f(0, 0);
		tile[6]->position = sf::Vector2f(0, 0);
		tile[7]->position = sf::Vector2f(0, 0);

		tile[8]->position = sf::Vector2f(0, 0);
		tile[9]->position = sf::Vector2f(0, 0);
		tile[10]->position = sf::Vector2f(0, 0);
		tile[11]->position = sf::Vector2f(0, 0);

		tile[12]->position = sf::Vector2f(0, 0);
		tile[13]->position = sf::Vector2f(0, 0);
		tile[14]->position = sf::Vector2f(0, 0);
		tile[15]->position = sf::Vector2f(0, 0);
	}
	else
	{
		tile[0]->position = sf::Vector2f(pos.x + tileRect.left, pos.y + tileRect.top);
		tile[1]->position = sf::Vector2f(pos.x, pos.y + tileRect.top);
		tile[2]->position = sf::Vector2f(pos.x, pos.y);
		tile[3]->position = sf::Vector2f(pos.x + tileRect.left, pos.y);

		tile[4]->position = sf::Vector2f(pos.x, pos.y + tileRect.top);
		tile[5]->position = sf::Vector2f(pos.x + tileRect.left + tileRect.width, pos.y + tileRect.top);
		tile[6]->position = sf::Vector2f(pos.x + tileRect.left + tileRect.width, pos.y);
		tile[7]->position = sf::Vector2f(pos.x, pos.y);

		tile[8]->position = sf::Vector2f(pos.x + tileRect.left, pos.y);
		tile[9]->position = sf::Vector2f(pos.x, pos.y);
		tile[10]->position = sf::Vector2f(pos.x, pos.y + tileRect.top + tileRect.height);
		tile[11]->position = sf::Vector2f(pos.x + tileRect.left, pos.y + tileRect.top + tileRect.height);

		tile[12]->position = sf::Vector2f(pos.x, pos.y);
		tile[13]->position = sf::Vector2f(pos.x + tileRect.left + tileRect.width, pos.y);
		tile[14]->position = sf::Vector2f(pos.x + tileRect.left + tileRect.width, pos.y + tileRect.top + tileRect.height);
		tile[15]->position = sf::Vector2f(pos.x, pos.y + tileRect.top + tileRect.height);
		// define its 16 corners
		/*
		tile[0]->position = sf::Vector2f(pos.x - tileSize.x / 2, pos.y - tileSize.y / 2);
		tile[1]->position = sf::Vector2f(pos.x, pos.y - tileSize.y / 2);
		tile[2]->position = sf::Vector2f(pos.x, pos.y);
		tile[3]->position = sf::Vector2f(pos.x - tileSize.x / 2, pos.y);

		tile[4]->position = sf::Vector2f(pos.x, pos.y - tileSize.y / 2);
		tile[5]->position = sf::Vector2f(pos.x + tileSize.x / 2, pos.y - tileSize.y / 2);
		tile[6]->position = sf::Vector2f(pos.x + tileSize.x / 2, pos.y);
		tile[7]->position = sf::Vector2f(pos.x, pos.y);

		tile[8]->position = sf::Vector2f(pos.x - tileSize.x / 2, pos.y);
		tile[9]->position = sf::Vector2f(pos.x, pos.y);
		tile[10]->position = sf::Vector2f(pos.x, pos.y + tileSize.y / 2);
		tile[11]->position = sf::Vector2f(pos.x - tileSize.x / 2, pos.y + tileSize.y / 2);

		tile[12]->position = sf::Vector2f(pos.x, pos.y);
		tile[13]->position = sf::Vector2f(pos.x + tileSize.x / 2, pos.y);
		tile[14]->position = sf::Vector2f(pos.x + tileSize.x / 2, pos.y + tileSize.y / 2);
		tile[15]->position = sf::Vector2f(pos.x, pos.y + tileSize.y / 2);*/
	}
}

void Tile::damage(int health)
{
	this->health -= health;
	if (this->health <= 0)
	{
		destroy();
	}
}

void Tile::destroy()
{
	this->is_destroyed = true;
	this->is_blocking = false;
	resetVertexPosition();
}

void Tile::resetVertexPosition()
{
	if (tile.size() != 16)return;
	tile[0]->position = sf::Vector2f(0, 0);
	tile[1]->position = sf::Vector2f(0, 0);
	tile[2]->position = sf::Vector2f(0, 0);
	tile[3]->position = sf::Vector2f(0, 0);

	tile[4]->position = sf::Vector2f(0, 0);
	tile[5]->position = sf::Vector2f(0, 0);
	tile[6]->position = sf::Vector2f(0, 0);
	tile[7]->position = sf::Vector2f(0, 0);

	tile[8]->position = sf::Vector2f(0, 0);
	tile[9]->position = sf::Vector2f(0, 0);
	tile[10]->position = sf::Vector2f(0, 0);
	tile[11]->position = sf::Vector2f(0, 0);

	tile[12]->position = sf::Vector2f(0, 0);
	tile[13]->position = sf::Vector2f(0, 0);
	tile[14]->position = sf::Vector2f(0, 0);
	tile[15]->position = sf::Vector2f(0, 0);
}

/*
Tile::Tile()
{
	this->name = "0";
	this->is_blocking = false;
	this->definition = nullptr;
	this->singleImage = true;
	tilevertex = sf::VertexArray(sf::Quads, 4);
}

Tile::Tile(TileDefinition * tiledef,sf::Vector2f pos)
{
	if (tiledef == nullptr)
	{
		this->name = "0";
		this->is_blocking = false;
		this->definition = nullptr;
		this->singleImage = true;
		tilevertex = sf::VertexArray(sf::Quads, 16);
		this->setPosition(pos);
		return;
	}
	this->name = tiledef->name;
	this->singleImage = tiledef->singleImage;
	this->definition = tiledef;
	this->is_blocking = tiledef->is_blocking;
	if (singleImage)
	{
		tilevertex = sf::VertexArray(sf::Quads, 16);
	}
	else
	{
		tilevertex = sf::VertexArray(sf::Quads, 16);
	}
	this->setPosition(pos);
}

Tile::~Tile()
{
}

void Tile::draw(sf::RenderTarget & window)
{
	if (definition == nullptr)return;
	if (definition->texture == nullptr)return;
	window.draw(tilevertex, definition->texture);
}

void Tile::setPosition(sf::Vector2f pos)
{
	sf::Vector2u tileSize(32, 32);
	Entity::setPosition(pos);
	if (singleImage)
	{
		// define its 4 corners
		tilevertex[0].position = sf::Vector2f(pos.x - tileSize.x / 2, pos.y - tileSize.y / 2);
		tilevertex[1].position = sf::Vector2f(pos.x + tileSize.x / 2, pos.y - tileSize.y / 2);
		tilevertex[2].position = sf::Vector2f(pos.x + tileSize.x / 2, pos.y + tileSize.y / 2);
		tilevertex[3].position = sf::Vector2f(pos.x - tileSize.x / 2, pos.y + tileSize.y / 2);

		tilevertex[4].position = sf::Vector2f(0, 0);
		tilevertex[5].position = sf::Vector2f(0, 0);
		tilevertex[6].position = sf::Vector2f(0, 0);
		tilevertex[7].position = sf::Vector2f(0, 0);

		tilevertex[8].position = sf::Vector2f(0, 0);
		tilevertex[9].position = sf::Vector2f(0, 0);
		tilevertex[10].position = sf::Vector2f(0, 0);
		tilevertex[11].position = sf::Vector2f(0, 0);

		tilevertex[12].position = sf::Vector2f(0, 0);
		tilevertex[13].position = sf::Vector2f(0, 0);
		tilevertex[14].position = sf::Vector2f(0, 0);
		tilevertex[15].position = sf::Vector2f(0, 0);
	}
	else
	{
		// define its 16 corners
		tilevertex[0].position = sf::Vector2f(pos.x - tileSize.x / 2, pos.y - tileSize.y / 2);
		tilevertex[1].position = sf::Vector2f(pos.x , pos.y - tileSize.y / 2);
		tilevertex[2].position = sf::Vector2f(pos.x , pos.y);
		tilevertex[3].position = sf::Vector2f(pos.x - tileSize.x / 2, pos.y);

		tilevertex[4].position = sf::Vector2f(pos.x , pos.y - tileSize.y / 2);
		tilevertex[5].position = sf::Vector2f(pos.x + tileSize.x / 2, pos.y - tileSize.y / 2);
		tilevertex[6].position = sf::Vector2f(pos.x + tileSize.x / 2, pos.y);
		tilevertex[7].position = sf::Vector2f(pos.x , pos.y);

		tilevertex[8].position = sf::Vector2f(pos.x - tileSize.x / 2, pos.y);
		tilevertex[9].position = sf::Vector2f(pos.x , pos.y);
		tilevertex[10].position = sf::Vector2f(pos.x, pos.y + tileSize.y / 2);
		tilevertex[11].position = sf::Vector2f(pos.x - tileSize.x/2, pos.y + tileSize.y / 2);

		tilevertex[12].position = sf::Vector2f(pos.x , pos.y);
		tilevertex[13].position = sf::Vector2f(pos.x + tileSize.x / 2, pos.y);
		tilevertex[14].position = sf::Vector2f(pos.x + tileSize.x / 2, pos.y + tileSize.y / 2);
		tilevertex[15].position = sf::Vector2f(pos.x , pos.y + tileSize.y / 2);
	}
}

void Tile::setDisplayType(bool LT, bool T, bool TR, bool L, bool R, bool LB, bool B, bool RB)
{
	if (singleImage)return;
	if (definition == nullptr)return;

	auto r = definition->getLTRect(L,LT,T);
	tilevertex[0].texCoords = sf::Vector2f(r.left,r.top);
	tilevertex[1].texCoords = sf::Vector2f(r.left+r.width,r.top);
	tilevertex[2].texCoords = sf::Vector2f(r.left+r.width, r.top+r.height);
	tilevertex[3].texCoords = sf::Vector2f(r.left, r.top+r.height);

	r = definition->getRTRect(T, TR, R);
	tilevertex[4].texCoords = sf::Vector2f(r.left, r.top);
	tilevertex[5].texCoords = sf::Vector2f(r.left + r.width, r.top);
	tilevertex[6].texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
	tilevertex[7].texCoords = sf::Vector2f(r.left, r.top + r.height);

	r = definition->getLBRect(B, LB, L);
	tilevertex[8].texCoords = sf::Vector2f(r.left, r.top);
	tilevertex[9].texCoords = sf::Vector2f(r.left + r.width, r.top);
	tilevertex[10].texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
	tilevertex[11].texCoords = sf::Vector2f(r.left, r.top + r.height);

	r = definition->getRBRect(R, RB, B);
	tilevertex[12].texCoords = sf::Vector2f(r.left, r.top);
	tilevertex[13].texCoords = sf::Vector2f(r.left + r.width, r.top);
	tilevertex[14].texCoords = sf::Vector2f(r.left + r.width, r.top + r.height);
	tilevertex[15].texCoords = sf::Vector2f(r.left, r.top + r.height);
}
*/