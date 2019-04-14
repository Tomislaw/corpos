#include "Crawler.hpp"
#include "game\engine\logic\ai\AiBasic.hpp"

void Crawler::draw(sf::RenderTarget & window)
{
	Character::draw(window);
	//drawDebugData(window);
	//ai->drawDebugData(window);
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

Crawler::Crawler(TextElement * data, EntityList * ptr) : Character(data, ptr)
{
	ai = std::unique_ptr<AiBasic>(new AiBasic(*this));
}

Crawler::~Crawler()
{
}