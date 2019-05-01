/////////Tile definition
#include "TileDefinition.hpp"

using namespace corpos;

void TileDefinition::setTile(TextElement * t, const sf::Texture * texture, std::string textureName)
{
	this->texture = texture;

	// Set name
	auto varname = t->get("Name");
	if (!varname.isEmpty())name = varname.toString(0);
	else Logger::e("Tile is missing name");

	//Set health
	health = t->get("Health").toFloat(0);

	this->textureName = textureName;

	//Set is blocking
	auto varIsBlocking = t->get("Block");
	if (!varIsBlocking.isEmpty())
		this->is_blocking = varIsBlocking.toInt(0);
	else this->is_blocking = false;

	//Set is single sprite
	auto varIsSingleImage = t->get("SingleImage");
	if (!varIsSingleImage.isEmpty())
		this->singleImage = varIsSingleImage.toInt(0);
	else this->singleImage = true;

	//Set background tile
	auto varBackground = t->get("Background");
	if (!varBackground.isEmpty())
		this->backgroundTile = varBackground.toString(0);
	else this->backgroundTile = "0";

	auto varConnectGroup = t->get("ConnectGroup");
	if (!varConnectGroup.isEmpty())
		connectGroup = varConnectGroup.toString(0);
	else connectGroup = "-1";

	auto r = t->get("TileRect");

	if (r.isEmpty())
	{
		this->tileRect = sf::IntRect(-16, -16, 32, 32);
	}
	else
	{
		auto tileRectInts = r.toInt();
		if (tileRectInts.size() < 4)
		{
			Logger::e("TileRect is invalid");
		}
		this->tileRect = sf::IntRect(tileRectInts.at(0), tileRectInts.at(1), tileRectInts.at(2), tileRectInts.at(3));
	}
	if (!this->singleImage)
	{
		////Top
		auto v = t->get("RT").toRect<int>();
		for (int i = 0; i < v.size(); i++)
			this->RT.push_back(v[i]);

		v = t->get("LT").toRect<int>();
		for (int i = 0; i < v.size(); i++)
			this->LT.push_back(v[i]);

		v = t->get("T").toRect<int>();
		for (int i = 0; i < v.size(); i++)
			this->T.push_back(v[i]);

		////Center
		v = t->get("L").toRect<int>();
		for (int i = 0; i < v.size(); i++)
			this->L.push_back(v[i]);

		v = t->get("C").toRect<int>();
		for (int i = 0; i < v.size(); i++)
			this->C.push_back(v[i]);;

		v = t->get("R").toRect<int>();
		for (int i = 0; i < v.size(); i++)
			this->R.push_back(v[i]);

		//Bottom
		v = t->get("LB").toRect<int>();
		for (int i = 0; i < v.size(); i++)
			this->LB.push_back(v[i]);

		v = t->get("B").toRect<int>();
		for (int i = 0; i < v.size(); i++)
			this->B.push_back(v[i]);

		v = t->get("RB").toRect<int>();
		for (int i = 0; i < v.size(); i++)
			this->RB.push_back(v[i]);

		// inner
		v = t->get("ILB").toRect<int>();
		for (int i = 0; i < v.size(); i++)
			this->ILB.push_back(v[i]);

		v = t->get("ILT").toRect<int>();
		for (int i = 0; i < v.size(); i++)
			this->ILT.push_back(v[i]);

		v = t->get("IRT").toRect<int>();
		for (int i = 0; i < v.size(); i++)

			this->IRT.push_back(v[i]);

		v = t->get("IRB").toRect<int>();
		for (int i = 0; i < v.size(); i++)
			this->IRB.push_back(v[i]);
	}

	auto v = t->get("inner").toRect<int>();
	for (int i = 0; i < v.size(); i++)
		this->inner.push_back(v[i]);

	if (texture != nullptr && C.size() > 0)
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
		for (int i = 0; i < 4; i++)
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
	data += "name:" + this->name;
	data += "\ntexture name:" + this->textureName;
	data += "\nhealth:" + std::to_string(this->health);
	data += "\nblock:" + std::to_string(this->is_blocking);
	return data;
}

TextElement TileDefinition::generateTextElement()
{
	TextElement element;
	element.name = "TILE";

	element["Name"] += TextItem(this->name);
	element["Health"] += TextItem(this->health);
	element["Block"] += TextItem(std::to_string(this->is_blocking));
	element["SingleImage"] += TextItem(std::to_string(this->singleImage));
	element["Background"] += TextItem(this->backgroundTile);
	element["ConnectGroup"] += TextItem(this->connectGroup);

	auto addRectangleData = [](TextElement & element, sf::IntRect rect, std::string name)->void
	{
		element[name] += TextItem(rect);
	};

	addRectangleData(element, tileRect, "TileRect");
	for each (auto rect in L)addRectangleData(element, rect, "L");
	for each (auto rect in R)addRectangleData(element, rect, "R");
	for each (auto rect in T)addRectangleData(element, rect, "T");
	for each (auto rect in B)addRectangleData(element, rect, "B");
	for each (auto rect in LT)addRectangleData(element, rect, "LT");
	for each (auto rect in RT)addRectangleData(element, rect, "RT");
	for each (auto rect in LB)addRectangleData(element, rect, "LB");
	for each (auto rect in RB)addRectangleData(element, rect, "RB");
	for each (auto rect in IRB)addRectangleData(element, rect, "IRB");
	for each (auto rect in IRT)addRectangleData(element, rect, "IRT");
	for each (auto rect in ILT)addRectangleData(element, rect, "ILT");
	for each (auto rect in ILB)addRectangleData(element, rect, "ILB");
	for each (auto rect in inner)addRectangleData(element, rect, "inner");
	for each (auto rect in C)addRectangleData(element, rect, "C");

	return element;
}