#ifndef	GUNFIRE_HPP
#define GUNFIRE_HPP
#include "D:\Microsoft Visual Studio\Projects\Corpos Space\Corpos Space\src\game\engine\Entity.hpp"
#include "game\engine\Damageable.hpp"

class EntityList;

//Logic type entity used for spawning bullets
//TODO: spawning bullet at correct angle
//TODO: spawning bullets in correct position
//TODO: start fire and stop fire functions - bullet frequency managing
//TODO: implementation in weapon class and soldier class
//TODO: finnish other needed stuff in this class
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
	void setBulletDefinition(Bullet & bullet);;
protected:
	float angle;
	float barrelLenght;
	Bullet bulletType;
	EntityList* entityListPtr;
	float frequency;

	unsigned int magAmmo;
	unsigned int maxMagAmmo;

	unsigned int ammo;
	unsigned int maxAmmo;

	float reloadTime;
private:
	float timeToReload;
	float timeToNextBullet;
	bool isFiring = false;
	bool isReload = false;
};

#endif
