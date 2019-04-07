#include "Character.hpp"
#include "game\map\Tilemap.h"
#include "EntityList.hpp"
#include "game\engine\logic\ai\AiBasic.hpp"

Character::Character(EntityList * ptr) : Prop()
{
	this->entlistPtr = ptr;
	if (ptr != nullptr)
		map = entlistPtr->getTileMapPtr();

	this->max_walk_speed = 200;

	collisionBox.top = -23;//-23
	collisionBox.left = -15;//-15
	collisionBox.height = 56;
	collisionBox.width = 30;

	this->sprite = GameSprite(*GameAssetsManager::getSprite("player"));
	this->sprite.attachToEntity(this);

	rect.setSize(sf::Vector2f(collisionBox.width, collisionBox.height));
	rect.setFillColor(sf::Color::Red);
}
Character::Character(TextElement * element, EntityList * ptr) : Prop(element,ptr)
{
	this->entlistPtr = ptr;
	if (ptr != nullptr) map = entlistPtr->getTileMapPtr();
	this->sprite.attachToEntity(this);

	if (element == nullptr)return;


	max_walk_speed = element->get("Speed").toInt(0);
	collisionBox = element->get("CollisionBox").toRect<float>(0);

	//Set drawable debugh box
	rect.setSize(sf::Vector2f(collisionBox.width, collisionBox.height));
	rect.setFillColor(sf::Color::Red);

	//Set sprite of character
	auto sprite = element->get("Sprite");
	if (!sprite.isEmpty())
	{
		auto spriteName = sprite.toString(0);
		auto spriteDefinition = GameAssetsManager::getSprite(spriteName);
		if (spriteDefinition != nullptr)
			this->sprite = GameSprite(*spriteDefinition);
	}

	navCharData.characterWidth = 1 + collisionBox.width / (TILE_SIZE / 2);
	navCharData.characterHeight = 1 + collisionBox.height / (TILE_SIZE / 2);
	navCharData.characterJumpHeight = 3;
	navCharData.isFlyingOne = false;
	navCharData.canUseLadder = false;
}
Character::~Character()
{
}

void Character::walkLeft()
{
	walk_speed.x = -max_walk_speed;
	//isTurnedLeft = true;
}

void Character::walkRight()
{
	walk_speed.x = max_walk_speed;
	//isTurnedLeft = false;
}

void Character::jump()
{
	if (is_standing && !is_jumping)
	{
		setPosition(getPosition().x, getPosition().y - 1);
		velocity.y -= 300;
		is_jumping = true;
	}
}

void Character::startAttack()
{
	is_attacking = true;
}

void Character::stopAttack()
{
	is_attacking = false;
}

void Character::stop()
{
	walk_speed.x = 0;
}

void Character::update(float time)
{
	if (ai != nullptr)ai->update(time);
	setAnimation();
	impulseVelocityX(walk_speed.x, 1200, time);
	velocity.y += 1000 * time;

	Entity::update(time);
	resolveCollision();
	this->sprite.setPosition(getPosition());;
	this->sprite.update(time);

	if (velocity.y != 0)is_standing = false;
	//std::cout << name << " " << collisionBox.left << " " << collisionBox.top << " " << collisionBox.width << " " << collisionBox.height << std::endl;
}
/*
void Character::resolveCollision()
{
	if (map == nullptr)return;
	std::cout << position.x + collisionBox.left << " " << position.y + collisionBox.top + collisionBox.height << std::endl;

	int leftCollidePoints = 0;
	int rightCollidePoints = 0;
	int topCollidePoints = 0;
	int bottomCollidePoints = 0;

	int ties_sizeX = collisionBox.width / 32 + 1;
	if (ties_sizeX = 1)
	{
		auto t1 = map->getTileId(sf::Vector2f(getPosition().x + collisionBox.left, getPosition().y + collisionBox.top + collisionBox.height));
		auto t2 = map->getTileId(sf::Vector2f(getPosition().x + collisionBox.left + collisionBox.width, getPosition().y + collisionBox.top + collisionBox.height));
		if (map->isTileBlocking(t1.x, t1.y)|| map->isTileBlocking(t2.x, t2.y))
		{
			this->setPosition(getPosition().x, t1.y * 32 - collisionBox.height - collisionBox.top);
			if(velocity.y>0)velocity.y = 0;
		}
	}
	else
	{
		for (int i = 0; i < ties_sizeX + 1; i++)
		{
		}
	}

	int ties_sizeY = collisionBox.width / 32 + 1;
	if (ties_sizeX = 1)
	{
		auto t1 = map->getTileId(sf::Vector2f(getPosition().x + collisionBox.left, getPosition().y + collisionBox.top + collisionBox.height-1));
		auto t2 = map->getTileId(sf::Vector2f(getPosition().x + collisionBox.left, getPosition().y + collisionBox.top+1));

		auto t3 = map->getTileId(sf::Vector2f(getPosition().x + collisionBox.left + collisionBox.width, getPosition().y + collisionBox.top + collisionBox.height-1));
		auto t4 = map->getTileId(sf::Vector2f(getPosition().x + collisionBox.left + collisionBox.width, getPosition().y + collisionBox.top+1));

		if (map->isTileBlocking(t1.x, t1.y) || map->isTileBlocking(t2.x, t2.y))
		{
			this->setPosition(t1.x * 32 +32 - collisionBox.left,getPosition().y);
			if (velocity.x<0)velocity.x = 0;
		}
		if (map->isTileBlocking(t3.x, t3.y) || map->isTileBlocking(t4.x, t4.y))
		{
			this->setPosition(t1.x * 32 - collisionBox.left, getPosition().y);
			if (velocity.x>0)velocity.x = 0;
		}
	}
	else
	{
		for (int i = 0; i < ties_sizeX + 1; i++)
		{
		}
	}
}*/

void Character::resolveCollision()
{
	Prop::resolveCollision();
	if(isTouchingGround){
			is_jumping = false;
			is_standing = true;
	}
}

void Character::draw(sf::RenderTarget & target)
{
	//rect.setPosition(sf::Vector2f(getPosition().x + collisionBox.left, getPosition().y + collisionBox.top));
	//target.draw(rect);
	sprite.draw(target);
}

bool Character::intersects(sf::FloatRect & rect)
{
	return sf::FloatRect(getPosition().x + collisionBox.left, getPosition().y + collisionBox.top,
		collisionBox.width, collisionBox.height).intersects(rect);
}

void Character::drawDebugData(sf::RenderTarget & window)
{
	debugString = "";
	if (is_standing)debugString += " standing";
	else debugString += " failing";
	if (is_jumping) debugString += " jumping";

	debugString += "\n health: " + std::to_string(health) + "/" + std::to_string(maxHealth);

	auto pos = getStandingTileId();
	debugString += "\n pos: x:" + std::to_string(pos.x) + " y:" + std::to_string(pos.y);
	Entity::drawDebugData(window);
}

void Character::impulseVelocity(sf::Vector2f v, float impulse, float delta)
{
	float impulseX = impulse;
	if (v.x < 0 || v.x == 0 && velocity.x>0) impulseX = -impulse;
	float impulseY = impulse;
	if (v.y < 0) impulseY = -impulse;

	float test = velocity.x;
	if (velocity.x < v.x && v.x>0 || velocity.x > v.x && v.x < 0)
	{
		if (velocity.x + impulseX * delta > v.x&& v.x > 0 || velocity.x + impulseX * delta < v.x&& v.x < 0)
		{
			velocity.x = v.x;
		}
		else
		{
			velocity.x += impulseX * delta;
		}
	}
	if (velocity.y < v.y && v.x>0 || velocity.y > v.y && v.y < 0)
	{
		if (velocity.y + impulseY * delta > v.y&& v.y > 0 || velocity.y + impulseY * delta < v.y&& v.y < 0)
		{
			velocity.y = v.y;
		}
		else
		{
			velocity.y += impulseY * delta;
		}
	}
	if (v.x == 0)
	{
		if (velocity.x + impulseX * delta >= 0 && velocity.x < 0 || velocity.x + impulseX * delta <= v.x&& velocity.x > 0 || velocity.x == 0)
		{
			velocity.x = v.x;
		}
		else
		{
			velocity.x += impulseX * delta;
		}
	}
}

void Character::impulseVelocityX(float maxSpeed, float impulse, float delta)
{
	if (maxSpeed < 0 || maxSpeed == 0 && velocity.x>0)
	{
		if (velocity.x - impulse * delta > maxSpeed)
		{
			velocity.x -= impulse * delta;
		}
		else
		{
			velocity.x = maxSpeed;
		}
	}
	else
	{
		if (velocity.x + impulse * delta < maxSpeed)
		{
			velocity.x += impulse * delta;
		}
		else
		{
			velocity.x = maxSpeed;
		}
	}
}


void Character::walkUp()
{
}

void Character::walkDown()
{
}

void Character::setAnimation()
{
	if (velocity.x < 0)isTurnedLeft = true;
	if (velocity.x > 0)isTurnedLeft = false;

	if (walk_speed.x == 0 && velocity.y == 0)
	{
		if (isTurnedLeft)
		{
			sprite.setAnimation("idle_left");
		}
		else
		{
			sprite.setAnimation("idle_right");
		}
	}
	else
	{
		if (!is_jumping)
		{
			if (isTurnedLeft)
			{
				sprite.setAnimation("walk_left");
			}
			else
			{
				sprite.setAnimation("walk_right");
			}
		}
		else
		{
			if (isTurnedLeft)
			{
				sprite.setAnimation("jump_left");
			}
			else
			{
				sprite.setAnimation("jump_right");
			}
		}
	}
}

TileMap * Character::getTileMapPtr() {
	if (entlistPtr == nullptr)
		return nullptr;
	else return entlistPtr->getTileMapPtr();
}

sf::Vector2i Character::getStandingTileId()
{
	if (map == nullptr)return sf::Vector2i(-1, -1);

	return map->getTileId(getCenteredPosition());
}

sf::Vector2f Character::getCenteredPosition()
{
	return sf::Vector2f(getPosition().x + collisionBox.left + +collisionBox.width / 2,
		getPosition().y + collisionBox.top + collisionBox.height - 1);
}