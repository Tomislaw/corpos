#include "Weapon.hpp"




Weapon::Weapon(TextElement * element, EntityList * entityptr) : gunfire(entityptr,Bullet())
{
	if (element == nullptr)return;
	auto weaponName = element->getVariableByName("Name")->toString(0);
	auto weaponSprite = element->getVariableByName("WeaponSprite")->toString(0);

	auto bulletSprite= element->getVariableByName("BulletSprite")->toString(0);
	auto bulletDamage = element->getVariableByName("BulletDamage")->toFloat(0);
	auto bulletSpeed = element->getVariableByName("BulletSpeed")->toFloat(0);

	auto weaponFrequency = element->getVariableByName("FireFrequency")->toFloat(0);

	auto weaponAmmo = element->getVariableByName("MaxAmmo")->toInt(0);
	auto weaponMagAmmo = element->getVariableByName("MagAmmo")->toInt(0);

	auto weaponLenght = element->getVariableByName("WeaponLenght")->toFloat(0);

	sf::Vector2f gunfireOffset;
	auto offset = element->getVariableByName("GunfireOffest");
	gunfireOffset.x = offset->toFloat(0);
	gunfireOffset.y = offset->toFloat(1);


	gunfire.setBulletDefinition(Bullet(bulletSprite, bulletDamage, sf::Vector2f(bulletSpeed, 0), sf::Vector2f(bulletSpeed, 0)));
	gunfire.attachToEntityOffset(&weapon, gunfireOffset);
}

