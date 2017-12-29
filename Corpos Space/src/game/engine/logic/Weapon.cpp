#include "Weapon.hpp"




Weapon::Weapon(TextElement * element, EntityList * entityptr) : gunfire(entityptr,Bullet())
{
	if (element == nullptr)return;
	auto weaponName = element->get_variable_by_name("Name")->to_string(0);
	auto weaponSprite = element->get_variable_by_name("WeaponSprite")->to_string(0);

	auto bulletSprite= element->get_variable_by_name("BulletSprite")->to_string(0);
	auto bulletDamage = element->get_variable_by_name("BulletDamage")->to_float(0);
	auto bulletSpeed = element->get_variable_by_name("BulletSpeed")->to_float(0);

	auto weaponFrequency = element->get_variable_by_name("FireFrequency")->to_float(0);

	auto weaponAmmo = element->get_variable_by_name("MaxAmmo")->to_int(0);
	auto weaponMagAmmo = element->get_variable_by_name("MagAmmo")->to_int(0);

	auto weaponLenght = element->get_variable_by_name("WeaponLenght")->to_float(0);

	sf::Vector2f gunfireOffset;
	auto offset = element->get_variable_by_name("GunfireOffest");
	gunfireOffset.x = offset->to_float(0);
	gunfireOffset.y = offset->to_float(1);


	gunfire.setBulletDefinition(Bullet(bulletSprite, bulletDamage, sf::Vector2f(bulletSpeed, 0), sf::Vector2f(bulletSpeed, 0)));
	gunfire.attachToEntityOffset(&weapon, gunfireOffset);
}

