#include "Soldier.hpp"
#include "game\map\Tilemap.hpp"
#include "game\engine\EntityList.hpp"





Soldier::~Soldier()
{
}

bool Soldier::setCharacter(TextElement * element)
{
	this->Character::setCharacter(element);
	std::string sprite1 = element->getVariableByName("SpriteHead")->var[0];
	this->head = GameSprite(*EntityList::getSpriteDefinition(sprite1));
	auto var1 = element->getVariableByName("HeadPos");
	headOffset = sf::Vector2f(var1->toFloat(0), var1->toFloat(1));
	this->head.attachToEntityOffset(this, headOffset);

	std::string sprite2 = element->getVariableByName("SpriteTorse")->var[0];
	this->torse = GameSprite(*EntityList::getSpriteDefinition(sprite2));
	auto var2 = element->getVariableByName("TorsePos");
	torseOffset = sf::Vector2f(var2->toFloat(0), var2->toFloat(1));
	this->torse.attachToEntityOffset(this, torseOffset);

	std::string sprite3 = element->getVariableByName("SpriteLegs")->var[0];
	this->legs = GameSprite(*EntityList::getSpriteDefinition(sprite3));
	auto var3 = element->getVariableByName("LegsPos");
	legsOffset = sf::Vector2f(var3->toFloat(0), var3->toFloat(1));
	this->legs.attachToEntityOffset(this, legsOffset);

	std::string sprite4 = element->getVariableByName("SpriteLHand")->var[0];
	this->lhand = GameSprite(*EntityList::getSpriteDefinition(sprite4));
	auto var4 = element->getVariableByName("LHandPos");
	lhandOffset = sf::Vector2f(var4->toFloat(0), var4->toFloat(1));
	this->lhand.attachToEntityOffset(this, lhandOffset);

	headOrigin = head.GetSprite().getOrigin();
	lhandOrigin = lhand.GetSprite().getOrigin();
	torseOrigin = torse.GetSprite().getOrigin();
	legsOrigin = legs.GetSprite().getOrigin();

	weapontest = GameSprite(*EntityList::getSpriteDefinition("testweapon1"));
	weaponOrigin = weapontest.GetSprite().getOrigin();
	weaponOffset = sf::Vector2f(1,20);
	this->weapontest.attachToEntityOffset(this, weaponOffset);
	return false;
}

void Soldier::draw(sf::RenderTarget & window)
{
	Character::draw(window);
	legs.draw(window);
	lhand.draw(window);
	torse.draw(window);
	head.draw(window);
	weapontest.draw(window);
	drawDebugData(window);
}

void Soldier::update(float timew)
{
	Character::update(timew);
	legs.update(timew);
	lhand.update(timew);
	torse.update(timew);
	head.update(timew);
	weapontest.update(timew);
	
}

void Soldier::aim(sf::Vector2f pos)
{
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

void Soldier::setAnimation()
{
	
	Character::setAnimation();
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
