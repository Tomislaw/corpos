#ifndef MENU_HPP
#define MENU_HPP
#include "game\graphics\GameSprite.hpp"
#include "MenuLabel.hpp"
#include "MenuList.hpp"
#include "game/GameWindow.hpp"
#include "imgui.h"
class Game;

class Menu : public GameWindow
{
public:
	Menu(Game & game) : game(game) {
	};

	void draw(sf::RenderWindow & target) override {
		target.draw(background);
		if (isShowingMainMenu)
			menuList.draw(target);
		if (isShowingModules)
			drawModules();
	}

	void update(float deltaTime) override {
		//menuList.update(deltaTime);
	}
	void onEvent(sf::Event & event) override {
		if (isShowingMainMenu)
			menuList.onEvent(event);
	};

	void init();

	void showMainMenu(bool isShowing)
	{
		isShowingMainMenu = isShowing;
	}
	void showModules(bool isShowing)
	{
		isShowingModules = isShowing;
	}

	void drawModules() {

		ImGui::ShowDemoWindow();
		ImGui::Begin("Sample window"); // begin window

		// Window title text edit
		ImGui::InputText("Window title", "jklj", 500);

		ImGui::End(); // end window
	}

private:

	Game & game;

	MenuList menuList;
	sf::Sprite background;

	bool isShowingMainMenu = true;
	bool isShowingModules = false;
};

#endif