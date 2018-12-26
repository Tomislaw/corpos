#include "GameSprite.hpp"

GameSprite::GameSprite()
{
}
GameSprite::GameSprite(sf::Vector2f position, const sf::Texture &set_texture, TextElement *spritetext)
{
	setPosition(position);
	setSprite(set_texture, spritetext);
	auto data = spritetext->getVariableByName("Texture");
	if (data != nullptr)textureName = data->toString(0);
}
GameSprite::GameSprite(const sf::Texture &set_texture, TextElement *spritetext)
{
	setSprite(set_texture, spritetext);
	auto data = spritetext->getVariableByName("Texture");
	if (data != nullptr)textureName = data->toString(0);
}

GameSprite::~GameSprite()
{
}

void GameSprite::setTexture(const sf::Texture &set_texture)
{
	sprite.setTexture(set_texture);
}
void GameSprite::setRectangle(sf::IntRect rect)
{
	sprite.setTextureRect(rect);
	setPosition(sf::Vector2f(50, 50));
}

void GameSprite::setSprite(const sf::Texture &set_texture, TextElement *spritetext)
{
	// Get name
	auto varname = spritetext->getVariableByName("Name");
	if (varname != nullptr) name = varname->toString(0);
	else Logger::e("Sprite is missing name");
	
	sprite.setTexture(set_texture);

	// Get size
	auto size = spritetext->getVariableByName("Texture_size");
	auto textureSize = sf::Vector2i();
	if (size != nullptr) 
	{
		setRectangle(sf::IntRect(size->toInt(0), size->toInt(1), size->toInt(2), size->toInt(3)));
		textureSize.x = size->toInt(2);
		textureSize.y = size->toInt(3);
	}
	else 
	{ 
		Logger::i("Sprite \"" + name + "\"is missing texture size, using default");
		setRectangle(sf::IntRect(0, 0, set_texture.getSize().x, set_texture.getSize().y));
		textureSize.x = set_texture.getSize().x;
		textureSize.y = set_texture.getSize().y;
	}

	// Get is animated
	animated = false;
	auto varIsAnimated = spritetext->getVariableByName("Animated");
	if (varIsAnimated != nullptr)animated = varIsAnimated->toInt(0);

	if (animated)
	{
		auto varSheet = spritetext->getVariableByName("Animation");
		if (varSheet != nullptr)
			setAnimationSheet(varSheet->toString(0));
		else Logger::e("Sprite is missing animation");
	}

	auto size2 = spritetext->getVariableByName("Sprite_size");
	if (size2 != nullptr)sprite.setScale(size2->toFloat(0) / textureSize.x, size2->toFloat(1) / textureSize.y);
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

	if (animated)
	{
		if (animationSheet.size() == 0) return;
		if (!animationSheet[currentAnimation].is_finished())sprite.setTextureRect(animationSheet[currentAnimation].get_current_rectangle(delta_time));
	}
}

bool GameSprite::setAnimation(unsigned int i)
{
	if (i >= animationSheet.size()) currentAnimation = 0;
	else currentAnimation = i;
	animationSheet[currentAnimation].reset();
	sprite.setTextureRect(animationSheet[currentAnimation].get_first_rectangle());
	return true;
}
bool GameSprite::setAnimation(const std::string  &str)
{
	for (int i = 0; i < animationSheet.size(); i++)
	{
		if (str == animationSheet[i].GetName())
		{
			if (i == currentAnimation)return true;
			currentAnimation = i;
			animationSheet[currentAnimation].reset();
			sprite.setTextureRect(animationSheet[currentAnimation].get_first_rectangle());
			return true;
		}
	}
	return false;
}

bool GameSprite::setAnimationSheet(const std::string  &str)
{
	if (animationSheet.size() != 0) animationSheet.clear();
	TextFileData file;
	file.loadFile(str);
	auto anim = file.getAllElementsByName("ANIMATION");

	for (int i = 0; i < anim.size(); i++)
	{
		Animation a(anim[i]);
		animationSheet.push_back(a);
	}

	if (animationSheet.size() == 0)
	{
		//std::cout << "No animations found in GAME SPRITE named " << name << std::endl;
		animationSheet.push_back(Animation(sprite.getTextureRect()));
	}
	return true;
}

std::vector<Animation>& GameSprite::getAnimationSheet()
{
	return animationSheet;
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
	if (animationSheet.size() > 0)
	{
		return &animationSheet.at(currentAnimation);
	}
	else return nullptr;
}

bool GameSprite::intersects(sf::FloatRect & rect)
{
	return rect.intersects(sprite.getGlobalBounds());
}