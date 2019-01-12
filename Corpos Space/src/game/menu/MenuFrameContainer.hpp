#ifndef MENU_FRAME_CONTAINER_HPP
#define MENU_FRAME_CONTAINER_HPP
#include "game\graphics\GameSprite.hpp"
#include "MenuItem.hpp"

/*/
class FrameContainer : public MenuItem
{
public:
	FrameContainer() { ; };

	void draw(sf::RenderWindow & target) override
	{
		if (hidden) return;
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

};*/

#endif
