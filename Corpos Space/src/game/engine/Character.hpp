#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entity.hpp"
#include "game\graphics\GameSprite.hpp"
#include "Damageable.hpp"



class Tilemap;
class EntityList;
class AiBasic;
//Core class for all characters
//TODO:comment this class
class Character :
	public Entity, public Damageable
{
public:
	enum SpecialType{ RELOAD, GRENADE, LONGJUMP };

	Character(EntityList * entityListPtr);
	Character(TextElement * data, EntityList * entityListPtr);
	~Character();

	virtual bool setCharacter(TextElement * element);

	virtual void walkLeft();
	virtual void walkRight();
	virtual void jump();
	//virtual void crouch();
	virtual void startAttack();
	virtual void stopAttack();

	virtual void special(unsigned int type) = 0;

	virtual void stop();
	virtual void update(float time) override;
	void resolveCollision();
	virtual void aim(sf::Vector2f pos) { ; };
	virtual void draw(sf::RenderTarget &target)override;
	virtual bool intersects(sf::FloatRect & rect)override;
	virtual bool bulletCollision(Bullet * bullet)override;

	virtual void drawDebugData(sf::RenderTarget & window) override;

	EntityList * getEntityListPtr() {
		return entlistPtr;
	}

	AiBasic * getAiController() { return ai.get(); };

protected:
	void impulseVelocity(sf::Vector2f v,float impulse,float delta);
	void impulseVelocityX(float maxSpeed, float impulse, float delta);
	int relationship_group = 0;
	float max_walk_speed = 50;
	//bool is_standing = false;

	sf::Vector2f walk_speed;
	sf::FloatRect collision_box;

	std::unique_ptr<AiBasic> ai;

	Tilemap * map = nullptr;
	EntityList * entlistPtr = nullptr;

	GameSprite sprite;

	bool isTurnedLeft = false;
	bool is_jumping = false;
	bool is_standing = false;
	bool is_attacking = false;
	virtual void setAnimation();
private:

	// returns on which tile character is standing
	sf::Vector2i getStandingTileId();
	sf::RectangleShape rect;
	
};
#endif

