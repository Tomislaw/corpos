#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "game\engine\Entity.hpp"
class Camera
{
public:
	
	Camera();
	Camera(sf::IntRect bounds, Entity * target);
	~Camera();

	void setNormalView(sf::RenderTarget & target);

	void setSize();
	void setTarget(Entity & entity);

	void setBackgroundView(sf::RenderTarget & target);

private:
	Entity * target;
	sf::IntRect bounds;
	sf::View camera;

};

#endif