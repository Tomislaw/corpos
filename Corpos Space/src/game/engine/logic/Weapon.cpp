#include "Weapon.hpp"

Weapon::Weapon(TextElement * element, EntityList * entityptr) : gunfire(entityptr, Bullet())
{
	if (element == nullptr)return;
	auto weaponName = element->getItem("Name").toString(0);
	auto weaponSprite = element->getItem("WeaponSprite").toString(0);

	auto bulletSprite = element->getItem("BulletSprite").toString(0);
	auto bulletDamage = element->getItem("BulletDamage").toFloat(0);
	auto bulletSpeed = element->getItem("BulletSpeed").toFloat(0);

	auto weaponFrequency = element->getItem("FireFrequency").toFloat(0);

	auto weaponAmmo = element->getItem("MaxAmmo").toInt(0);
	auto weaponMagAmmo = element->getItem("MagAmmo").toInt(0);

	auto weaponLenght = element->getItem("WeaponLenght").toFloat(0);

	sf::Vector2f gunfireOffset;
	auto offset = element->getItem("GunfireOffest");
	gunfireOffset = offset.toVector<float>(0);

	gunfire.setBulletDefinition(Bullet(bulletSprite, bulletDamage, sf::Vector2f(bulletSpeed, 0), sf::Vector2f(bulletSpeed, 0)));
	gunfire.attachToEntityOffset(&weapon, gunfireOffset);
}