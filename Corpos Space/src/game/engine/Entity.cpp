#include "Entity.hpp"



Entity::Entity()
{
}

Entity::Entity(std::string name, sf::Vector2f position)
{
	this->name = name;
	this->position = position;
}

Entity::Entity(std::string name, sf::Vector2f position, sf::Vector2f velocity)
{
	this->name = name;
	this->position = position;
	this->velocity = velocity;
}

Entity::~Entity()
{
}

std::string Entity::getName() { return name; }

void Entity::update(float delta_time)
{
	;
	if(parent == nullptr)
	{ 
	position.x += velocity.x * delta_time;
	position.y += velocity.y * delta_time;
	}
	else
	{
		this->setPosition(parent->getPosition().x + attachOffset.x, parent->getPosition().y + attachOffset.y);
	}
}

void Entity::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void Entity::setPosition(float x, float y)
{
	this->position.x = x;
	this->position.y = y;
}

sf::Vector2f Entity::getPosition()
{
	return position;
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

void Entity::setVelocity(float x, float y)
{
	this->velocity.x = x;
	this->velocity.y = y;
}

sf::Vector2f Entity::getVelocity()
{
	return velocity;
}

void Entity::attachToEntity(Entity * entity)
{
	this->parent = entity;
	this->attachOffset.x = 0;
	this->attachOffset.y = 0;
	this->setPosition(entity->getPosition());
}

void Entity::attachToEntityOffset(Entity * entity, sf::Vector2f offset)
{
	this->parent = entity;
	this->attachOffset = offset;
	this->setPosition(parent->getPosition().x + attachOffset.x, parent->getPosition().y + attachOffset.y);
}

bool Entity::isAttached()
{
	if (parent != nullptr) return true;
	else return false;
}