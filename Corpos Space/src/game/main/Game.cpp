#include "Game.hpp"



Game::Game(int argc, char * argv[])
{
	sf::Vector2u windowSize(500,500);
	GameAssetsManager::loadTextures("bin/graphics/textures/texture_definition.txt");
	GameAssetsManager::loadSprites("bin/graphics/sprite/sprite_definitions.txt");
	world.loadMap("bin/map/mm.txt");
	//world.loadEntitylist("bin/graphics/sprite/sprite_definitions.txt");
	cursor.setCursor();
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
			events(event);

		}
		

		while (timeSinceLastUpdate > TimePerFrame)
		{
			frame_time = delta;


			update(delta);

			timeSinceLastUpdate -= TimePerFrame;

			fpscheck.restart();

			if (FpsframeCount <10)
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
			draw();
		}

		fpscheck.restart();
		

	}
	Logger::i("Game end ");
	return 0;
}

void Game::update(float delta_time)
{
	world.update(delta_time);
	
}

void Game::draw()
{
	window->clear(sf::Color::Black);

	//draw background
	auto view = window->getView();
	window->setView(window->getDefaultView());


	window->setView(view);
	//

	
	world.draw(*window);
	cursor.draw(*window);


	//draw hud related items
	view = window->getView();
	window->setView(window->getDefaultView());;

	window->draw(fpsText);

	window->setView(view);
	//

	window->display();
	
}

void Game::events(sf::Event event)
{
	world.events(event);

		if (event.type == sf::Event::Closed)
			window->close();

}
