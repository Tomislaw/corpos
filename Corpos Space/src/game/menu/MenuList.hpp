#ifndef MENULIST_HPP
#define MENULIST_HPP
#include "game\graphics\GameSprite.hpp"
#include "MenuItem.hpp"

namespace corpos
{
	class MenuList : public MenuItem
	{
	public:
		MenuList() {};

		void draw(sf::RenderWindow & target) override {
			for each (auto item in list)
			{
				item->draw(target);
			}
		};

		void setPosition(sf::Vector2f position) override {
			MenuItem::setPosition(position);
			resolveItemsPosition();
		}

		void setOptimalHeight(int height) {
			this->optimalHeight = height;
		}

		void onEvent(sf::Event event) override {
			for each (auto item in list)
			{
				item->onEvent(event);
			}
		}

		sf::Vector2f getSize() override {
			return sf::Vector2f(width, height);
		}

		void addItem(std::shared_ptr <MenuItem> item) {
			list.push_back(item);
			resolveItemsPosition();
		}

	protected:
		void resolveItemsPosition() {
			sf::Vector2f previousPosition = getPosition();
			width = 0;

			if (optimalHeight == 0)
				for each (auto item in list)
				{
					item->setPosition(previousPosition);
					previousPosition.y += item->getSize().y;
					if (item->getSize().x > width)width = item->getSize().x;
				}
			else
				for each (auto item in list)
				{
					item->setPosition(previousPosition);
					previousPosition.y += (float)optimalHeight / (float)list.size();
					if (item->getSize().x > width)width = item->getSize().x;
				}

			height = previousPosition.y;
		}

	private:
		std::vector<std::shared_ptr <MenuItem>> list;
		sf::Vector2f size;
		int optimalHeight = 0;
		int height = 0;
		int width = 0;
	};
}
#endif