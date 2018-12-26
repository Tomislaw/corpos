#ifndef MENU_HPP
#define MENU_HPP
#include "game\graphics\GameSprite.hpp"
#include "MenuLabel.hpp"
#include "MenuList.hpp"
#include "game/GameWindow.hpp"

class Game;

class Menu : public GameWindow
{
public:
	Menu(Game & game) : game(game) {
	};

	void draw(sf::RenderWindow & target) override {
		target.draw(background);
		menuList.draw(target);
	}
		
	void update(float deltaTime) override {
		//menuList.update(deltaTime);
	}
	void onEvent(sf::Event & event) override {
		menuList.onEvent(event);
	};

	void init();

private:
	
	Game & game;

	MenuList menuList;
	sf::Sprite background;

};

#endif
