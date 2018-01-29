#include "Damageable.hpp"
#include "EntityList.hpp"
#include <math.h>

Damageable::Damageable()
{
}

Damageable::Damageable(TextElement * t)
{
	
	this->setDamageable(t);
}


Damageable::~Damageable()
{
}

void Damageable::setDamageable(TextElement * t)
{
	if (t == nullptr)
	{
		return;
	}


	//collidable
	bool isCollidable = false;

	auto variableIsCollidable = t->getVariableByName("Collidable");
	if(variableIsCollidable!= nullptr) 
		isCollidable = variableIsCollidable->toInt(0);

	if (!isCollidable)
	{
		this->health = 0;
		this->maxHealth = 0;
		this->indestructable = true;
	}
	//health

	auto variableHealth = t->getVariableByName("Health");
	if (variableHealth != nullptr)
	{ 
		this->health = variableHealth->toInt(0);
		this->maxHealth = this->health;
	}
	else
	{
		this->health = -1;
		this->maxHealth = -1;

	}

	//DamageFilter
	auto variableDamagefilter = t->getVariableByName("DamageFilter");
	if (variableDamagefilter != nullptr)
	{
		this->damageFilter = variableDamagefilter->toInt(0);
	}
	else
	{
		this->damageFilter = -1;

	}


	//flags
	if (maxHealth < 0) this->indestructable = true;
	else this->indestructable = false;
	if (maxHealth >= 0 && health <= 0)destroy();
	else destroyed = false;

}

void Damageable::damage(int hp)
{
	if (indestructable)return;
	health -= hp;
	if (health < 0)destroy();
}

int Damageable::getHealth()
{
	return health;
}

int Damageable::getMaxHealth()
{
	return maxHealth;
}

void Damageable::setHealth(int health)
{
	this->health = health;
}

void Damageable::setMaxHealth(int health)
{
	this->maxHealth = health;
}

bool Damageable::isIndestructable()
{
	return indestructable;
}

void Damageable::setIndestructable(bool is_indestructable)
{
	indestructable = is_indestructable;
}

void Damageable::destroy()
{
	destroyed = true;
}

bool Damageable::isDestroyed()
{
	return destroyed;
}




Bullet::Bullet()
{
}

Bullet::Bullet(Bullet & bullet, sf::Vector2f position, sf::Vector2f velocity) : Entity("bullet", position, velocity)
{
	previousPosition = position;
	bulletSprite = GameSprite(bullet.bulletSprite);
	this->damage = bullet.damage;
	bulletSprite.attachToEntity(this);
	speed = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);
}

Bullet::Bullet(std::string bulletSpriteName, int damage, sf::Vector2f position, sf::Vector2f velocity) : Entity("bullet",position, velocity)
{


	bulletSprite = GameSprite(*EntityList::getSpriteDefinition(bulletSpriteName));
	this->damage = damage;
	bulletSprite.attachToEntity(this);
	speed = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);
}

void Bullet::draw(sf::RenderTarget & window)
{
	if (destroyed)return;
	bulletSprite.draw(window);

}

void Bullet::update(float time)
{
	if (destroyed)return;

	previousPosition = getPosition();
	Entity::update(time);
	bulletSprite.GetSprite().setRotation(atan2(velocity.y, velocity.x) * 180 / 3.14159265359);

	bulletSprite.update(time);
	if (startDestroyAnimation)
	{
		bulletSprite.SetAnimation("destroy");
		startDestroyAnimation = false;
	}
	if (duringDestroying)
	{
		if (bulletSprite.getCurrentAnimation()->is_finished())kill();
	}
}


bool Bullet::isDestroyed()
{
	return destroyed;
}

bool Bullet::isDuringDestroying()
{
	return duringDestroying;
}

void Bullet::destroy()
{
	duringDestroying = true;
	startDestroyAnimation = true;
	velocity = sf::Vector2f();
}

void Bullet::correctBulletPositionAfterDestroy(sf::FloatRect collisionBox)
{

	sf::Vector2f pos;
	pos.x = getPosition().x / 2 + getPreviousPosition().x / 2;
	pos.y = getPosition().y / 2 + getPreviousPosition().y / 2;
	//sf::Vector2f center(collisionBox.left + collisionBox.width / 2, collisionBox.top + collisionBox.height / 2);

	/*std::cout << collisionBox.left << " " << previousPosition.x << std::endl;
		//if(angleDeg>-45&& angleDeg<45)
		if (velocity.x < 0)
		{
			position.x = collisionBox.left;
		}
		else
		{
			position.x = collisionBox.left + collisionBox.width;
		}

	else
	{
		if (velocity.y < 0)
		{
			position.y = collisionBox.top;
		}
		else
		{
			position.y = collisionBox.top + collisionBox.height;
		}
	}*/
}

void Bullet::kill()
{
	destroyed = true;
}
