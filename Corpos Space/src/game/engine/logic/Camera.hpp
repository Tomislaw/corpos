#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "game\engine\Entity.hpp"
class Camera :
	public Entity
{
public:

	Camera();
	Camera(sf::IntRect bounds, Entity * target);
	~Camera();

	void setForegroundView(sf::RenderTarget & target);
	void setBackgroundView(sf::RenderTarget & target);

private:
	Entity * target;
	sf::IntRect bounds;
	sf::View camera;
	float zoom = 1;
};

#endif