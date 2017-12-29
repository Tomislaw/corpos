
#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>

// Entity - klasa odpowiedzialna za podstawowy byt gry
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

	virtual void update(float delta_time);
	virtual void draw(sf::RenderTarget &window) {};
	virtual void setPosition(sf::Vector2f position);
	virtual void setPosition(float x, float y);
	virtual sf::Vector2f getPosition();
	virtual void setVelocity(sf::Vector2f velocity);
	virtual void setVelocity(float x, float y);
	virtual sf::Vector2f getVelocity();

	void attachToEntity(Entity * entity);
	void attachToEntityOffset(Entity * entity, sf::Vector2f offset);
	bool isAttached();

	sf::Vector2f getAttachOffset() { return attachOffset; };
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