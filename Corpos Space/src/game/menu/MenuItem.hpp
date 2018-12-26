#ifndef MENUITEM_HPP
#define MENUITEM_HPP
#include "game\graphics\GameSprite.hpp"

class MenuItem
{
public:
	MenuItem() {};
	// draw it
	virtual void draw(sf::RenderWindow & target) = 0;

	virtual sf::Vector2f getPosition() { return position; }
	virtual void setPosition(sf::Vector2f value) { position = value; }

	virtual sf::Vector2f getSize() { return sf::Vector2f(); }
	virtual sf::FloatRect getBounds() {
		return sf::FloatRect(getPosition(), getSize());
	}

	virtual void onEvent(sf::Event event) {};

	virtual void setOnClikAction(std::function<void()> onClick) {
		this->onClick = onClick;
	}
protected:
	sf::Vector2f position;
	std::function<void()> onClick;
};

#endif