#ifndef MENULABEL_HPP
#define MENULABEL_HPP

#include "game\graphics\GameSprite.hpp"
#include "MenuItem.hpp"

class MenuLabel : 
	public MenuItem
{
public:
	MenuLabel();

	MenuLabel(std::string text);;

	// draw it
	void draw(sf::RenderWindow & target) override
	{
		target.draw(label);
	}

	void setPosition(sf::Vector2f position) override {
		label.setPosition(position);
	}

	sf::Text & getLabel() {
		return label;
	}

	sf::Vector2f getSize() override {
		return sf::Vector2f(label.getGlobalBounds().width, label.getGlobalBounds().height);
	}

	void onEvent(sf::Event event) override;

	void setSelected(bool selected);

	bool isSelected() { return selected; }

private:
	sf::Text label;
	bool selected = false;
};

#endif