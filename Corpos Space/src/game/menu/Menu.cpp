#include "Menu.hpp"
#include "game/main/Game.hpp"

void Menu::init() {
	menuList.setOptimalHeight(300);
	std::shared_ptr <MenuLabel> labelStart = std::make_shared<MenuLabel>();
	labelStart->getLabel().setString("Start game");
	labelStart->setOnClikAction([&]() {game.showGame(); });
	menuList.addItem(labelStart);

	std::shared_ptr <MenuLabel> labelModules = std::make_shared<MenuLabel>();
	labelModules->getLabel().setString("Modules");
	labelModules->setOnClikAction([this]() {showMainMenu(false); showModules(true); });
	menuList.addItem(labelModules);

	std::shared_ptr <MenuLabel> labelOptions = std::make_shared<MenuLabel>();
	labelOptions->getLabel().setString("Options");
	labelOptions->setOnClikAction([]() { ;});
	menuList.addItem(labelOptions);

	std::shared_ptr <MenuLabel> labelExit = std::make_shared<MenuLabel>();
	labelExit->getLabel().setString("Exit");
	labelExit->setOnClikAction([&]() {game.exit(); });
	menuList.addItem(labelExit);

	menuList.setPosition(sf::Vector2f(100, 100));

	sf::Texture & texture = *GameAssetsManager::getTexture("mainmenu");
	sf::Vector2u size = texture.getSize();
	background.setTexture(texture);
}
