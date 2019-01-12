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

void Camera::setView(sf::RenderTarget & target)
{
	camera.setSize(sf::Vector2f(target.getSize()));

	if (this->target != nullptr)
	{
		position = this->target->getPosition();
	}

	if (bounds.width != 0)
	{
		if (-camera.getSize().x / 2 + position.x < bounds.left)
		{
			position.x = camera.getSize().x / 2 + bounds.left;
		}
		if (camera.getSize().x / 2 + position.x > (bounds.left + bounds.width))
		{
			position.x = -camera.getSize().x / 2 + bounds.left + bounds.width;
		}
	}
	if (bounds.height != 0)
	{
		if ((position.y - camera.getSize().y / 2 < bounds.top) && false)
		{
			position.y = camera.getSize().y + bounds.top;
		}
		if (camera.getSize().y / 2 + position.y > bounds.top + bounds.height)
		{
			position.y = -camera.getSize().y / 2 + bounds.top + bounds.height;
		}
	}

	position.x = (int)position.x;
	position.y = (int)position.y;
	camera.setCenter(position);

	target.setView(camera);
}
