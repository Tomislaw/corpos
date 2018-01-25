#include "Prop.hpp"
#include "game\utility\Logger.hpp"
#include "game\engine\Player.hpp"
#include "game\engine\Prop.hpp"
#include "EntityList.hpp"

Prop::Prop()
{
}

Prop::Prop(TextElement * file) : Damageable(file)
{
	if (file == nullptr)return;



	is_collidable = false;

	// Set collidable flag
	auto varCollidable = file->getVariableByName("Collidable");
	if (varCollidable != nullptr)
		is_collidable = varCollidable->toInt(0);

	if(is_collidable)
	{ 
		setDamageable(file);

		//Set collision box
		auto var = file->getVariableByName("CollisionBox");
		if(var != nullptr)
		{ 
			this->collisionBox.left = var->toFloat(0);
			this->collisionBox.top = var->toFloat(1);
			this->collisionBox.width = var->toFloat(2);
			this->collisionBox.height = var->toFloat(3);
		}
		else Logger::e("Damageable entity " + name + " dont have CollisionBox variable.");
	}

	// Set sprite
	auto varSprite = file->getVariableByName("Sprite");
	if(varSprite != nullptr)
	{ 
		std::string spr = varSprite->toString(0);
		auto x = EntityList::getSpriteDefinition(spr);
		if (x == nullptr)
		{
			Logger::e("Sprite " + spr + " not found!");
			return;
		}
		sprite = GameSprite(*x);
	}

	//Set sprite offset
	auto sproff = file->getVariableByName("Sprite_offest");
	if(sproff!= nullptr)
	{ 
		sf::Vector2f spriteoffset;
		spriteoffset.x = sproff->toFloat(0);
		spriteoffset.y = sproff->toFloat(1);
		sprite.attachToEntityOffset(this, spriteoffset);
	}
	else sprite.attachToEntity(this);
}


Prop::~Prop()
{
}

void Prop::resolveCollision()
{
}

void Prop::draw(sf::RenderTarget & window)
{
	sprite.draw(window);
}

void Prop::update(float time)
{
	Entity::update(time);
	this->sprite.update(time);
}

bool Prop::bulletCollision(Bullet * bullet)
{
	sf::FloatRect cb = sf::FloatRect(position.x + collisionBox.left, collisionBox.top + position.y, collisionBox.width, collisionBox.height);
	bool contains = (cb.contains(bullet->getPosition()) || cb.contains(bullet->getPreviousPosition()));

	if (contains == false)
	{
		// do line interesct here
	}


	if (contains)
	{

		int damage = bullet->getDamage();
		bullet->decreaseDamage(getHealth());
		this->damage(damage);

		if (bullet->isDestroyed() || bullet->isDuringDestroying())
		{
			bullet->correctBulletPositionAfterDestroy(collisionBox);
		}
		
		return true;
	}
	return false;
}

bool Prop::contains(sf::FloatRect & rect)
{
	return rect.intersects(sf::FloatRect(position.x + collisionBox.left, collisionBox.top + position.y, collisionBox.width, collisionBox.height));
}
