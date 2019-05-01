#include "Weapon.hpp"

using namespace corpos;

Weapon::Weapon(TextElement * element, EntityList * entityptr) : gunfire(entityptr, Bullet())
{
	if (element == nullptr)return;
	auto weaponName = element->get("Name").toString(0);
	auto weaponSprite = element->get("WeaponSprite").toString(0);

	auto bulletSprite = element->get("BulletSprite").toString(0);
	auto bulletDamage = element->get("BulletDamage").toFloat(0);
	auto bulletSpeed = element->get("BulletSpeed").toFloat(0);

	auto weaponFrequency = element->get("FireFrequency").toFloat(0);

	auto weaponAmmo = element->get("MaxAmmo").toInt(0);
	auto weaponMagAmmo = element->get("MagAmmo").toInt(0);

	auto weaponLenght = element->get("WeaponLenght").toFloat(0);

	sf::Vector2f gunfireOffset;
	auto offset = element->get("GunfireOffest");
	gunfireOffset = offset.toVector<float>(0);

	gunfire.setBulletDefinition(Bullet(bulletSprite, bulletDamage, sf::Vector2f(bulletSpeed, 0), sf::Vector2f(bulletSpeed, 0)));
	gunfire.attachToEntityOffset(&weapon, gunfireOffset);
}