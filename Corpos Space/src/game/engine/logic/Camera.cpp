#include "Camera.hpp"



Camera::Camera()
{
}

Camera::Camera(sf::IntRect bounds, Entity * target)
{
	this->bounds = bounds;
	this->target = target;
}


Camera::~Camera()
{
}

void Camera::setForegroundView(sf::RenderTarget & target)
{
	
	camera.setSize(sf::Vector2f(target.getSize()));

	if (this->target == nullptr)
	{
		target.setView(camera);
		return;
	}

	sf::Vector2f position;
	position.x = (int)this->target->getPosition().x;;
	position.y = (int)this->target->getPosition().y;;
	camera.setCenter(position);

	
	camera.setCenter(position);
	target.setView(camera);
}

/*
void Camera::update(sf::RenderTarget & target)
{
	if (bounds.width != 0)
	{
		if (-camera.getSize().x / 2 + camera.getCenter().x < bounds.left)
		{
			position.x = camera.getSize().x / 2 + bounds.left;
		}
		if (camera.getSize().x / 2 + camera.getCenter().x >(bounds.left + bounds.width))
		{
			position.x = -camera.getSize().x / 2 + bounds.left + bounds.width;
		}
	}
	if (bounds.height != 0)
	{
		if ((camera.getCenter().y - camera.getSize().y / 2 < bounds.top) && false)
		{
			position.y = camera.getSize().y + bounds.top;
		}
		if (camera.getSize().y / 2 + camera.getCenter().y > bounds.top + bounds.height)
		{
			position.y = -camera.getSize().y / 2 + bounds.top + bounds.height;
		}
	}
}*/
