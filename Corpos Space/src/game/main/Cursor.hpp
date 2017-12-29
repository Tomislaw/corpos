#ifndef CURSOR_HPP
#define CURSOR_HPP
#include "game\graphics\GameSprite.hpp"


class Cursor
{
public:
	Cursor();
	~Cursor();

	void setCursor();
	static sf::Vector2f getCursorPosition();
	void draw(sf::RenderWindow & target);
private:
	int mode;
	GameSprite cursor;
	static sf::Vector2f cursorPos;
};

#endif