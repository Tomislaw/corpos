#include "Prop.hpp"
#include "game\utility\Logger.hpp"
#include "game\engine\Player.hpp"
#include "game\engine\Prop.hpp"
#include "EntityList.hpp"

Prop::Prop()
{
}

Prop::Prop(TextElement * file)
{
	is_collidable = file->get_variable_by_name("Collidable")->to_int(0);
	if(is_collidable)
	{ 
		setDamageable(file);
	auto var = file->get_variable_by_name("CollisionBox");

	this->collisionBox.left = var->to_float(0);
	this->collisionBox.top = var->to_float(1);
	this->collisionBox.width = var->to_float(2);
	this->collisionBox.height = var->to_float(3);
	}
	name = file->get_variable_by_name("Name")->var[0];
	auto pos = file->get_variable_by_name("Position");
	position.x = pos->to_float(0);
	position.y = pos->to_float(1);
	std::string spr = file->get_variable_by_name("Sprite")->var[0];
	auto x = EntityList::getSpriteDefinition(spr);
	if (x == nullptr)
	{
		Logger::e("Sprite " + spr + " not found!");
		return;
	}
	sprite = GameSprite(*x);
	
	auto sproff = file->get_variable_by_name("Sprite_offest");
	sf::Vector2f spriteoffset;
	spriteoffset.x = sproff->to_float(0);
	spriteoffset.y = sproff->to_float(1);
	sprite.attachToEntityOffset(this, spriteoffset);
}


Prop::~Prop()
{
}

void Prop::resolveCollision()
{
}

void Prop::draw(sf::RenderTarget & window)
{
	sprite.draw(window);
}

void Prop::update(float time)
{
	Entity::update(time);
	this->sprite.update(time);
}
