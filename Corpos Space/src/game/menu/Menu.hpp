#ifndef MENU_HPP
#define MENU_HPP
#include "game\graphics\GameSprite.hpp"
#include "MenuLabel.hpp"
#include "MenuList.hpp"
#include "game/GameWindow.hpp"
#include "imgui.h"
#include <filesystem>
class Game;

class ModuleChooser
{
public:

	void findModulesInPath(std::string path) {
		this->path = path;
		for (auto &f : std::filesystem::directory_iterator(path)) {
			modules.push_back(f.path().string());
		}
	}

	std::string path = "";
	std::vector<std::string> modules;
};

class Menu : public GameWindow
{
public:
	Menu(Game & game) : game(game) {
		chooser.findModulesInPath("modules");
	};

	void draw(sf::RenderWindow & target) override {
		target.draw(background);
		if (isShowingMainMenu)
			menuList.draw(target);
		if (isShowingModules)
			drawModules(target);
		if (isShowingOptions)
			drawOptions(target);
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
	void showOptionss(bool isShowing)
	{
		isShowingOptions = isShowing;
	}
	void drawModules(sf::RenderWindow & target);
	void drawOptions(sf::RenderWindow & target);
private:

	Game & game;

	ModuleChooser chooser;
	MenuList menuList;
	sf::Sprite background;

	bool isShowingMainMenu = true;
	bool isShowingModules = false;
	bool isShowingOptions = false;
};

#endif