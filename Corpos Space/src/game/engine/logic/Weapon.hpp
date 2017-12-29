#ifndef	WEAPON_HPP
#define WEAPON_HPP
#include "D:\Microsoft Visual Studio\Projects\Corpos Space\Corpos Space\src\game\engine\Entity.hpp"
#include "game\engine\Damageable.hpp"
#include "GunFire.hpp"
class EntityList;
class Weapon
{
public:

	Weapon(TextElement * element, EntityList * entityptr);
	GunFire gunfire;
private:
	GameSprite weapon;

};
#endif

