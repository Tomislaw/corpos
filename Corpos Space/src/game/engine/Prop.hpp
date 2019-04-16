#ifndef PROP_HPP
#define PROP_HPP
#include "game\graphics\GameSprite.hpp"
#include "game\utility\TextFileData.hpp"
#include "game\utility\Logger.hpp"
#include "game\engine\Damageable.hpp"

class EntityList;
class TileMap;

class Prop :
	public Entity, public Damageable
{
public:
	Prop();
	Prop(TextElement * file, EntityList * entityListPtr);
	~Prop();

	virtual void setProp(TextElement * file);

	// check collisions with entities TODO: finish resolveCollision function
	virtual void resolveCollision();
	// draw it
	virtual void draw(sf::RenderTarget &window) override;
	// update it
	virtual void update(float time) override;
	// check if bullet is in prop
	virtual bool bulletCollision(Bullet * bullet);

	virtual void destroy() override {
		Damageable::destroy();
		actions().outputs.invokeOutput("onDestroy");
	}

	virtual bool intersects(sf::FloatRect & rect)override;
	// TODO: make line based collision test
protected:

	virtual void initializeActionManager() override;

	bool is_collidable = false;
	bool isTouchingGround = false;;
	sf::FloatRect collisionBox;

	TileMap * map = nullptr;
	EntityList * entlistPtr = nullptr;

	//drawable part
	GameSprite sprite;
};

#endif;