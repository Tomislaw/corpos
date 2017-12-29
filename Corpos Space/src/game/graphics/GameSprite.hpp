

#ifndef GAMESPRITE_HPP
#define GAMESPRITE_HPP

#include <SFML\Graphics.hpp>
#include "game\engine\Entity.hpp"
#include "game\utility\TextFileData.hpp"
#include "Animation.hpp"

class GameSprite :
	public Entity
{
public:
	GameSprite();
	//GameSprite(GameSprite &s) = default;
	GameSprite(const sf::Texture &set_texture, TextElement *spritetext);
	GameSprite(sf::Vector2f position, const sf::Texture &set_texture, TextElement *spritetext);
	~GameSprite();

	
	virtual void update (float delta_time) override;
	void setPosition(sf::Vector2f pos) override;
	void SetTexture(const sf::Texture &set_texture);
	void SetRectangle(sf::IntRect rect);
	void SetSprite(const sf::Texture &set_texture, TextElement *spritetext);
	bool SetAnimation(unsigned int i);
	bool SetAnimation(const std::string  &str);
	bool SetAnimationSheet(const std::string  &str);
	std::vector <Animation> & getAnimationSheet();
	virtual void draw(sf::RenderTarget &window) override;
	sf::Sprite &GetSprite() { return sprite; };
	const std::string &getTextureName() { return texture_name; };
	Animation * getCurrentAnimation();;
protected:
	bool is_animated = true;
	unsigned int current_animation = 0;

	sf::Sprite sprite;
	std::string texture_name;
	std::vector <Animation> animation_sheet;


};
#endif
