#ifndef LANDSCAPE_HPP
#define LANDSCAPE_HPP
#include "Entity.hpp"
#include "game\graphics\GameSprite.hpp"
#include "game\utility\TextFileData.hpp"
#include "game\utility\Logger.hpp"
// wrapper for character used for controling it by player
class Landscape : Entity
{
public:
	Landscape();
	Landscape(TextElement * element);
	~Landscape();

	bool isForeground() 
	{
		return mIsForeground;
	}

	void draw(sf::RenderTarget &window) override
	{
		auto position = getPosition();
		auto viewPosition = window.getView().getCenter();
		viewPosition.x -= window.getView().getSize().x / 2;
		viewPosition.y -= window.getView().getSize().y / 2;
		position.x += viewPosition.x * distanceFactor;
		position.y += viewPosition.y * distanceFactor;
		sprite.setPosition(position);
		sprite.draw(window);
	};

	void update(float delta) override 
	{
		sprite.update(delta);
	}

	bool setLandscape(TextElement * element)
	{
		if (element == nullptr)return false;

		//Set distance factorr
		auto variableDistanceFactor = element->getVariableByName("DistanceFactor");
		if (variableDistanceFactor != nullptr)
			this->distanceFactor = variableDistanceFactor->toFloat(0);

		//Set position
		auto variablePosition = element->getVariableByName("Position");
		if (variablePosition != nullptr) {
			this->position.x = variablePosition->toFloat(0);
			this->position.y = variablePosition->toFloat(1);
		}
			

		//Set sprite of character
		auto sprite = element->getVariableByName("Sprite");
		if (sprite != nullptr)
		{
			auto spriteName = sprite->toString(0);
			auto spriteDefinition = GameAssetsManager::getSprite(spriteName);
			if (spriteDefinition != nullptr)
				this->sprite = GameSprite(*spriteDefinition);
		}

		return true;
	}

private:
	GameSprite sprite;
	double distanceFactor = 1; // 0 for background, 1 for normal
	bool mIsForeground = false;
};
#endif