#include "GameSprite.hpp"


GameSprite::GameSprite()
{
}
GameSprite::GameSprite(sf::Vector2f position, const sf::Texture &set_texture, TextElement *spritetext)
{
	setPosition(position);
	SetSprite(set_texture, spritetext);
	auto data = spritetext->getVariableByName("Texture");
	if (data != nullptr)texture_name = data->toString(0);
}
GameSprite::GameSprite(const sf::Texture &set_texture, TextElement *spritetext)
{

	SetSprite(set_texture, spritetext);
	auto data = spritetext->getVariableByName("Texture");
	if (data != nullptr)texture_name = data->toString(0);
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
	// Get name
	auto varname = spritetext->getVariableByName("Name");
	if(varname!= nullptr) name = varname->toString(0);
	else Logger::e("Sprite is missing name");
	sprite.setTexture(set_texture);

	// Get size
	auto size = spritetext->getVariableByName("Texture_size");
	if(size != nullptr)
		SetRectangle(sf::IntRect(size->toInt(0), size->toInt(1), size->toInt(2), size->toInt(3)));
	else Logger::e("Sprite is missing texture size");

	// Get is animated
	is_animated = false;
	auto varIsAnimated = spritetext->getVariableByName("Animated");
	if (varIsAnimated != nullptr)is_animated = varIsAnimated->toInt(0);


	if (is_animated)
	{
		auto varSheet = spritetext->getVariableByName("Animation");
		if(varSheet!= nullptr)
			SetAnimationSheet(varSheet->toString(0));
		else Logger::e("Sprite is missing animation");
	}

	auto size2 = spritetext->getVariableByName("Sprite_size");
	if(size2!= nullptr)sprite.setScale(size2->toFloat(0) / size->toFloat(2), size2->toFloat(1) / size->toFloat(3));
	else Logger::e("Sprite is missing size");

	auto size3 = spritetext->getVariableByName("Sprite_center");
	if (size3 != nullptr)sprite.setOrigin(sf::Vector2f(size3->toFloat(0), size3->toFloat(1)));
	else sprite.setOrigin(sf::Vector2f(0, 0));
	//origin.x 
	

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
	file.loadFile(str);
	auto anim = file.getAllElementsByName("ANIMATION");

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

bool GameSprite::intersects(sf::FloatRect & rect)
{

	return rect.intersects(sprite.getGlobalBounds());
}

