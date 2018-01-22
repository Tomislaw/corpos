#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "Entity.hpp"
#include "game\graphics\GameSprite.hpp"
#include "Damageable.hpp"
class Tilemap;
class EntityList;
//Core class for all characters
//TODO:comment this class
class Character :
	public Entity, public Damageable
{
public:
	Character(Tilemap * tilemap);
	Character(TextElement * data,Tilemap * tilemap);
	~Character();

	virtual bool setCharacter(TextElement * element);

	virtual void walkLeft();
	virtual void walkRight();
	virtual void jump();
	//virtual void crouch();
	//virtual void attack();
	virtual void stop();
	virtual void update(float time) override;
	void resolveCollision();
	virtual void aim(sf::Vector2f pos) { ; };
	virtual void draw(sf::RenderTarget &target)override;
	virtual bool contains(sf::FloatRect & rect)override;
	virtual bool bulletCollision(Bullet * bullet)override;
protected:
	void impulseVelocity(sf::Vector2f v,float impulse,float delta);
	void impulseVelocityX(float maxSpeed, float impulse, float delta);
	float health = 0;
	int relationship_group = 0;
	float max_walk_speed = 50;
	bool is_standing = false;

	sf::Vector2f walk_speed;
	sf::FloatRect collision_box;

	Tilemap * map = nullptr;

	GameSprite sprite;

	bool isTurnedLeft = false;

	virtual void setAnimation();
private:

	// returns on which tile character is standing
	sf::Vector2i getStandingTileId();
	sf::RectangleShape rect;
	
};
#endif

