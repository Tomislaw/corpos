

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
	virtual void update (float delta_time) override;
	// set position
	void setPosition(sf::Vector2f pos) override;
	// set sprite textire
	void SetTexture(const sf::Texture &set_texture);
	// set main rectangle - used in animations
	void SetRectangle(sf::IntRect rect);
	// set sprite - used in constructors
	void SetSprite(const sf::Texture &set_texture, TextElement *spritetext);
	// set animation 
	bool SetAnimation(unsigned int i);
	// set animation 
	bool SetAnimation(const std::string  &str);
	// set animation sheet
	// contains all animations
	bool SetAnimationSheet(const std::string  &str);
	// get animation sheet 
	// contains all animations
	std::vector <Animation> & getAnimationSheet();
	// draw it
	virtual void draw(sf::RenderTarget &window) override;
	// return sf::sprite
	sf::Sprite &GetSprite() { return sprite; };
	// return texture name
	const std::string &getTextureName() { return texture_name; };
	// return current animation
	Animation * getCurrentAnimation();;

	virtual bool contains(sf::FloatRect & rect) override;
protected:
	bool is_animated = true;
	unsigned int current_animation = 0;

	sf::Sprite sprite;
	std::string texture_name;
	std::vector <Animation> animation_sheet;


};
#endif
