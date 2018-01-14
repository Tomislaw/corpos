#include "Player.hpp"

#include "game\main\Cursor.hpp"

Player::Player()
{
}


Player::~Player()
{
}

void Player::events(sf::Event & e)
{
	switch (e.type)
	{
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::A)
		{
			walkingLeft = true;
			player->walkLeft();
		}
		if (e.key.code == sf::Keyboard::D)
		{
			walkingRight = true;
			player->walkRight();
		}
		if (e.key.code == sf::Keyboard::W)
		{
			player->jump();
		}
		if (e.key.code == sf::Keyboard::S)
		{
		}
		break;

		case sf::Event::KeyReleased:
			if (e.key.code == sf::Keyboard::A)
			{
				walkingLeft = false;
				if(walkingRight)player->walkRight();
				else player->stop();
			}
			if (e.key.code == sf::Keyboard::D)
			{
				walkingRight = false;
				if (walkingLeft)player->walkLeft();
				else player->stop();
			}
		break;
		// we don't process other types of events
	default:
		break;
	}
}

void Player::update(float time)
{
	if (player == nullptr)return;
	player->aim(Cursor::getCursorPosition());
}
