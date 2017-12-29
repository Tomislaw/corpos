#ifndef DAMAGEABLE_HPP
#define DAMAGEABLE_HPP
#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>
#include "game\graphics\GameSprite.hpp"

class Damageable;
class Bullet;

class Bullet :
	public Entity
{
public:
	Bullet();
	Bullet(Bullet & bullet, sf::Vector2f position, sf::Vector2f velocity);
	Bullet(std::string bulletSpriteName, int damage, sf::Vector2f position, sf::Vector2f velocity);
	virtual void draw(sf::RenderTarget &window) override;
	virtual void update(float time) override;

	bool isDestroyed();
	void destroy();
	int getDamage()
	{
		return damage;
	}
	int getFilter()
	{
		return filter;
	}
protected:
	GameSprite bulletSprite;
	int damage;
	int filter;
	bool destroyed;
	float speed;
};

class Damageable
{
public:
	Damageable();
	Damageable(TextElement * t);
	~Damageable();


	virtual void damage(int hp);
	virtual int getHealth();
	virtual int getMaxHealth();
	virtual void setHealth(int health);
	virtual void setMaxHealth(int health);
	virtual bool isIndestructable();
	virtual void setIndestructable(bool is_indestructable);
	virtual void destroy();
	virtual bool isDestroyed();
	virtual bool bulletCollisionTest(sf::Vector2f pos) = 0;

	virtual bool bulletCollision(Bullet * bullet);
	////bool checkFilter(int filter)
	//{
	//
	//}
protected:
	virtual void setDamageable(TextElement * t);

	int health = 0;
	int maxHealth = 0;
	bool destroyed = false;
	bool indestructable = false;
	__int8 damageFilter = -1;

	
};
#endif
