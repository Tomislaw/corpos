#include "Soldier.hpp"
#include "game\map\Tilemap.hpp"
#include "game\engine\EntityList.hpp"
#include "game\engine\logic\ai\AiBasic.hpp"

//Main constructor TODO: add null pointer handling

Soldier::Soldier(TextElement * data, EntityList * ptr) : Character(data, ptr), test(ptr, Bullet("bullet_blue", 150, sf::Vector2f(), sf::Vector2f(0, 50)))
{
	ai = std::unique_ptr<AiBasic>(new AiBasic(*this));
	setCharacter(data);
}

Soldier::~Soldier()
{
}

bool Soldier::setCharacter(TextElement * element)
{
	if (element == nullptr)return false;

	navCharData.canUseLadder = true;

	//Set head part of soldier
	auto varSpriteHead = element->getVariableByName("SpriteHead");
	if (varSpriteHead != nullptr)
	{
		std::string sprite1 = varSpriteHead->toString(0);
		this->head = GameSprite(*GameAssetsManager::getSprite(sprite1));

		//Set offset of that part
		auto var1 = element->getVariableByName("HeadPos");
		if (var1 != nullptr)
			headOffset = sf::Vector2f(var1->toFloat(0), var1->toFloat(1));
		this->head.attachToEntityOffset(this, headOffset);
	}
	else Logger::e("SpriteHead in " + name + " not found!");

	//Set torse part of soldier
	auto varSpriteTorse = element->getVariableByName("SpriteTorse");
	if (varSpriteTorse != nullptr)
	{
		std::string sprite2 = varSpriteTorse->toString(0);
		this->torse = GameSprite(*GameAssetsManager::getSprite(sprite2));

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
		this->legs = GameSprite(*GameAssetsManager::getSprite(sprite3));

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
		this->lhand = GameSprite(*GameAssetsManager::getSprite(sprite4));

		//Set offset of that part
		auto var4 = element->getVariableByName("LHandPos");
		if (var4 != nullptr)
			lhandOffset = sf::Vector2f(var4->toFloat(0), var4->toFloat(1));
		this->lhand.attachToEntityOffset(this, lhandOffset);
	}
	else Logger::e("SpriteLHand in " + name + " not found!");

	headOrigin = head.getSprite().getOrigin();
	lhandOrigin = lhand.getSprite().getOrigin();
	torseOrigin = torse.getSprite().getOrigin();
	legsOrigin = legs.getSprite().getOrigin();

	//TODO: make weapon
	weapontest = GameSprite(*GameAssetsManager::getSprite("testweapon1"));
	weaponOrigin = weapontest.getSprite().getOrigin();
	weaponOffset = sf::Vector2f(1, 20);
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
	//test.drawDebugData(window);
	ai->drawDebugData(window);
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
	if (pos.x > getPosition().x)isTurnedLeft = false;
	else isTurnedLeft = true;
	if (!isTurnedLeft)
	{
		armangle += 180;
		headangle += 180;
		weaponangle += 180;

		if (headangle > 70 && headangle < 250)headangle = 70;
		if (headangle < 325 && headangle > 90)headangle = 325;
		if (armangle > 180)armangle -= (360 - armangle)*0.6;
	}
	else
	{
		if (headangle > 35)headangle = 35;
		if (headangle < -70)headangle = -70;
		if (armangle > 0)armangle *= 1.6;
	}
	head.getSprite().setRotation(headangle);
	lhand.getSprite().setRotation(armangle);
	weapontest.getSprite().setRotation(weaponangle);
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
			legs.setAnimation("idle_left");
		}
		else
		{
			legs.setAnimation("idle_right");
		}
	}
	else
	{
		if (velocity.y == 0)
		{
			if (isTurnedLeft)
			{
				legs.setAnimation("walk_left");
			}
			else
			{
				legs.setAnimation("walk_right");
			}
		}
		else
		{
			if (isTurnedLeft)
			{
				legs.setAnimation("jump_left");
			}
			else
			{
				legs.setAnimation("jump_right");
			}
		}
	}

	if (isTurnedLeft)
	{
		head.setAnimation("left");
		torse.setAnimation("left");
		lhand.setAnimation("left");

		head.getSprite().setOrigin(head.getSprite().getLocalBounds().width - headOrigin.x, headOrigin.y);
		torse.getSprite().setOrigin(torse.getSprite().getLocalBounds().width - torseOrigin.x, torseOrigin.y);
		lhand.getSprite().setOrigin(lhand.getSprite().getLocalBounds().width - lhandOrigin.x, lhandOrigin.y);
		legs.getSprite().setOrigin(legs.getSprite().getLocalBounds().width - legsOrigin.x, legsOrigin.y);

		int x = -lhandOffset.x;
		lhand.setAttachOffset(sf::Vector2f(x, lhandOffset.y));

		x = -torseOffset.x;
		torse.setAttachOffset(sf::Vector2f(x, torseOffset.y));

		x = -headOffset.x;
		head.setAttachOffset(sf::Vector2f(x, headOffset.y));

		x = -legsOffset.x;
		legs.setAttachOffset(sf::Vector2f(x, legsOffset.y));

		weapontest.setAnimation("left");
		x = -weaponOffset.x;
		weapontest.setAttachOffset(sf::Vector2f(x, weaponOffset.y));
		weapontest.getSprite().setOrigin(weapontest.getSprite().getLocalBounds().width - weaponOrigin.x, weaponOrigin.y);
	}
	else
	{
		legs.setAttachOffset(legsOffset);
		head.setAnimation("right");
		head.setAttachOffset(headOffset);
		torse.setAnimation("right");
		torse.setAttachOffset(torseOffset);
		lhand.setAnimation("right");
		lhand.setAttachOffset(lhandOffset);

		head.getSprite().setOrigin(headOrigin);
		legs.getSprite().setOrigin(legsOrigin);
		lhand.getSprite().setOrigin(lhandOrigin);
		torse.getSprite().setOrigin(torseOrigin);

		weapontest.setAnimation("right");
		weapontest.setAttachOffset(weaponOffset);
		weapontest.getSprite().setOrigin(weaponOrigin);
	}
}