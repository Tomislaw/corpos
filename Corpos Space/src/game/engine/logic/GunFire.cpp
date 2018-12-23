#include "GunFire.hpp"
#include "game\engine\EntityList.hpp"

GunFire::GunFire(EntityList * entlist, Bullet bulletType)
{
	name = "gunfire";
	this->bulletType = bulletType;
	this->entityListPtr = entlist;

	muzzle = bulletType.getSprite();
	muzzle.attachToEntity(nullptr);
	muzzle.SetAnimation("muzzle");

	auto animation = muzzle.getCurrentAnimation();
	if (animation != nullptr)animation->finish();
}

GunFire::~GunFire()
{
}

void GunFire::update(float delta)
{
	Entity::update(delta);
	muzzle.update(delta);

	if (entityListPtr == nullptr)
		return;

	//if not reloading
	if (!isReload)
	{
		//decrease time to spawn next bullet
		//if time is passed, spawn new bullet

		// return if not firing or have no ammo

		timeToNextBullet -= delta;

		if (!isFiring || magAmmo <= 0)
		{
			if (timeToNextBullet < 0)timeToNextBullet = 0;;
			return;
		}

		if (timeToNextBullet > 0)return;

		if (-timeToNextBullet > 1 / frequency)
		{
			float timebuffer = -timeToNextBullet;
			while (timebuffer > 0)
			{
				fireBullet(timebuffer);
				timebuffer -= 1 / frequency;
			}
			timeToNextBullet = timebuffer + 1 / frequency;
		}
		else
		{
			fireBullet(-timeToNextBullet);
			timeToNextBullet += 1 / frequency;
		}
	}//if reloading
	else
	{
		timeToReload -= delta;
		if (timeToReload <= 0)
		{
			isReload = false;
			if (maxMagAmmo > ammo)magAmmo = ammo;
			else magAmmo = maxMagAmmo;
			timeToNextBullet = 0;
		}
	}
}

void GunFire::startFire()
{
	if (timeToNextBullet <= 0)
	{
		timeToNextBullet = 0;
		fireBullet(-timeToNextBullet);
		timeToNextBullet = 1 / frequency;
	}
	isFiring = true;
}

void GunFire::stopFire()
{
	isFiring = false;
}

void GunFire::reload()
{
	if (isReload)return;
	if (ammo <= 0)return;
	if (magAmmo == maxMagAmmo)return;
	if (magAmmo == ammo)return;

	timeToReload = reloadTime;
	if (timeToReload <= 0)isReload = false;
	else isReload = true;
}

void GunFire::setBulletDefinition(Bullet & bullet) { bulletType = Bullet(bullet); }

void GunFire::aim(sf::Vector2f aimPos)
{
	radians = atan2(getPosition().y - aimPos.y, getPosition().x - aimPos.x) + 3.14; //rotated by 180 angle
}

void GunFire::draw(sf::RenderTarget & window)
{
	if (!muzzle.getCurrentAnimation()->is_finished())
	{
		sf::Vector2f muzzlePos;
		muzzlePos.x = getPosition().x + barrelLenght * cos(radians);
		muzzlePos.y = getPosition().y + barrelLenght * sin(radians);
		muzzle.setPosition(muzzlePos);
		muzzle.draw(window);
	}
}

void GunFire::drawDebugData(sf::RenderTarget & window)
{
	debugString = " frequency: " + std::to_string(frequency) + "\n " + std::to_string(magAmmo) + "/" + std::to_string(maxMagAmmo) + " " + std::to_string(ammo) + "\n";
	if (isFiring)debugString += " firing";
	if (isReload)debugString += " reloading " + std::to_string(timeToReload);
	Entity::drawDebugData(window);
}

void GunFire::fireBullet(float timeAfterUpdate)
{
	if (magAmmo <= 0 || ammo <= 0)return;
	ammo -= 1;
	magAmmo -= 1;

	if (entityListPtr == nullptr)return;

	float distance = barrelLenght + bulletType.getBulletDefaultSpeed()*timeAfterUpdate;

	sf::Vector2f startpos;
	startpos.x = getPosition().x + distance * cos(radians);
	startpos.y = getPosition().y + distance * sin(radians);

	muzzle.GetSprite().setRotation(radians * 180 / 3.14);

	auto anim = muzzle.getCurrentAnimation();
	if (anim != nullptr)anim->reset();

	sf::Vector2f velocity;
	velocity.x = bulletType.getBulletDefaultSpeed() * cos(radians);
	velocity.y = bulletType.getBulletDefaultSpeed() * sin(radians);

	auto p = std::shared_ptr<Bullet>(new  Bullet(bulletType, startpos, velocity));
	p->setPreviousPosition(getPosition());
	entityListPtr->addBullet(p);
}