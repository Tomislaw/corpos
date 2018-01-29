#include "Crawler.hpp"




bool Crawler::setCharacter(TextElement * element)
{
	if (element == nullptr)return false;

	this->Character::setCharacter(element);
	
	//auto variableMaxSpeed = element->getVariableByName("Speed");
	//if (variableMaxSpeed != nullptr)
	//	this->walkSpeed = variableMaxSpeed->toInt(0);

	//jumpSpeed = 600;

	return true;
}

void Crawler::draw(sf::RenderTarget & window)
{
	Character::draw(window);
	drawDebugData(window);
}

void Crawler::update(float timew)
{

	Character::update(timew);
	/*if (is_jumping)
	{
		max_walk_speed = jumpSpeed;
		if (isTurnedLeft)
			velocity.x = -jumpSpeed;
		else
			velocity.x = jumpSpeed;
	}
	else max_walk_speed = walkSpeed;*/
}



void Crawler::jump()
{

	
	Character::jump();


}

void Crawler::special(unsigned int type)
{
}

void Crawler::setAnimation()
{

	Character::setAnimation();
	
}

Crawler::~Crawler()
{
}
