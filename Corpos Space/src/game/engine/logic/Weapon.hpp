#ifndef	WEAPON_HPP
#define WEAPON_HPP
#include "game\engine\Entity.hpp"
#include "game\engine\Damageable.hpp"
#include "GunFire.hpp"

class EntityList;
//Unfinished weapon class
//TODO: finnish this class
//TODO: make pickupable class?
//TODO: rotating, inside soldier class or here?
class Weapon
{
public:

	Weapon(TextElement * element, EntityList * entityptr);
	GunFire gunfire;
private:
	GameSprite weapon;

	float weaponangle;
};
#endif

