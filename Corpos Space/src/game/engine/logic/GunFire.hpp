#ifndef	GUNFIRE_HPP
#define GUNFIRE_HPP
#include "D:\Microsoft Visual Studio\Projects\Corpos Space\Corpos Space\src\game\engine\Entity.hpp"
#include "game\engine\Damageable.hpp"

class EntityList;
class GunFire :
	public Entity
{
public:
	GunFire(EntityList* entlist,Bullet bulletType);
	~GunFire();

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
