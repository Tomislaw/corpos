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

	void drawModules(sf::RenderWindow & target) {

		ImGui::Begin("Modules",nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
		
		auto windowSize = target.getSize();
		auto margin = sf::Vector2u(100, windowSize.y/10);
		auto size = windowSize - (margin + margin);

		ImGui::SetWindowPos(margin);
		ImGui::SetWindowSize(size);
		ImGui::Text("Modules");
		
		static int listbox_item_current = 0;


		ImGui::ListBox("Choose module to play", &listbox_item_current, 
			[](void* vec, int idx, const char** out_text) {
			auto& vector = *static_cast<std::vector<std::string>*>(vec);
			if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
			*out_text = vector.at(idx).c_str();
			return true;
		}, reinterpret_cast<void*>(&chooser.modules), chooser.modules.size(), size.y/20 );
		if (ImGui::Button("Play", sf::Vector2i(80, 40))) {

		}
		ImGui::SetCursorPos(size - sf::Vector2u(95, 55));
		if (ImGui::Button("Back", sf::Vector2i(80,40))) {
			showMainMenu(true);
			showModules(false);
		}
		ImGui::End(); // end window
	}

private:

	Game & game;

	ModuleChooser chooser;
	MenuList menuList;
	sf::Sprite background;

	bool isShowingMainMenu = true;
	bool isShowingModules = false;
};

#endif