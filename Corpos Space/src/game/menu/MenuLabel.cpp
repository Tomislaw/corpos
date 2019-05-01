#include "MenuLabel.hpp"

using namespace corpos;

MenuLabel::MenuLabel()
{
	label.setFont(TextContainer::getInstance()->getBasicFont());
	label.setString("");
}

MenuLabel::MenuLabel(std::string text)
{
	label.setFont(TextContainer::getInstance()->getBasicFont());
	label.setString(text);
}

void MenuLabel::onEvent(sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button != sf::Mouse::Left) return;
		auto mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
		if (!label.getGlobalBounds().contains(mousePos))return;
		onClick();
	}
	if (event.type == sf::Event::MouseMoved) {
		auto mousePos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
		auto bounds = label.getGlobalBounds();
		if (!label.getGlobalBounds().contains(mousePos)) setSelected(false);
		else setSelected(true);
	}
}

void MenuLabel::setSelected(bool selected) {
	if (this->selected == selected)return;
	this->selected = selected;
	if (selected)label.setColor(sf::Color::Red);
	else label.setColor(sf::Color::White);
}