#ifndef MAINGAE_HPP
#define MAINGAE_HPP
#include "game\graphics\GameSprite.hpp"
#include "GameWindow.hpp"
#include "game\engine\World.hpp"
class MainGame : public GameWindow
{
public:
	MainGame() { 
		
	};

	void draw(sf::RenderWindow & target) override{
		world.draw(target);
	}
	void update(float deltaTime) override {
		world.update(deltaTime);
	}
	void onEvent(sf::Event & event) override {
		world.events(event);
	};


	void init(std::string map) {
		world.loadMap(map);
	}

private :

	World world;;
};

#endif
