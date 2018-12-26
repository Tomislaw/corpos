#ifndef GAMESPRITE_HPP
#define GAMESPRITE_HPP

#include <SFML\Graphics.hpp>
#include "game\engine\Entity.hpp"
#include "game\utility\TextFileData.hpp"
#include "Animation.hpp"

// main graphic entity
class GameSprite :
	public Entity
{
public:
	GameSprite();
	//GameSprite(GameSprite &s) = default;
	GameSprite(const sf::Texture &set_texture, TextElement *spritetext);
	GameSprite(sf::Vector2f position, const sf::Texture &set_texture, TextElement *spritetext);
	~GameSprite();

	// update animations and position
	virtual void update(float delta_time) override;
	// set position
	void setPosition(sf::Vector2f pos) override;
	// set sprite textire
	void setTexture(const sf::Texture &set_texture);
	// set main rectangle - used in animations
	void setRectangle(sf::IntRect rect);
	// set sprite - used in constructors
	void setSprite(const sf::Texture &set_texture, TextElement *spritetext);
	// set animation
	bool setAnimation(unsigned int i);
	// set animation
	bool setAnimation(const std::string  &str);
	// set animation sheet
	// contains all animations
	bool setAnimationSheet(const std::string  &str);
	// get animation sheet
	// contains all animations
	std::vector <Animation> & getAnimationSheet();
	// draw it
	virtual void draw(sf::RenderTarget &window) override;
	// return sf::sprite
	sf::Sprite &getSprite() { return sprite; };
	// return texture name
	const std::string &getTextureName() { return textureName; };
	// return current animation
	Animation * getCurrentAnimation();;

	virtual bool intersects(sf::FloatRect & rect) override;
protected:
	bool animated = true;
	unsigned int currentAnimation = 0;

	sf::Sprite sprite;
	std::string textureName;
	std::vector <Animation> animationSheet;
};
#endif