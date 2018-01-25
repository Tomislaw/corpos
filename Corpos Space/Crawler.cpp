#include "Crawler.hpp"




bool Crawler::setCharacter(TextElement * element)
{
	this->Character::setCharacter(element);
	
	return false;
}

void Crawler::draw(sf::RenderTarget & window)
{
	Character::draw(window);
	drawDebugData(window);
}

void Crawler::update(float timew)
{
	Character::update(timew);

}



void Crawler::setAnimation()
{

	Character::setAnimation();
	
}

Crawler::~Crawler()
{
}
