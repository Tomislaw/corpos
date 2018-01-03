
#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>

// Entity - main base class
/*
*/
class Entity
{
public:
	Entity();
	Entity(std::string name, sf::Vector2f position);
	Entity(std::string name, sf::Vector2f position, sf::Vector2f velocity);
	~Entity();

	std::string getName();

	// update position and velocity
	virtual void update(float delta_time);
	// draw it - this class dont have anything to draw
	virtual void draw(sf::RenderTarget &window) {};
	// set position
	virtual void setPosition(sf::Vector2f position);
	// set position
	virtual void setPosition(float x, float y);
	// set position
	virtual sf::Vector2f getPosition();
	virtual void setVelocity(sf::Vector2f velocity);
	virtual void setVelocity(float x, float y);
	virtual sf::Vector2f getVelocity();

	// attach to entity, atached entity have exact position each frame as parent
	void attachToEntity(Entity * entity);
	// attach to entity, atached entity have exact position each frame as parent and moved by offset
	void attachToEntityOffset(Entity * entity, sf::Vector2f offset);
	// return true when attached
	bool isAttached();
	// return attach offset
	sf::Vector2f getAttachOffset() { return attachOffset; };
	// set attach offset
	void setAttachOffset(sf::Vector2f attachOffset) { this->attachOffset = attachOffset; };
protected:

	std::string name;
	sf::Vector2f position;
	sf::Vector2f velocity;

private:
	sf::Vector2f attachOffset;
	Entity * parent;

};

#endif