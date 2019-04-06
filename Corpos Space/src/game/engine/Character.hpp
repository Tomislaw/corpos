#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entity.hpp"
#include "game\graphics\GameSprite.hpp"
#include "Damageable.hpp"
#include "Prop.hpp"
class TileMap;
class EntityList;
class AiBasic;
//Core class for all characters
//TODO:comment this class

struct NavigationNodeCharacterData
{
	unsigned int characterWidth = 2;
	unsigned int characterHeight = 4;
	unsigned int characterJumpHeight = 4;
	bool canUseLadder = true;
	bool isFlyingOne = false;
};

class Character : public Prop
{
public:
	enum SpecialType { RELOAD, GRENADE, LONGJUMP };

	Character(EntityList * entityListPtr);
	Character(TextElement * data, EntityList * entityListPtr);
	~Character();


	virtual void walkUp();
	virtual void walkDown();
	virtual void walkLeft();
	virtual void walkRight();
	virtual void jump();
	//virtual void crouch();
	virtual void startAttack();
	virtual void stopAttack();

	virtual void special(unsigned int type) = 0;

	virtual void stop();
	virtual void update(float time) override;
	virtual void resolveCollision() override;
	virtual void aim(sf::Vector2f pos) { ; };
	virtual void draw(sf::RenderTarget &target)override;
	virtual bool intersects(sf::FloatRect & rect)override;
	//virtual bool bulletCollision(Bullet * bullet)override;

	virtual int getMaximumMoveSpeed() { return max_walk_speed;  }

	virtual void drawDebugData(sf::RenderTarget & window) override;

	EntityList * getEntityListPtr() {
		return entlistPtr;
	}
	TileMap * getTileMapPtr();

	std::shared_ptr<AiBasic> & getAiController() { return ai; };

	sf::Vector2i getStandingTileId();
	sf::Vector2f getCenteredPosition();

	const NavigationNodeCharacterData getNavigationNodeCharacterData()
	{
		return navCharData;
	}

	bool isStanding() { return is_standing; };
	bool isJumping() { return is_standing; };
protected:
	void impulseVelocity(sf::Vector2f v, float impulse, float delta);
	void impulseVelocityX(float maxSpeed, float impulse, float delta);
	int relationship_group = 0;
	float max_walk_speed = 50;
	//bool is_standing = false;

	sf::Vector2f walk_speed;

	std::shared_ptr<AiBasic> ai;

	TileMap * map = nullptr;
	EntityList * entlistPtr = nullptr;

	GameSprite sprite;

	bool isTurnedLeft = false;
	bool is_jumping = false;
	bool is_standing = false;
	bool is_attacking = false;
	virtual void setAnimation();

	NavigationNodeCharacterData navCharData;
private:

	// returns on which tile character is standing

	sf::RectangleShape rect;
};
#endif