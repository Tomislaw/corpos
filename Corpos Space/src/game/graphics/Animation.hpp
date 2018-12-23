#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <vector>
#include "game\utility\TextFileData.hpp"
#include  <SFML\Graphics.hpp>
// gamesprite animation
class Animation
{
public:
	Animation();
	Animation(sf::IntRect r);
	Animation(TextElement *spritetext);
	~Animation();
	// create animation from pointer to text element
	bool SetAnimation(TextElement *spritetext);
	// return current rectangle - called each frame by gamesprite
	sf::IntRect Animation::get_current_rectangle(float delta_time);
	// return first rectangle from animation
	sf::IntRect Animation::get_first_rectangle() { return frame.front(); };
	// return animation name
	std::string GetName() { return name; };
	// return true if animation is not looped and it is finished
	bool is_finished() { return this->isfinished; };;

	//finish animation;
	void finish();
	// reset animation
	bool reset();
	// return animation data in string
	std::string toString();
	// return frame count of animation
	int getFrameCount() {
		return frame.size();
	}
	// return current frame id
	int getCurrentFrameId() { return current_frame; }
	// return rectangle of animation
	sf::IntRect getRectangle(unsigned int id)
	{
		if (id < frame.size() && id >= 0)return frame.at(id);
		else return sf::IntRect();
	}
private:
	// TODO: change name variable to Entity::name
	std::string name = "idle";
	bool is_loop = true;
	bool isfinished = false;
	float animation_speed = 1;
	float current_time = 0;
	unsigned int current_frame = 0;
	std::vector <sf::IntRect> frame;
};
#endif