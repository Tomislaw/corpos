#include "Character.hpp"
#include "game\map\Tilemap.hpp"
#include "EntityList.hpp"




Character::Character(EntityList * ptr) : Entity("char",sf::Vector2f(50,50))
{
	this->entlistPtr = ptr;
	if (ptr != nullptr)
		map = entlistPtr->getTilemapPtr();

	this->max_walk_speed = 200;


	collision_box.top = -23;//-23
	collision_box.left =-15;//-15
	collision_box.height = 56;
	collision_box.width = 30;

	this->sprite = GameSprite(*EntityList::getSpriteDefinition("player"));
	this->sprite.attachToEntity(this);

	rect.setSize(sf::Vector2f(collision_box.width, collision_box.height));
	rect.setFillColor(sf::Color::Red);
	
}
Character::Character(TextElement * data, EntityList * ptr) : Entity(data)
{

	this->entlistPtr = ptr;
	if (ptr != nullptr)
		map = entlistPtr->getTilemapPtr();
	this->sprite.attachToEntity(this);

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
	
	if (is_standing)
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
	setAnimation();
	impulseVelocityX(walk_speed.x,1200,time);
	velocity.y += 1000 * time;

	Entity::update(time);
	resolveCollision();
	this->sprite.setPosition(getPosition());;
	this->sprite.update(time);

	if (velocity.y != 0)is_standing = false;
	//std::cout << name << " " << collision_box.left << " " << collision_box.top << " " << collision_box.width << " " << collision_box.height << std::endl;
}
/*
void Character::resolveCollision()
{
	
	if (map == nullptr)return;
	std::cout << position.x + collision_box.left << " " << position.y + collision_box.top + collision_box.height << std::endl;

	int leftCollidePoints = 0;
	int rightCollidePoints = 0;
	int topCollidePoints = 0;
	int bottomCollidePoints = 0;

	int ties_sizeX = collision_box.width / 32 + 1;
	if (ties_sizeX = 1)
	{
		auto t1 = map->getTileId(sf::Vector2f(getPosition().x + collision_box.left, getPosition().y + collision_box.top + collision_box.height));
		auto t2 = map->getTileId(sf::Vector2f(getPosition().x + collision_box.left + collision_box.width, getPosition().y + collision_box.top + collision_box.height));
		if (map->isTileBlocking(t1.x, t1.y)|| map->isTileBlocking(t2.x, t2.y))
		{
			this->setPosition(getPosition().x, t1.y * 32 - collision_box.height - collision_box.top);
			if(velocity.y>0)velocity.y = 0;
		}
	}
	else
	{
		for (int i = 0; i < ties_sizeX + 1; i++)
		{

		}
	}

	int ties_sizeY = collision_box.width / 32 + 1;
	if (ties_sizeX = 1)
	{
		auto t1 = map->getTileId(sf::Vector2f(getPosition().x + collision_box.left, getPosition().y + collision_box.top + collision_box.height-1));
		auto t2 = map->getTileId(sf::Vector2f(getPosition().x + collision_box.left, getPosition().y + collision_box.top+1));

		auto t3 = map->getTileId(sf::Vector2f(getPosition().x + collision_box.left + collision_box.width, getPosition().y + collision_box.top + collision_box.height-1));
		auto t4 = map->getTileId(sf::Vector2f(getPosition().x + collision_box.left + collision_box.width, getPosition().y + collision_box.top+1));

		if (map->isTileBlocking(t1.x, t1.y) || map->isTileBlocking(t2.x, t2.y))
		{
			this->setPosition(t1.x * 32 +32 - collision_box.left,getPosition().y);
			if (velocity.x<0)velocity.x = 0;
		}
		if (map->isTileBlocking(t3.x, t3.y) || map->isTileBlocking(t4.x, t4.y))
		{
			this->setPosition(t1.x * 32 - collision_box.left, getPosition().y);
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

	if (map == nullptr)return;
	//std::cout << position.x + collision_box.left << " " << position.y + collision_box.top + collision_box.height << std::endl;
	// TODO: change corner collision detection to be more clearly -- change with cornerXX objects
	int leftCollidePoints = 0;
	int rightCollidePoints = 0;
	int topCollidePoints = 0;
	int bottomCollidePoints = 0;

	bool leftTop = false;
	bool leftBottom = false;
	bool rightTop = false;
	bool rightBottom = false;

	auto cornerLB = sf::Vector2f(getPosition().x + collision_box.left, getPosition().y + collision_box.top + collision_box.height);
	auto cornerLT = sf::Vector2f(getPosition().x + collision_box.left, getPosition().y + collision_box.top);
	auto cornerRB = sf::Vector2f(getPosition().x + collision_box.left + collision_box.width, getPosition().y + collision_box.top + collision_box.height);
	auto cornerRT = sf::Vector2f(getPosition().x + collision_box.left + collision_box.width, getPosition().y + collision_box.top);
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
	int ties_sizeX = collision_box.width / 32 + 1;
	int ties_sizeY = collision_box.height / 32 + 1;
	if (ties_sizeX > 1)
	{

		for (int i = 1; i < ties_sizeX;i++)
		{
			auto tile = map->getTileId(sf::Vector2f(getPosition().x + collision_box.left
				+ collision_box.width/ ties_sizeX*i,
				getPosition().y + collision_box.top + collision_box.height));

			auto tile2 = map->getTileId(sf::Vector2f(getPosition().x + collision_box.left
				+ collision_box.width / ties_sizeX*i,
				getPosition().y + collision_box.top));

			if (map->isTileBlocking(tile.x, tile.y))bottomCollidePoints += 1;
			if (map->isTileBlocking(tile2.x, tile2.y))topCollidePoints += 1;
		}
	}
	if (ties_sizeY > 1)
	{

		for (int i = 1; i < ties_sizeY;i++)
		{
			auto tile = map->getTileId(sf::Vector2f(getPosition().x + collision_box.left, 
				getPosition().y + collision_box.top + 
				collision_box.height/ ties_sizeY*i));

			auto tile2 = map->getTileId(sf::Vector2f(getPosition().x + collision_box.left + collision_box.width,
				getPosition().y + collision_box.top +
				collision_box.height / ties_sizeY*i));
			if (map->isTileBlocking(tile.x, tile.y))leftCollidePoints += 1;
			if (map->isTileBlocking(tile2.x, tile2.y))rightCollidePoints += 1;
		}
	}

	// bottom collsion
	if (rightBottom||leftBottom || bottomCollidePoints>0)
	{
		bool collideBottom = false;
		if(rightBottom&&leftBottom || bottomCollidePoints>0)
		{ 
			collideBottom = true;
		}
		else
		{
			if (leftBottom)
				if (getPosition().x + collision_box.left - t1.x * 32 < -getPosition().y - collision_box.top - collision_box.height + t1.y * 32 + 32)
				{
					collideBottom = true;
				}
	
			if(rightBottom)
			{
				if (-getPosition().x - collision_box.left - collision_box.width + t3.x * 32 + 32 <-getPosition().y - collision_box.top - collision_box.height + t3.y * 32 + 32)
				{
					collideBottom = true;
				}

			}
		}

		if (collideBottom)
		{
			this->setPosition(getPosition().x, t1.y * 32 - collision_box.height - collision_box.top);
			if (velocity.y>0)velocity.y = 0;
			is_jumping = false;
			is_standing = true;
		}
	}

	// top collision
	if (leftTop || rightTop || topCollidePoints>0)
	{
		bool collideTop = false;
		if (leftTop&&rightTop || topCollidePoints>0)
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
			this->setPosition(getPosition().x, t2.y * 32 - collision_box.top + 32);
			if (velocity.y<0)velocity.y = 0;
		}
	}

	// left collision
	if (leftBottom||leftTop || leftCollidePoints>0)
	{
		bool collideLeft = false;
		if (leftTop&&leftBottom || leftCollidePoints>0)
		{
			collideLeft = true;
		}
		else
		{
			
			if (leftBottom)
			{
				if (getPosition().x + collision_box.left - t1.x * 32 > -getPosition().y - collision_box.top - collision_box.height + t1.y * 32 + 32)
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
			this->setPosition(t1.x *32 - collision_box.left + 32, getPosition().y);
			if (velocity.x < 0)velocity.x = 0;
		}
	}
	//right collision
	if (rightTop||rightBottom || rightCollidePoints>0)
	{
		bool collideRight = false;
		if (rightTop&&rightBottom || rightCollidePoints>0)
		{
			collideRight = true;
		}



		if (rightBottom)
		{
			if (-getPosition().x - collision_box.left - collision_box.width + t3.x * 32 + 32 >-getPosition().y - collision_box.top - collision_box.height + t3.y * 32 + 32)
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
			this->setPosition(t3.x * 32 - collision_box.width - collision_box.left, getPosition().y);
			if (velocity.x>0)velocity.x = 0;
		}
	}



}


void Character::draw(sf::RenderTarget & target)
{
	rect.setPosition(sf::Vector2f(getPosition().x + collision_box.left, getPosition().y + collision_box.top));
	target.draw(rect);
	sprite.draw(target);
	
}

bool Character::contains(sf::FloatRect & rect)
{
	return sf::FloatRect(getPosition().x + collision_box.left, getPosition().y + collision_box.top,
		collision_box.width, collision_box.height).intersects(rect);
}

bool Character::bulletCollision(Bullet * bullet)
{
	return false;
}

void Character::drawDebugData(sf::RenderTarget & window)
{
	debugString = "";
	if (is_standing)debugString += " standing";
	else debugString += " failing";
	if (is_jumping) debugString += " jumping";

	debugString += "\n health: " + std::to_string(health) + "/" + std::to_string(maxHealth);
	Entity::drawDebugData(window);
}

void Character::impulseVelocity(sf::Vector2f v, float impulse, float delta)
{

	float impulseX = impulse;
	if (v.x < 0 || v.x ==0 && velocity.x>0) impulseX = -impulse;
	float impulseY = impulse;
	if (v.y < 0) impulseY = -impulse;

	float test = velocity.x;
	if (velocity.x < v.x && v.x>0 || velocity.x > v.x && v.x<0)
	{
		if (velocity.x + impulseX*delta > v.x&& v.x>0 || velocity.x + impulseX*delta < v.x&& v.x<0)
		{
			velocity.x = v.x;
		}
		else
		{
			velocity.x += impulseX*delta;
		}
	}
	if (velocity.y < v.y && v.x>0 || velocity.y > v.y && v.y<0)
	{
		if (velocity.y + impulseY*delta > v.y&& v.y>0 || velocity.y + impulseY*delta < v.y&& v.y<0)
		{
			velocity.y = v.y;
		}
		else
		{
			velocity.y += impulseY*delta;
		}
	}
	if (v.x == 0)
	{
		if (velocity.x + impulseX*delta >= 0 && velocity.x <0 || velocity.x + impulseX*delta <= v.x&& velocity.x > 0|| velocity.x ==0)
		{
			velocity.x = v.x;
		}
		else
		{
			velocity.x += impulseX*delta;
		}
	}

}

void Character::impulseVelocityX(float maxSpeed, float impulse, float delta)
{
	
	if (maxSpeed < 0 || maxSpeed == 0 && velocity.x>0)
	{
		if (velocity.x -impulse*delta > maxSpeed)
		{
			velocity.x -= impulse*delta;
		}
		else
		{
			velocity.x = maxSpeed;
		}
	}
	else
	{
		if (velocity.x + impulse*delta < maxSpeed)
		{
			velocity.x += impulse*delta;
		}
		else
		{
			velocity.x = maxSpeed;
		}
	}
}




bool Character::setCharacter(TextElement * element)
{

	if (element == nullptr)return false;

	setDamageable(element);

	//Set speed of character
	auto variableMaxSpeed = element->getVariableByName("Speed");
	if(variableMaxSpeed != nullptr)
		this->max_walk_speed = variableMaxSpeed->toInt(0);

	//Set character collision box
	auto cb = element->getVariableByName("CollisionBox");
	if(cb != nullptr)
	{ 
		collision_box.left = cb->toFloat(0);
		collision_box.top = cb->toFloat(1);
		collision_box.width = cb->toFloat(2);
		collision_box.height = cb->toFloat(3);
	}

	//Set drawable debugh box
	rect.setSize(sf::Vector2f(collision_box.width, collision_box.height));
	rect.setFillColor(sf::Color::Red);

	//Set sprite of character
	auto sprite = element->getVariableByName("Sprite");
	if (sprite != nullptr)
	{
		auto spriteName = sprite->toString(0);
		auto spriteDefinition = EntityList::getSpriteDefinition(spriteName);
		if(spriteDefinition!= nullptr)
		this->sprite = GameSprite(*spriteDefinition);
	}
	return true;
}

void Character::setAnimation()
{
	if (velocity.x < 0)isTurnedLeft = true;
	if (velocity.x > 0)isTurnedLeft = false;

	if (walk_speed.x == 0&& velocity.y==0)
	{
		if (isTurnedLeft)
		{
			sprite.SetAnimation("idle_left");
		}
		else
		{
			sprite.SetAnimation("idle_right");
		}
	}
	else
	{
		if(!is_jumping)
		{ 
			if (isTurnedLeft)
			{
				sprite.SetAnimation("walk_left");
			}
			else
			{
				sprite.SetAnimation("walk_right");
			}
		}
		else
		{
			if (isTurnedLeft)
			{
				sprite.SetAnimation("jump_left");
			}
			else
			{
				sprite.SetAnimation("jump_right");
			}
		}
	}


}

sf::Vector2i Character::getStandingTileId()
{
	if (map == nullptr)return sf::Vector2i(-1, -1);
	auto CBPosition = sf::Vector2f(getPosition().x , getPosition().y + collision_box.top + collision_box.height-1);
	return map->getTileId(CBPosition);
}
