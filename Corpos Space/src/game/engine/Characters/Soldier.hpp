#ifndef SOLDIER_HPP
#define SOLDIER_HPP
#include "D:\Microsoft Visual Studio\Projects\Corpos Space\Corpos Space\src\game\engine\Character.hpp"
class Soldier :
	public Character
{
public:
	Soldier(TextElement * data, Tilemap * tilemap) : Character(data, tilemap) {};
	~Soldier();

	bool setCharacter(TextElement * element)override;

	void draw(sf::RenderTarget & window) override;
	void update(float timew) override;

	void aim(sf::Vector2f pos) override;
protected:
	void setAnimation() override;
private:

	GameSprite weapontest;
	GameSprite lhand;
	GameSprite head;
	GameSprite torse;
	GameSprite legs;
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
#endif

