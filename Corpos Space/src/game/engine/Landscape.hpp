#ifndef LANDSCAPE_HPP
#define LANDSCAPE_HPP
#include "Entity.hpp"
#include "game\graphics\GameSprite.hpp"
#include "game\utility\TextFileData.hpp"
#include "game\utility\Logger.hpp"
// wrapper for character used for controling it by player

namespace corpos
{
	class Landscape : public Entity
	{
	public:
		Landscape();
		Landscape(TextElement * element);
		Landscape(json & data);
		~Landscape();

		bool isForeground()
		{
			return mIsForeground;
		}

		void draw(sf::RenderTarget &window) override;;

		void update(float delta) override
		{
			sprite.update(delta);
		}

		bool setLandscape(TextElement * element);

	private:
		GameSprite sprite;
		double distanceFactor = 1; // 0 for background, 1 for normal
		bool mIsForeground = false;
	};
}
#endif