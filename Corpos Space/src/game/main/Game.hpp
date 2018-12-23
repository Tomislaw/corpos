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
// Main game class, contains main game loop and configuration options
class Game
{
public:
	Game(int argc, char * argv[]);
	~Game();
	// start game
	bool run();
private:
	// update all physics and game logic
	void update(float delta_time);
	// draw it all
	void draw();
	// handle keyboard/mouse events
	void events(sf::Event event);
	// frames per seconds
	unsigned int FPS = 30;
	// pointer to window frame
	sf::RenderWindow *window;

	//cursor
	Cursor cursor;
	// tilemap and entity list
	World world;;

	//TODO: create menu class
	// game state for handling menu& game
	int game_state = 0;

	// data for fps drawing and calculating

	sf::Text fpsText;
	unsigned FpsframeCount = 0;
	float FpsDelta = 0;
};

#endif