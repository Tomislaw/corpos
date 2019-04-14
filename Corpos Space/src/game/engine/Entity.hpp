#ifndef ENTITY_HPP
#define ENTITY_HPP
#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>
#include "game\utility\TextFileData.hpp"
#include "game\graphics\TextContainer.hpp"
#include "game\graphics\GameAssetsManager.hpp"
#include "game/engine/logic/Action.h"
// Entity - main base class
/*
*/

class Entity
{
public:
	Entity();
	Entity(TextElement * data);
	Entity(std::string name, sf::Vector2f position);
	Entity(std::string name, sf::Vector2f position, sf::Vector2f velocity);
	~Entity();

	std::string getName();

	ActionManager & actions() { return actionManager; }

	// update position and velocity
	virtual void update(float delta_time);
	// draw it - this class dont have anything to draw
	virtual void draw(sf::RenderTarget &window) {};

	virtual void drawDebugData(sf::RenderTarget &window);
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

	virtual bool intersects(sf::FloatRect &rect);

protected:

	virtual void initializeActionManager();

	std::string name;
	sf::Vector2f position;
	sf::Vector2f velocity;
	std::string debugString;

private:
	sf::Vector2f attachOffset;
	Entity * parent = nullptr;
	ActionManager actionManager;
	bool isInitialized = false;
	sf::Text entityDebugText;
};

#endif