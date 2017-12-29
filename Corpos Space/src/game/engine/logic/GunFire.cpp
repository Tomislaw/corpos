#include "GunFire.hpp"
#include "game\engine\EntityList.hpp"



GunFire::GunFire(EntityList * entlist, Bullet bulletType)
{
	this->bulletType = bulletType;
}

GunFire::~GunFire()
{
}

void GunFire::update(float delta)
{
	Entity::update(delta);

	if (entityListPtr != nullptr)
	{
		if (timeToReload <= 0)
		{
			if (isFiring)
			{

				timeToNextBullet -= delta;
				if (timeToNextBullet <= 0)
				{
					timeToNextBullet = 1 / frequency;
					auto p = std::shared_ptr<Bullet>(new  Bullet(bulletType,getPosition(),sf::Vector2f(50,50)));
					entityListPtr->addBullet(p);
				}
			}
		}
	}
}

void GunFire::setBulletDefinition(Bullet & bullet) { bulletType = Bullet(bullet); }
