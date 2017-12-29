#ifndef CURSOR_HPP
#define CURSOR_HPP
#include "game\graphics\GameSprite.hpp"

// Cursor class 
//TODO: make cursor class singleton
class Cursor
{
public:
	Cursor();
	~Cursor();
	//set sprite of cursor
	void setCursor();
	//return cursor position relative to window
	static sf::Vector2f getCursorPosition();
	// draw it
	void draw(sf::RenderWindow & target);
private:
	// cursor mode TODO: make enums for cursor modes
	int mode;
	// Cursor sprite
	GameSprite cursor;
	//Cursor position
	static sf::Vector2f cursorPos;
};

#endif