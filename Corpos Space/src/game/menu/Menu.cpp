#include "Menu.hpp"
#include "game/main/Game.hpp"

void Menu::init() {
	menuList.setOptimalHeight(300);
	std::shared_ptr <MenuLabel> labelStart = std::make_shared<MenuLabel>();
	labelStart->getLabel().setString("Start game");
	labelStart->setOnClikAction([&]() {
		GameAssetsManager::loadTextures("bin/graphics/textures/texture_definition.txt");
		GameAssetsManager::loadSprites("bin/graphics/sprite/sprite_definitions.txt");
		game.mainGame.init("bin/map/mm.txt");
		game.showGame();
	});
	menuList.addItem(labelStart);

	std::shared_ptr <MenuLabel> labelModules = std::make_shared<MenuLabel>();
	labelModules->getLabel().setString("Modules");
	labelModules->setOnClikAction([this]() {showMainMenu(false); showModules(true); });
	menuList.addItem(labelModules);

	std::shared_ptr <MenuLabel> labelOptions = std::make_shared<MenuLabel>();
	labelOptions->getLabel().setString("Options");
	labelOptions->setOnClikAction([]() {; });
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

void Menu::drawModules(sf::RenderWindow & target) {
	ImGui::Begin("Modules", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

	auto windowSize = target.getSize();
	auto margin = sf::Vector2u(100, windowSize.y / 10);
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
	}, reinterpret_cast<void*>(&chooser.modules), chooser.modules.size(), size.y / 20);
	if (ImGui::Button("Play", sf::Vector2i(80, 40))) {
		auto moduleLocation = chooser.modules.at(listbox_item_current);
		GameAssetsManager::loadTextures(moduleLocation + "/graphics/textures/texture_definition.txt");
		GameAssetsManager::loadSprites(moduleLocation + "/graphics/sprite/sprite_definitions.txt");
		game.mainGame.init(moduleLocation + "/map/mm.txt");
		game.showGame();
	}
	ImGui::SetCursorPos(size - sf::Vector2u(95, 55));
	if (ImGui::Button("Back", sf::Vector2i(80, 40))) {
		showMainMenu(true);
		showModules(false);
	}
	ImGui::End(); // end window
}