#include "GameSprite.hpp"


GameSprite::GameSprite()
{
}
GameSprite::GameSprite(sf::Vector2f position, const sf::Texture &set_texture, TextElement *spritetext)
{
	setPosition(position);
	SetSprite(set_texture, spritetext);
	auto data = spritetext->get_variable_by_name("Texture");
	if (!data->is_null())texture_name = data->var[0];
}
GameSprite::GameSprite(const sf::Texture &set_texture, TextElement *spritetext)
{

	SetSprite(set_texture, spritetext);
	auto data = spritetext->get_variable_by_name("Texture");
	if (!data->is_null())texture_name = data->var[0];
}


GameSprite::~GameSprite()
{
}


void GameSprite::SetTexture(const sf::Texture &set_texture)
{
	sprite.setTexture(set_texture);
}
void GameSprite::SetRectangle(sf::IntRect rect)
{
	sprite.setTextureRect(rect);
	setPosition(sf::Vector2f(50, 50));
}

void GameSprite::SetSprite(const sf::Texture &set_texture, TextElement *spritetext)
{
	name = spritetext->get_variable_by_name("Name")->var[0];
	sprite.setTexture(set_texture);


	auto size = spritetext->get_variable_by_name("Texture_size");
	SetRectangle(sf::IntRect(size->to_int(0), size->to_int(1), size->to_int(2), size->to_int(3)));

	is_animated = spritetext->get_variable_by_name("Animated")->to_int(0);
	if (is_animated)SetAnimationSheet(spritetext->get_variable_by_name("Animation")->var[0]);

	auto size2 = spritetext->get_variable_by_name("Sprite_size");
	sprite.setScale(size2->to_float(0) / size->to_float(2), size2->to_float(1) / size->to_float(3));

	auto size3 = spritetext->get_variable_by_name("Sprite_center");
	sf::Vector2f origin(size3->to_float(0), size3->to_float(1));
	//origin.x 
	sprite.setOrigin(sf::Vector2f(size3->to_float(0), size3->to_float(1)));

}

void GameSprite::update(float delta_time)
{
	Entity::update(delta_time);
	
	
	sprite.setPosition(getPosition());

	if (is_animated)
	{
		if (animation_sheet.size() == 0) return;
		if (!animation_sheet[current_animation].is_finished())sprite.setTextureRect(animation_sheet[current_animation].get_current_rectangle(delta_time));
	}

}

bool GameSprite::SetAnimation(unsigned int i)
{
	if (i >= animation_sheet.size()) current_animation = 0;
	else current_animation = i;
	animation_sheet[current_animation].reset();
	sprite.setTextureRect(animation_sheet[current_animation].get_first_rectangle());
	return true;
}
bool GameSprite::SetAnimation(const std::string  &str)
{
	for (int i = 0; i < animation_sheet.size(); i++)
	{
		if (str == animation_sheet[i].GetName())
		{
			if (i==current_animation)return true;
			current_animation = i;
			animation_sheet[current_animation].reset();
			sprite.setTextureRect(animation_sheet[current_animation].get_first_rectangle());
			return true;
		}
	}
	return false;
}

bool GameSprite::SetAnimationSheet(const std::string  &str)
{
	if (animation_sheet.size() != 0) animation_sheet.clear();
	TextFileData file;
	file.load_file(str);
	auto anim = file.get_all_elements_by_name("ANIMATION");

	for (int i = 0; i < anim.size(); i++)
	{

		Animation a(anim[i]);
		animation_sheet.push_back(a);
	}

	if (animation_sheet.size() == 0)
	{
		//std::cout << "No animations found in GAME SPRITE named " << name << std::endl;
		animation_sheet.push_back(Animation(sprite.getTextureRect()));
	}
	return true;
}

std::vector<Animation>& GameSprite::getAnimationSheet()
{
	return animation_sheet;
}

void GameSprite::setPosition(sf::Vector2f pos)
{
	Entity::setPosition(pos);
	sprite.setPosition(pos.x, pos.y);
}

void GameSprite::draw(sf::RenderTarget &window)
{

	sf::FloatRect intersect(window.getView().getCenter() - window.getView().getSize() / 2.f, window.getView().getSize());
	if (intersect.intersects(sprite.getGlobalBounds()))	window.draw(sprite);

}

Animation * GameSprite::getCurrentAnimation() {
	if (animation_sheet.size() > 0)
	{
		return &animation_sheet.at(current_animation);
	}
	else return nullptr;
}

