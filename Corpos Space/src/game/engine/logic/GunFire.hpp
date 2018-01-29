#ifndef	GUNFIRE_HPP
#define GUNFIRE_HPP
#include "D:\Microsoft Visual Studio\Projects\Corpos Space\Corpos Space\src\game\engine\Entity.hpp"
#include "game\engine\Damageable.hpp"

class EntityList;

//Logic type entity used for spawning bullets
//TODO: implementation in weapon class and soldier class
class GunFire :
	public Entity
{
public:
	//Constructor for gunfire entity, TODO: add null pointer handling
	GunFire(EntityList* entlist,Bullet bulletType);
	~GunFire();

	//update 
	void update(float delta) override;
	void startFire();
	void stopFire();
	void reload();
	void setBulletDefinition(Bullet & bullet);
	void aim(sf::Vector2f aimPos);

	virtual void draw(sf::RenderTarget & window)override;
	virtual void drawDebugData(sf::RenderTarget & window) override;
protected:
	//float angle;
	float radians;
	float barrelLenght = 40;
	Bullet bulletType;
	EntityList* entityListPtr;
	float frequency = 5;

	unsigned int magAmmo = 30;
	unsigned int maxMagAmmo = 30;

	unsigned int ammo = 90;
	unsigned int maxAmmo = 90;

	float reloadTime = 2;

	GameSprite muzzle;
private:
	float timeToReload = 0;
	float timeToNextBullet = 0;
	bool isFiring = false;
	bool isReload = false;

	void fireBullet(float timeAfterUpdate);

};

#endif
