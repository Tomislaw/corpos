#ifndef DAMAGEABLE_HPP
#define DAMAGEABLE_HPP
#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>
#include "game\graphics\GameSprite.hpp"

namespace corpos
{
	class Damageable;
	class Bullet;
	// bullet class
	class Bullet :
		public Entity
	{
	public:
		Bullet();
		Bullet(Bullet & bullet, sf::Vector2f position, sf::Vector2f velocity);
		Bullet(std::string bulletSpriteName, int damage, sf::Vector2f position, sf::Vector2f velocity);
		// draw it
		virtual void draw(sf::RenderTarget &window) override;
		// update it
		virtual void update(float time) override;

		// true if destroyed
		bool isDestroyed();
		bool isDuringDestroying();
		// destroy it TODO: start destroy animation, then delete it
		void destroy();
		void correctBulletPositionAfterDestroy(sf::FloatRect collisionBox);
		void kill();
		// return damage caused by bullet

		void decreaseDamage(int damage)
		{
			this->damage -= damage;
			if (this->damage <= 0) destroy();
		}

		int getDamage() { return damage; }
		int getFilter() { return filter; }

		void setPosition(sf::Vector2f position) override {
			Entity::setPosition(position);
			bulletSprite.setPosition(position);
		}

		sf::Vector2f getPreviousPosition() { return previousPosition; }
		void setPreviousPosition(sf::Vector2f v) { previousPosition = v; }
		float getBulletDefaultSpeed() { return speed; }

		GameSprite getSprite() { return bulletSprite; }
	protected:
		// sprite of bullet
		GameSprite bulletSprite;
		int damage;
		int filter;
		bool destroyed = false;
		bool startDestroyAnimation = false;
		bool duringDestroying = false;
		float speed;

		sf::Vector2f previousPosition;
	};
	// interface for damagable entities
	// TODO: comment this class
	class Destructable
	{
	public:
		Destructable();

		virtual void destroy();
		virtual bool isDestroyed();

	protected:
		bool destroyed = false;
	};

	class Damageable : public Destructable
	{
	public:
		Damageable();
		Damageable(TextElement * t);
		Damageable(json & t);
		~Damageable();

		virtual void damage(int hp);
		virtual int getHealth();
		virtual int getMaxHealth();
		virtual void setHealth(int health);
		virtual void setMaxHealth(int health);
		virtual bool isIndestructable();
		virtual void setIndestructable(bool is_indestructable);

		virtual bool bulletCollision(Bullet * bullet) { return false; };
		////bool checkFilter(int filter)
		//{
		//
		//}
	protected:

		int health = 0;
		int maxHealth = 0;

		bool indestructable = false;
		__int8 damageFilter = -1;
	};
}
#endif