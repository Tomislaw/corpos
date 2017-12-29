
#ifndef PROP_HPP
#define PROP_HPP
#include "game\graphics\GameSprite.hpp"
#include "game\utility\TextFileData.hpp"
#include "game\utility\Logger.hpp"
#include "game\engine\Damageable.hpp"
class Prop :
	public Entity, public Damageable
{
public:
	Prop();
	Prop(TextElement * file);
	~Prop();

	virtual void resolveCollision();
	virtual void draw(sf::RenderTarget &window) override;
	virtual void update(float time) override;
	virtual bool bulletCollisionTest(sf::Vector2f pos) override
	{
		return collisionBox.contains(pos.x - getPosition().x,pos.y - getPosition().y);
	}
protected:
	bool is_collidable = false;
	sf::FloatRect collisionBox;


	GameSprite sprite;

};

#endif;
