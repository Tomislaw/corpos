#include "Soldier.hpp"
#include "game\map\Tilemap.hpp"
#include "game\engine\EntityList.hpp"





Soldier::~Soldier()
{
}

bool Soldier::setCharacter(TextElement * element)
{
	if (element == nullptr)return false;
	this->Character::setCharacter(element);

	//Set head part of soldier
	auto varSpriteHead = element->getVariableByName("SpriteHead");
	if (varSpriteHead != nullptr)
	{
		std::string sprite1 = varSpriteHead->toString(0);
		this->head = GameSprite(*EntityList::getSpriteDefinition(sprite1));

		//Set offset of that part
		auto var1 = element->getVariableByName("HeadPos");
		if(var1!=nullptr)
			headOffset = sf::Vector2f(var1->toFloat(0), var1->toFloat(1));
		this->head.attachToEntityOffset(this, headOffset);
	}
	else Logger::e("SpriteHead in " + name + " not found!");

	//Set torse part of soldier
	auto varSpriteTorse = element->getVariableByName("SpriteTorse");
	if (varSpriteTorse != nullptr)
	{
		std::string sprite2 = varSpriteTorse->toString(0);
		this->torse = GameSprite(*EntityList::getSpriteDefinition(sprite2));

		//Set offset of that part
		auto var2 = element->getVariableByName("TorsePos");
		if (var2 != nullptr)
			torseOffset = sf::Vector2f(var2->toFloat(0), var2->toFloat(1));
		this->torse.attachToEntityOffset(this, torseOffset);
	}
	else Logger::e("SpriteTorse in " + name + " not found!");

	//Set legs part of soldier
	auto varSpriteLegs = element->getVariableByName("SpriteLegs");
	if (varSpriteTorse != nullptr)
	{
		std::string sprite3 = varSpriteLegs->toString(0);
		this->legs = GameSprite(*EntityList::getSpriteDefinition(sprite3));

		//Set offset of that part
		auto var3 = element->getVariableByName("LegsPos");
		if (var3 != nullptr)
			legsOffset = sf::Vector2f(var3->toFloat(0), var3->toFloat(1));
		this->legs.attachToEntityOffset(this, legsOffset);
	}
	else Logger::e("SpriteLegs in " + name + " not found!");

	//Set left hand part of soldier
	auto varSpriteLHand = element->getVariableByName("SpriteLHand");
	if (varSpriteTorse != nullptr)
	{
		std::string sprite4 = varSpriteLHand->toString(0);
		this->lhand = GameSprite(*EntityList::getSpriteDefinition(sprite4));

		//Set offset of that part
		auto var4 = element->getVariableByName("LHandPos");
		if (var4 != nullptr)
			lhandOffset = sf::Vector2f(var4->toFloat(0), var4->toFloat(1));
		this->lhand.attachToEntityOffset(this, lhandOffset);
	}
	else Logger::e("SpriteLHand in " + name + " not found!");

	headOrigin = head.GetSprite().getOrigin();
	lhandOrigin = lhand.GetSprite().getOrigin();
	torseOrigin = torse.GetSprite().getOrigin();
	legsOrigin = legs.GetSprite().getOrigin();

	//TODO: make weapon
	weapontest = GameSprite(*EntityList::getSpriteDefinition("testweapon1"));
	weaponOrigin = weapontest.GetSprite().getOrigin();
	weaponOffset = sf::Vector2f(1,20);
	this->weapontest.attachToEntityOffset(this, weaponOffset);


	test.attachToEntity(&weapontest);
	return true;
}

void Soldier::draw(sf::RenderTarget & window)
{
	Character::draw(window);
	legs.draw(window);
	lhand.draw(window);
	torse.draw(window);
	head.draw(window);
	weapontest.draw(window);
	//drawDebugData(window);
	test.draw(window);
	test.drawDebugData(window);
}

void Soldier::update(float timew)
{
	Character::update(timew);
	legs.update(timew);
	lhand.update(timew);
	torse.update(timew);
	head.update(timew);
	weapontest.update(timew);
	test.update(timew);
}

void Soldier::aim(sf::Vector2f pos)
{
	test.aim(pos);

	float headangle = atan2(head.getPosition().y - pos.y, head.getPosition().x - pos.x) * 180 / 3.14;
	float armangle = atan2(lhand.getPosition().y - pos.y, lhand.getPosition().x - pos.x) * 180 / 3.14;
	float weaponangle = atan2(weapontest.getPosition().y - pos.y, weapontest.getPosition().x - pos.x) * 180 / 3.14;
	if (pos.x> getPosition().x)isTurnedLeft = false;
	else isTurnedLeft = true;
	if (!isTurnedLeft)
	{
		armangle += 180;
		headangle += 180;
		weaponangle += 180;

		if (headangle > 70 && headangle < 250)headangle = 70;
		if (headangle < 325 && headangle > 90)headangle = 325;
		if (armangle > 180)armangle -= (360-armangle)*0.6;
	}
	else
	{
		if (headangle > 35)headangle = 35;
		if (headangle < -70)headangle = -70;
		if (armangle > 0)armangle *= 1.6;
	}
	head.GetSprite().setRotation(headangle);
	lhand.GetSprite().setRotation(armangle);
	weapontest.GetSprite().setRotation(weaponangle);
}

void Soldier::startAttack()
{
	test.startFire();
}

void Soldier::stopAttack()
{
	test.stopFire();
}

void Soldier::special(unsigned int type)
{
	switch (type)
	{
	case Character::RELOAD:
		test.reload();
		break;
	}
}

void Soldier::setAnimation()
{
	
	//Character::setAnimation();
	if (walk_speed.x == 0 && velocity.y == 0)
	{
		if (isTurnedLeft)
		{
			legs.SetAnimation("idle_left");
		}
		else
		{
			legs.SetAnimation("idle_right");
		}
	}
	else
	{
		if (velocity.y == 0)
		{
			if (isTurnedLeft)
			{
				legs.SetAnimation("walk_left");
			}
			else
			{
				legs.SetAnimation("walk_right");
			}
		}
		else
		{
			if (isTurnedLeft)
			{
				legs.SetAnimation("jump_left");
			}
			else
			{
				legs.SetAnimation("jump_right");
			}
		}
	}

	if (isTurnedLeft)
	{
		head.SetAnimation("left");
		torse.SetAnimation("left");
		lhand.SetAnimation("left");

		head.GetSprite().setOrigin(head.GetSprite().getLocalBounds().width - headOrigin.x, headOrigin.y);
		torse.GetSprite().setOrigin(torse.GetSprite().getLocalBounds().width - torseOrigin.x, torseOrigin.y);
		lhand.GetSprite().setOrigin(lhand.GetSprite().getLocalBounds().width - lhandOrigin.x, lhandOrigin.y);
		legs.GetSprite().setOrigin(legs.GetSprite().getLocalBounds().width - legsOrigin.x, legsOrigin.y);

		int x = - lhandOffset.x;
		lhand.setAttachOffset(sf::Vector2f(x,lhandOffset.y));

		x = - torseOffset.x;
		torse.setAttachOffset(sf::Vector2f(x, torseOffset.y));

		x = - headOffset.x;
		head.setAttachOffset(sf::Vector2f(x, headOffset.y));

		x = - legsOffset.x;
		legs.setAttachOffset(sf::Vector2f(x, legsOffset.y));

		weapontest.SetAnimation("left");
		x = -weaponOffset.x;
		weapontest.setAttachOffset(sf::Vector2f(x, weaponOffset.y));
		weapontest.GetSprite().setOrigin(weapontest.GetSprite().getLocalBounds().width - weaponOrigin.x, weaponOrigin.y);
	}
	else
	{
		legs.setAttachOffset(legsOffset);
		head.SetAnimation("right");
		head.setAttachOffset(headOffset);
		torse.SetAnimation("right");
		torse.setAttachOffset(torseOffset);
		lhand.SetAnimation("right");
		lhand.setAttachOffset(lhandOffset);

		head.GetSprite().setOrigin(headOrigin);
		legs.GetSprite().setOrigin(legsOrigin);
		lhand.GetSprite().setOrigin(lhandOrigin);
		torse.GetSprite().setOrigin(torseOrigin);

		weapontest.SetAnimation("right");
		weapontest.setAttachOffset(weaponOffset);
		weapontest.GetSprite().setOrigin(weaponOrigin);
	}
}
