#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Character.hpp"
#include "game\utility\Logger.hpp"
// wrapper for character used for controling it by player
class Player
{
public:
	Player();
	~Player();

	// set character to control
	void setCharacter(Character * c) {
		player = c;
		if (c != nullptr)Logger::i("Player set to: " + c->getName());
		else Logger::i("Player is nullptr");
	};
	// return controlled character
	Character * getCharacter() { return player; };
	// resolve events
	void events(sf::Event & e);

	//update it
	void update(float time);
	// pointer to character
	Character * player = nullptr;

	bool walkingLeft = false;
	bool walkingRight = false;
};
#endif