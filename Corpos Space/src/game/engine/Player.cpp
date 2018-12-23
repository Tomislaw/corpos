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
	if (player == nullptr)return;
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
		if (e.key.code == sf::Keyboard::R)
		{
			player->special(Character::RELOAD);
		}
		break;

	case sf::Event::KeyReleased:
		if (e.key.code == sf::Keyboard::A)
		{
			walkingLeft = false;
			if (walkingRight)player->walkRight();
			else player->stop();
		}
		if (e.key.code == sf::Keyboard::D)
		{
			walkingRight = false;
			if (walkingLeft)player->walkLeft();
			else player->stop();
		}
		break;

	case sf::Event::MouseButtonPressed:
		if (e.key.code == sf::Mouse::Left)
		{
			player->startAttack();
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (e.key.code == sf::Mouse::Left)
		{
			player->stopAttack();
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