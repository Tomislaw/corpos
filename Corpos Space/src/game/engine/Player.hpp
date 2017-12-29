#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Character.hpp"
#include "game\utility\Logger.hpp"
class Player
{
public:
	Player();
	~Player();

	void setCharacter(Character * c) { 
		player = c;
		if(c!= nullptr)Logger::i("Player set to: " + c->getName());
		else Logger::i("Player is nullptr");
	};
	Character * getCharacter() { return player; };
	void events(sf::Event & e);
	
	void update(float time);
	Character * player;

	bool walkingLeft = false;
	bool walkingRight = false;

};
#endif

