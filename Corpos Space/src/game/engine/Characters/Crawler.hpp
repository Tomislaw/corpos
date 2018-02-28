#ifndef CRAWLER_HPP
#define CRAWLER_HPP
#include "game\engine\Character.hpp"

class Crawler :
	public Character
{
public:


	Crawler(TextElement * data, EntityList * ptr);;
	~Crawler();

	// used in constructor, argument is pointer to text element
	bool setCharacter(TextElement * element)override;

	//draw it
	void draw(sf::RenderTarget & window) override;
	// update position, velocity and others
	void update(float timew) override;
	// aim at selected point
	void aim(sf::Vector2f pos) override {};

	void jump();

	void special(unsigned int type) override;
protected:
	//set animation, walking, shooting and other
	void setAnimation() override;
	float jumpSpeed = 0;
	float walkSpeed = 0;
private:


};
#endif

