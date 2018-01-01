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
	is_collidable = file->getVariableByName("Collidable")->toInt(0);
	if(is_collidable)
	{ 
		setDamageable(file);
	auto var = file->getVariableByName("CollisionBox");

	this->collisionBox.left = var->toFloat(0);
	this->collisionBox.top = var->toFloat(1);
	this->collisionBox.width = var->toFloat(2);
	this->collisionBox.height = var->toFloat(3);
	}
	name = file->getVariableByName("Name")->var[0];
	auto pos = file->getVariableByName("Position");
	position.x = pos->toFloat(0);
	position.y = pos->toFloat(1);
	std::string spr = file->getVariableByName("Sprite")->var[0];
	auto x = EntityList::getSpriteDefinition(spr);
	if (x == nullptr)
	{
		Logger::e("Sprite " + spr + " not found!");
		return;
	}
	sprite = GameSprite(*x);
	
	auto sproff = file->getVariableByName("Sprite_offest");
	sf::Vector2f spriteoffset;
	spriteoffset.x = sproff->toFloat(0);
	spriteoffset.y = sproff->toFloat(1);
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
