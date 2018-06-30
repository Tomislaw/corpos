#include "Cursor.hpp"
#include "game\engine\EntityList.hpp"

sf::Vector2f Cursor::cursorPos;

Cursor::Cursor()
{
}

Cursor::~Cursor()
{
}

void Cursor::setCursor()
{
	cursor = GameSprite(*GameAssetsManager::getSprite("cursor"));
	cursor.SetAnimation("crosshair");
}

sf::Vector2f Cursor::getCursorPosition()
{
	return cursorPos;
}

void Cursor::draw(sf::RenderWindow & target)
{
	cursorPos = target.mapPixelToCoords(sf::Mouse::getPosition(target));
	cursor.setPosition(cursorPos);
	cursor.draw(target);
}
