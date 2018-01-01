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
	//health
	this->health = t->getVariableByName("Health")->toInt(0);
	this->maxHealth = t->getVariableByName("MaxHealth")->toInt(0);

	//flags
	if (maxHealth < 0) this->indestructable = true;
	else this->indestructable = false;
	if (maxHealth >= 0 && health <= 0)destroy();
	else destroyed = false;

	this->damageFilter = t->getVariableByName("DamageFilter")->toInt(0);
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

bool Damageable::bulletCollision(Bullet * bullet)
{

		if (destroyed || bullet->isDestroyed())return true;
		if (bulletCollisionTest(bullet->getPosition()))
		{
			//TODO: check filer
			this->damage(bullet->getDamage());
			bullet->destroy();
			return true;
		}
		return false;
}


Bullet::Bullet()
{
}

Bullet::Bullet(Bullet & bullet, sf::Vector2f position, sf::Vector2f velocity) : Entity("bullet", position, velocity)
{
	bulletSprite = GameSprite(bullet.bulletSprite);
	this->damage = damage;
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
	Entity::update(time);
	bulletSprite.GetSprite().setRotation(atan2(velocity.y, velocity.x) * 180 / 3.14159265359);

	bulletSprite.update(time);
}



bool Bullet::isDestroyed()
{
	return destroyed;
}

void Bullet::destroy()
{
	destroyed = true;
	velocity = sf::Vector2f();
}
