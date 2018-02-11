#include "Tile.hpp"

#include "game\engine\World.hpp"

Tile::Tile()
{
	this->name = "0";
	this->is_blocking = false;
	this->definition = nullptr;
	this->singleImage = true;
}


Tile::Tile(TileDefinition * tiledef, std::vector<sf::Vertex*> tile, sf::Vector2f pos)
{
	changeTile(tiledef,tile,pos);
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

	int randx = getPosition().x - 16 + std::rand() % 32;
	int randy = getPosition().y - 16 + std::rand() % 32;

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

	return sf::FloatRect(getPosition() - sf::Vector2f(16,16), sf::Vector2f(32, 32));
}
void Tile::setDisplayType(bool LT, bool T, bool TR, bool L, bool R, bool LB, bool B, bool RB)
{

	if (definition == nullptr )
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
	Entity::setPosition(pos);
	if (tile.size() < 16)
	{
		//Logger::e("Size of tile vector is to small. Current is " + std::to_string(tile.size()));
		return;
	}
	sf::Vector2u tileSize(32, 32);

	if (singleImage)
	{
		tile[0]->position = sf::Vector2f(pos.x + tileRect.left , pos.y + tileRect.top);
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
	if (tile.size()!= 16)return;
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



/////////Tile definition
void TileDefinition::setTile(TextElement * t, const sf::Texture * texture, std::string textureName)
{
	this->texture = texture;

	// Set name
	auto varname = t->getVariableByName("Name");
	if (varname != nullptr)name = varname->toString(0);
	else Logger::e("Tile is missing name");

	//Set health
	auto varHealth = t->getVariableByName("Health");
	if (varHealth != nullptr)
		health = varHealth->toFloat(0);
	else health = 0;

	this->texture_name = textureName;

	//Set is blocking
	auto varIsBlocking = t->getVariableByName("Block");
	if (varIsBlocking != nullptr)
		this->is_blocking = varIsBlocking->toInt(0);
	else this->is_blocking = false;

	//Set is single sprite
	this->singleImage = true;
	auto varIsSingleImage = t->getVariableByName("SingleImage");
	if (varIsSingleImage != nullptr)
		this->singleImage = varIsSingleImage->toInt(0);

	//Set background tile
	auto varBackground = t->getVariableByName("Background");
	if(varBackground!= nullptr)
		this->backgroundTile = varBackground->toString(0);
	else this->backgroundTile = "0";

	auto varConnectGroup = t->getVariableByName("ConnectGroup");
	if(varConnectGroup!=nullptr)
		connectGroup = varConnectGroup->toString(0);
	else connectGroup = "-1";

	auto r = t->getVariableByName("TileRect");

	if (r==nullptr)
	{
		this->tileRect = sf::IntRect(-16, -16, 32, 32);
	}
	else
	{
		auto tileRectInts = r->toInt();
		if (tileRectInts.size() < 4)
		{
			Logger::e("TileRect is invalid");
		}
		this->tileRect = sf::IntRect(tileRectInts.at(0), tileRectInts.at(1), tileRectInts.at(2), tileRectInts.at(3));
	}
	if (!this->singleImage)
	{
		////Top
		auto v =t->getAllVariablesByName("RT");
		for (int i = 0; i < v.size(); i++)
		{
			auto r = v[i]->toInt();
			this->RT.push_back(sf::IntRect(r.at(0), r.at(1), r.at(2), r.at(3)));
		}

		v = t->getAllVariablesByName("LT");
		for (int i = 0; i < v.size(); i++)
		{
			auto r = v[i]->toInt();
			this->LT.push_back(sf::IntRect(r.at(0), r.at(1), r.at(2), r.at(3)));
		}

		v = t->getAllVariablesByName("T");
		for (int i = 0; i < v.size(); i++)
		{
			auto r = v[i]->toInt();
			this->T.push_back(sf::IntRect(r.at(0), r.at(1), r.at(2), r.at(3)));
		}

		////Center
		v = t->getAllVariablesByName("L");
		for (int i = 0; i < v.size(); i++)
		{
			auto r = v[i]->toInt();
			this->L.push_back(sf::IntRect(r.at(0), r.at(1), r.at(2), r.at(3)));
		}

		v = t->getAllVariablesByName("C");
		for (int i = 0; i < v.size(); i++)
		{
			auto r = v[i]->toInt();
			this->C.push_back(sf::IntRect(r.at(0), r.at(1), r.at(2), r.at(3)));
		}
		v = t->getAllVariablesByName("R");
		for (int i = 0; i < v.size(); i++)
		{
			auto r = v[i]->toInt();
			this->R.push_back(sf::IntRect(r.at(0), r.at(1), r.at(2), r.at(3)));
		}

		//Bottom
		v = t->getAllVariablesByName("LB");
		for (int i = 0; i < v.size(); i++)
		{
			auto r = v[i]->toInt();
			this->LB.push_back(sf::IntRect(r.at(0), r.at(1), r.at(2), r.at(3)));
		}
		v = t->getAllVariablesByName("B");
		for (int i = 0; i < v.size(); i++)
		{
			auto r = v[i]->toInt();
			this->B.push_back(sf::IntRect(r.at(0), r.at(1), r.at(2), r.at(3)));
		}

		v = t->getAllVariablesByName("RB");
		for (int i = 0; i < v.size(); i++)
		{
			auto r = v[i]->toInt();
			this->RB.push_back(sf::IntRect(r.at(0), r.at(1), r.at(2), r.at(3)));
		}

		// inner
		v = t->getAllVariablesByName("ILB");
		for (int i = 0; i < v.size(); i++)
		{
			auto r = v[i]->toInt();
			this->ILB.push_back(sf::IntRect(r.at(0), r.at(1), r.at(2), r.at(3)));
		}
		v = t->getAllVariablesByName("ILT");
		for (int i = 0; i < v.size(); i++)
		{
			auto r = v[i]->toInt();
			this->ILT.push_back(sf::IntRect(r.at(0), r.at(1), r.at(2), r.at(3)));
		}

		v = t->getAllVariablesByName("IRT");
		for (int i = 0; i < v.size(); i++)
		{
			auto r = v[i]->toInt();
			this->IRT.push_back(sf::IntRect(r.at(0), r.at(1), r.at(2), r.at(3)));
		}
		v = t->getAllVariablesByName("IRB");
		for (int i = 0; i < v.size(); i++)
		{
			auto r = v[i]->toInt();
			this->IRB.push_back(sf::IntRect(r.at(0), r.at(1), r.at(2), r.at(3)));
		}


	}


	auto v = t->getAllVariablesByName("inner");
	for (int i = 0; i < v.size(); i++)
	{
		auto r = v[i]->toInt();
		this->inner.push_back(sf::IntRect(r.at(0), r.at(1), r.at(2), r.at(3)));
	}

	if (texture != nullptr && C.size()>0)
	{
		sf::IntRect ct;

		if (!singleImage)
		{
			ct = this->C.at(0);
		}
		else
		{
			if (inner.size() > 0)
			{
				ct = this->inner.at(0);
			}
			else
			{
				destroyParticleColors.push_back(sf::Color(255, 255, 255, 255));
				return;
			}
		}
		auto img = texture->copyToImage();
		for (int i = 0; i < 4;i++)
		{
			int randx = ct.left + std::rand() % ct.width;
			int randy = ct.top + std::rand() % ct.height;
			auto px = img.getPixel(randx, randy);
			destroyParticleColors.push_back(sf::Color(px.r, px.g, px.b, px.a));
		}
	}
	else
	{
		destroyParticleColors.push_back(sf::Color(255, 255, 255, 255));
	}

}

sf::IntRect TileDefinition::getLTRect(bool L, bool LT, bool T)
{
	//srand((unsigned)time(NULL));
	if (L == false && LT == false && T == false || L == false && LT == true && T == false)
	{
		int rand = std::rand() % this->LT.size();
		return this->LT.at(rand);
	}
	if (L == false && LT == false && T == true || L == false && LT == true && T == true)
	{
		int rand = std::rand() % this->L.size();
		return this->L.at(rand);
	}
	if (L == true && LT == false && T == false || L == true && LT == true && T == false)
	{
		int rand = std::rand() % this->T.size();
		return this->T.at(rand);
	}
	if (L == true && LT == false && T == true)
	{
		int rand = std::rand() % this->ILT.size();
		return this->ILT.at(rand);
	}
	if (L == true && LT == true && T == true)
	{
		int rand = std::rand() % this->C.size();
		return this->C.at(rand);
	}
	return sf::IntRect();
}

sf::IntRect TileDefinition::getRTRect(bool T, bool TR, bool R)
{
	//srand((unsigned)time(NULL));
	if (T == false && TR == false && R == false || T == false && TR == true && R == false)
	{
		int rand = std::rand() % this->RT.size();
		return this->RT.at(rand);
	}
	if (T == false && TR == false && R == true || T == false && TR == true && R == true)
	{
		int rand = std::rand() % this->T.size();
		return this->T.at(rand);
	}
	if (T == true && TR == false && R == false || T == true && TR == true && R == false)
	{
		int rand = std::rand() % this->R.size();
		return this->R.at(rand);
	}
	if (T == true && TR == false && R == true)
	{
		int rand = std::rand() % this->IRT.size();
		return this->IRT.at(rand);
	}
	if (T == true && TR == true && R == true)
	{
		int rand = std::rand() % this->C.size();
		return this->C.at(rand);
	}
	return sf::IntRect();
}

sf::IntRect TileDefinition::getRBRect(bool R, bool RB, bool B)
{
	//srand((unsigned)time(NULL));
	if (R == false && RB == false && B == false || R == false && RB == true && B == false)
	{
		int rand = std::rand() % this->RB.size();
		return this->RB.at(rand);
	}
	if (R == false && RB == false && B == true || R == false && RB == true && B == true)
	{
		int rand = std::rand() % this->R.size();
		return this->R.at(rand);
	}
	if (R == true && RB == false && B == false || R == true && RB == true && B == false)
	{
		int rand = std::rand() % this->B.size();
		return this->B.at(rand);
	}
	if (R == true && RB == false && B == true)
	{
		int rand = std::rand() % this->IRB.size();
		return this->IRB.at(rand);
	}
	if (R == true && RB == true && B == true)
	{
		int rand = std::rand() % this->C.size();
		return this->C.at(rand);
	}
	return sf::IntRect();
}

sf::IntRect TileDefinition::getLBRect(bool B, bool LB, bool L)
{
	//srand((unsigned)time(NULL));
	if (B == false && LB == false && L == false || B == false && LB == true && L == false)
	{
		int rand = std::rand() % this->LB.size();
		return this->LB.at(rand);
	}
	if (B == false && LB == false && L == true || B == false && LB == true && L == true)
	{
		int rand = std::rand() % this->B.size();
		return this->B.at(rand);
	}
	if (B == true && LB == false && L == false || B == true && LB == true && L == false)
	{
		int rand = std::rand() % this->L.size();
		return this->L.at(rand);
	}
	if (B == true && LB == false && L == true)
	{
		int rand = std::rand() % this->ILB.size();
		return this->ILB.at(rand);
	}
	if (B == true && LB == true && L == true)
	{
		int rand = std::rand() % this->C.size();
		return this->C.at(rand);
		
	}
	return sf::IntRect();
}

sf::IntRect TileDefinition::getInnerRect()
{
	//srand((unsigned)time(NULL));
	int rand = std::rand() % this->inner.size();
	return this->inner.at(rand);
}

const sf::Color & TileDefinition::getRandomColor()
{
	int rand = std::rand() % this->destroyParticleColors.size();
	return this->destroyParticleColors.at(rand);
}


std::string TileDefinition::toString()
{
	
	std::string data;
	data += "Name:" + this->name;
	data += "\nTexture name:" + this->texture_name;
	data += "\nHealth:" + std::to_string(this->health);
	data += "\nBlock:" + std::to_string(this->is_blocking);
	return data;
}
