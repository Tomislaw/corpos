#ifndef SOLDIER_HPP
#define SOLDIER_HPP
#include "game/engine/Character.hpp"

#include "game\engine\logic\GunFire.hpp"
// Soldier character type
// Humanoid character type
// Using weapon and multiple sprite parts

namespace corpos
{
	class Soldier :
		public Character
	{
	public:
		//Main constructor TODO: add null pointer handling
		Soldier(TextElement * data, EntityList * ptr);
		Soldier(json & data, EntityList * ptr);
		~Soldier();

		//draw it
		void draw(sf::RenderTarget & window) override;
		// update position, velocity and others
		void update(float timew) override;
		// aim at selected point
		void aim(sf::Vector2f pos) override;

		virtual void startAttack()override;
		virtual void stopAttack()override;

		void special(unsigned int type) override;

	protected:
		//set animation, walking, shooting and other
		void setAnimation() override;

	private:

		// weapon sprite TODO: make custom class for weapon
		GameSprite weapontest;
		// left hand sprite
		GameSprite lhand;
		// head sprite
		GameSprite head;
		// torse sprite
		GameSprite torse;
		// legs sprite
		GameSprite legs;
		//TODO: add right hand sprite

		GunFire test;

		//offsets and orgins used for better looking in character moving and turning

		sf::Vector2f lhandOffset;
		sf::Vector2f headOffset;
		sf::Vector2f torseOffset;
		sf::Vector2f legsOffset;

		sf::Vector2f lhandOrigin;
		sf::Vector2f headOrigin;
		sf::Vector2f torseOrigin;
		sf::Vector2f legsOrigin;

		sf::Vector2f weaponOrigin;
		sf::Vector2f weaponOffset;
	};
}

#endif