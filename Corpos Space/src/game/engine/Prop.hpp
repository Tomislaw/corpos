#ifndef PROP_HPP
#define PROP_HPP
#include "game\graphics\GameSprite.hpp"
#include "game\utility\TextFileData.hpp"
#include "game\utility\Logger.hpp"
#include "game\engine\Damageable.hpp"
// static entity object
class Prop :
	public Entity, public Damageable
{
public:
	Prop();
	Prop(TextElement * file);
	~Prop();

	// check collisions with entities TODO: finish resolveCollision function
	virtual void resolveCollision();
	// draw it
	virtual void draw(sf::RenderTarget &window) override;
	// update it
	virtual void update(float time) override;
	// check if bullet is in prop
	virtual bool bulletCollision(Bullet * bullet);

	virtual bool intersects(sf::FloatRect & rect)override;
	// TODO: make line based collision test
protected:
	bool is_collidable = false;
	sf::FloatRect collisionBox;

	//drawable part
	GameSprite sprite;
};

#endif;