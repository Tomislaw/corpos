#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP
#include "game\graphics\GameSprite.hpp"

namespace corpos
{
	class GameWindow
	{
	public:
		GameWindow() {
		};
		// draw it
		virtual void draw(sf::RenderWindow & target) = 0;
		virtual void update(float deltaTime) = 0;
		virtual void onEvent(sf::Event & event) = 0;
	};
}
#endif