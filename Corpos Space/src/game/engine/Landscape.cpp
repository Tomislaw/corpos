#include "Landscape.hpp"

using namespace corpos;

Landscape::Landscape()
{
}

Landscape::Landscape(TextElement * element)
{
	setLandscape(element);
}

Landscape::Landscape(json & data) : Entity(data)
{
	this->distanceFactor = data["distanceFactor"].get(0.0);
	this->sprite = GameSprite(*GameAssetsManager::getSprite(data["sprite"].get("")));
}

Landscape::~Landscape()
{
}

inline void Landscape::draw(sf::RenderTarget & window)
{
	auto position = getPosition();
	auto viewPosition = window.getView().getCenter();
	viewPosition.x -= window.getView().getSize().x / 2;
	viewPosition.y -= window.getView().getSize().y / 2;
	position.x += viewPosition.x * distanceFactor;
	position.y += viewPosition.y * distanceFactor;
	sprite.setPosition(position);
	sprite.draw(window);
}

bool Landscape::setLandscape(TextElement * element)
{
	if (element == nullptr)return false;

	//Set distance factorr
	auto variableDistanceFactor = element->get("DistanceFactor");
	if (!variableDistanceFactor.isEmpty())
		this->distanceFactor = variableDistanceFactor.toFloat(0);

	//Set position
	auto variablePosition = element->get("Position");
	if (!variablePosition.isEmpty()) {
		this->position = variablePosition.toVector<float>(0);
	}

	//Set sprite of character
	auto sprite = element->get("Sprite");
	if (!sprite.isEmpty())
	{
		auto spriteName = sprite.toString(0);
		auto spriteDefinition = GameAssetsManager::getSprite(spriteName);
		if (spriteDefinition != nullptr)
			this->sprite = GameSprite(*spriteDefinition);
	}

	return true;
}