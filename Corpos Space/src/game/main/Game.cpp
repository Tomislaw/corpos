#include "Game.hpp"
#include <imgui.h>
#include <imgui-SFML.h>
Game::Game(int argc, char * argv[])
	:menu(*this)
{
	sf::Vector2u windowSize(500, 500);
	GameAssetsManager::loadTextures("bin/graphics/textures/texture_definition.txt");
	GameAssetsManager::loadSprites("bin/graphics/sprite/sprite_definitions.txt");

	//world.loadEntitylist("bin/graphics/sprite/sprite_definitions.txt");
	cursor.setCursor();
	mainGame.init();
	menu.init();
	fpsText.setFont(TextContainer::getInstance()->getBasicFont());
}

Game::~Game()
{
	delete GameAssetsManager::getInstance();
}

bool Game::run()
{
	Logger::i("Game start");
	sf::RenderWindow w(sf::VideoMode(1000, 1000), "Corpos space");
	this->window = &w;
	window->resetGLStates();

	ImGui::SFML::Init(*window);

	long double delta = 0.00;
	long double frame_time = 0.00;

	sf::Clock clock;
	sf::Clock fpscheck;

	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time TimePerFrame = sf::seconds(1.f / FPS);

	while (w.isOpen())
	{
		delta = timeSinceLastUpdate.asSeconds();
		timeSinceLastUpdate += clock.restart();

		sf::Event event;
		while (window->pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			events(event);
		}

		ImGui::SFML::Update(*window, timeSinceLastUpdate);

		while (timeSinceLastUpdate > TimePerFrame)
		{
			frame_time = delta;

			update(delta);

			timeSinceLastUpdate -= TimePerFrame;

			fpscheck.restart();

			if (FpsframeCount < 10)
			{
				FpsframeCount += 1;
				FpsDelta += delta;
			}
			else
			{
				fpsText.setString(std::to_string((int)(10 / FpsDelta)));
				FpsframeCount = 0;
				FpsDelta = 0;
			}
			
		}
		draw();
		fpscheck.restart();
	}
	Logger::i("Game end ");
	ImGui::SFML::Shutdown();
	return 0;
}

void Game::update(float delta_time)
{
	switch (game_state) {
	case 0:
		menu.update(delta_time);
		break;
	case 1:
		mainGame.update(delta_time);
		break;
	}
}

void Game::draw()
{
	window->clear(sf::Color::Black);

	switch (game_state) {
	case 0:
		menu.draw(*window);
		break;
	case 1:
		mainGame.draw(*window);
		break;
	}
	
	cursor.draw(*window);
	window->setView(defaultView);
	window->draw(fpsText);

	ImGui::SFML::Render(*window);
	window->display();
}

void Game::events(sf::Event event)
{
	switch (game_state) {
	case 0:
		menu.onEvent(event);
		break;
	case 1:
		mainGame.onEvent(event);
		break;
	}

	if (event.type == sf::Event::Resized)
	{
		// update the view to the new size of the window
		sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
		defaultView = sf::View(visibleArea);
	}
	if (event.type == sf::Event::Closed)
		window->close();
}