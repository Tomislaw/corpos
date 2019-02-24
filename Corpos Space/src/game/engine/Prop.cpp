#include "Prop.hpp"
#include "game\utility\Logger.hpp"
#include "game\engine\Player.hpp"
#include "game\engine\Prop.hpp"
#include "EntityList.hpp"
#include "game/map/TileMap.h"
#include "game/utility/Intersection.hpp"
Prop::Prop()
{
}

Prop::Prop(TextElement * file, EntityList * entityListPtr)  : Damageable(file), Entity(file)
{
	if (entityListPtr != nullptr)map = entityListPtr->getTileMapPtr();

	if (file == nullptr)return;

	is_collidable = false;

	// Set collidable flag
	auto varCollidable = file->getItem("Collidable");
	if (!varCollidable.isEmpty())
		is_collidable = varCollidable.toInt(0);

	if (is_collidable)
	{
		//Set collision box
		auto var = file->getItem("CollisionBox");
		if (!var.isEmpty())
		{
			this->collisionBox = var.toRect<float>(0);
		}
		else Logger::e("Damageable entity " + name + " dont have CollisionBox variable.");
	}

	// Set sprite
	auto varSprite = file->getItem("Sprite");
	if (!varSprite.isEmpty())
	{
		std::string spr = varSprite.toString(0);
		auto x = GameAssetsManager::getSprite(spr);
		if (x == nullptr)
		{
			Logger::e("Sprite " + spr + " not found!");
			return;
		}
		sprite = GameSprite(*x);
	}

	//Set sprite offset
	auto sproff = file->getItem("Sprite_offest");
	if (!sproff.isEmpty())
	{
		sprite.attachToEntityOffset(this, sproff.toVector<float>(0));
	}
	else sprite.attachToEntity(this);
}

Prop::~Prop()
{
}

void Prop::setProp(TextElement * file)
{

}

void Prop::resolveCollision()
{
		if (map == nullptr)return;
		//std::cout << position.x + collisionBox.left << " " << position.y + collisionBox.top + collisionBox.height << std::endl;
		// TODO: change corner collision detection to be more clearly -- change with cornerXX objects
		int leftCollidePoints = 0;
		int rightCollidePoints = 0;
		int topCollidePoints = 0;
		int bottomCollidePoints = 0;

		bool leftTop = false;
		bool leftBottom = false;
		bool rightTop = false;
		bool rightBottom = false;

		auto cornerLB = sf::Vector2f(getPosition().x + collisionBox.left, getPosition().y + collisionBox.top + collisionBox.height);
		auto cornerLT = sf::Vector2f(getPosition().x + collisionBox.left, getPosition().y + collisionBox.top);
		auto cornerRB = sf::Vector2f(getPosition().x + collisionBox.left + collisionBox.width, getPosition().y + collisionBox.top + collisionBox.height);
		auto cornerRT = sf::Vector2f(getPosition().x + collisionBox.left + collisionBox.width, getPosition().y + collisionBox.top);
		//defining in which tile are corners
		auto t1 = map->getTileId(cornerLB);
		auto t2 = map->getTileId(cornerLT);
		auto t3 = map->getTileId(cornerRB);
		auto t4 = map->getTileId(cornerRT);

		//checking corner collision

		if (map->isTileBlocking(t1.x, t1.y))leftBottom = true;;
		if (map->isTileBlocking(t2.x, t2.y))leftTop = true;;
		if (map->isTileBlocking(t3.x, t3.y))rightBottom = true;
		if (map->isTileBlocking(t4.x, t4.y))rightTop = true;

		//checking oversized
		int ties_sizeX = collisionBox.width / 32 + 1;
		int ties_sizeY = collisionBox.height / 32 + 1;
		if (ties_sizeX > 1)
		{
			for (int i = 1; i < ties_sizeX; i++)
			{
				auto tile = map->getTileId(sf::Vector2f(getPosition().x + collisionBox.left
					+ collisionBox.width / ties_sizeX * i,
					getPosition().y + collisionBox.top + collisionBox.height));

				auto tile2 = map->getTileId(sf::Vector2f(getPosition().x + collisionBox.left
					+ collisionBox.width / ties_sizeX * i,
					getPosition().y + collisionBox.top));

				if (map->isTileBlocking(tile.x, tile.y))bottomCollidePoints += 1;
				if (map->isTileBlocking(tile2.x, tile2.y))topCollidePoints += 1;
			}
		}
		if (ties_sizeY > 1)
		{
			for (int i = 1; i < ties_sizeY; i++)
			{
				auto tile = map->getTileId(sf::Vector2f(getPosition().x + collisionBox.left,
					getPosition().y + collisionBox.top +
					collisionBox.height / ties_sizeY * i));

				auto tile2 = map->getTileId(sf::Vector2f(getPosition().x + collisionBox.left + collisionBox.width,
					getPosition().y + collisionBox.top +
					collisionBox.height / ties_sizeY * i));
				if (map->isTileBlocking(tile.x, tile.y))leftCollidePoints += 1;
				if (map->isTileBlocking(tile2.x, tile2.y))rightCollidePoints += 1;
			}
		}

		// bottom collsion
		if (rightBottom || leftBottom || bottomCollidePoints > 0)
		{
			bool collideBottom = false;
			if (rightBottom&&leftBottom || bottomCollidePoints > 0)
			{
				collideBottom = true;
			}
			else
			{
				if (leftBottom)
					if (getPosition().x + collisionBox.left - t1.x * 32 < -getPosition().y - collisionBox.top - collisionBox.height + t1.y * 32 + 32)
					{
						collideBottom = true;
					}

				if (rightBottom)
				{
					if (-getPosition().x - collisionBox.left - collisionBox.width + t3.x * 32 + 32 < -getPosition().y - collisionBox.top - collisionBox.height + t3.y * 32 + 32)
					{
						collideBottom = true;
					}
				}
			}

			isTouchingGround = collideBottom;
			if (collideBottom)
			{
				this->setPosition(getPosition().x, t1.y * 32 - collisionBox.height - collisionBox.top);
				if (velocity.y >= 0)velocity.y = 0;
			}
		}

		// top collision
		if (leftTop || rightTop || topCollidePoints > 0)
		{
			bool collideTop = false;
			if (leftTop&&rightTop || topCollidePoints > 0)
			{
				collideTop = true;
			}
			else
			{
				if (leftTop)

					if (cornerLT.x - t2.x * 32 < -t2.y * 32 + cornerLT.y)
					{
						collideTop = true;
					}

				if (rightTop)
				{
					if (t4.x * 32 - cornerRT.x + 32 < cornerRT.y - t4.y * 32)
					{
						collideTop = true;
					}
				}
			}

			if (collideTop)
			{
				this->setPosition(getPosition().x, t2.y * 32 - collisionBox.top + 32);
				if (velocity.y < 0)velocity.y = 0;
			}
		}

		// left collision
		if (leftBottom || leftTop || leftCollidePoints > 0)
		{
			bool collideLeft = false;
			if (leftTop&&leftBottom || leftCollidePoints > 0)
			{
				collideLeft = true;
			}
			else
			{
				if (leftBottom)
				{
					if (getPosition().x + collisionBox.left - t1.x * 32 > -getPosition().y - collisionBox.top - collisionBox.height + t1.y * 32 + 32)
					{
						collideLeft = true;
					}
				}

				if (leftTop)
					if (cornerLT.x - t2.x * 32 > -t2.y * 32 + cornerLT.y)
					{
						collideLeft = true;
					}
			}
			if (collideLeft)
			{
				this->setPosition(t1.x * 32 - collisionBox.left + 32, getPosition().y);
				if (velocity.x < 0)velocity.x = 0;
			}
		}
		//right collision
		if (rightTop || rightBottom || rightCollidePoints > 0)
		{
			bool collideRight = false;
			if (rightTop&&rightBottom || rightCollidePoints > 0)
			{
				collideRight = true;
			}

			if (rightBottom)
			{
				if (-getPosition().x - collisionBox.left - collisionBox.width + t3.x * 32 + 32 > -getPosition().y - collisionBox.top - collisionBox.height + t3.y * 32 + 32)
				{
					collideRight = true;
				}
			}

			if (rightTop)
			{
				if (t4.x * 32 - cornerRT.x + 32 > cornerRT.y - t4.y * 32)
				{
					collideRight = true;
				}
			}
			if (collideRight)
			{
				this->setPosition(t3.x * 32 - collisionBox.width - collisionBox.left, getPosition().y);
				if (velocity.x > 0)velocity.x = 0;
			}
		}
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

bool Prop::bulletCollision(Bullet * bullet) {
	if (bullet == nullptr) return false;

	auto bulletOldPos = bullet->getPreviousPosition() - getPosition();
	auto bulletNewPos = bullet->getPosition() - getPosition();
	sf::Vector2f intersectPos;
	bool isHit = Intersection::LineSegRectIntersectionPoint(bulletOldPos, bulletNewPos, collisionBox, intersectPos);
	if (isHit) {
		auto bulletDamage = bullet->getDamage();
		bullet->decreaseDamage(getHealth());
		if (bullet->isDuringDestroying())bullet->setPosition(intersectPos);
		damage(bulletDamage);
	}
	return isHit;
}

/*
bool Prop::bulletCollision(Bullet * bullet)
{
	sf::FloatRect cb = sf::FloatRect(position.x + collisionBox.left, collisionBox.top + position.y, collisionBox.width, collisionBox.height);
	bool intersects = (cb.contains(bullet->getPosition()) || cb.contains(bullet->getPreviousPosition()));

	if (intersects == false)
	{
		// do line interesct here
	}

	if (intersects)
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
}*/

bool Prop::intersects(sf::FloatRect & rect)
{
	return rect.intersects(sf::FloatRect(position.x + collisionBox.left, collisionBox.top + position.y, collisionBox.width, collisionBox.height));
}