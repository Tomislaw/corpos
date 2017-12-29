#ifndef GAME_HPP
#define GAME_HPP
#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>
#include "game\utility\Logger.hpp"
#include "iostream"
#include "game\engine\World.hpp"
#include "game\main\Cursor.hpp"
#include "game\graphics\TextContainer.hpp"
class Game
{
public:
	Game(int argc, char * argv[]);
	~Game();
	bool run();
private:
	void update(float delta_time);
	void draw();
	void events(sf::Event event);
	unsigned int FPS = 30;
	sf::RenderWindow *window;

	Cursor cursor;
	World world;;
	int game_state = 0;
	sf::Text fpsText;
	unsigned FpsframeCount = 0;
	float FpsDelta = 0;
};

#endif

