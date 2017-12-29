#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <vector>
#include "game\utility\TextFileData.hpp"
#include  <SFML\Graphics.hpp>
class Animation
{
public:
	Animation();
	Animation(sf::IntRect r);
	Animation(TextElement *spritetext);
	~Animation();
	bool SetAnimation(TextElement *spritetext);
	sf::IntRect Animation::get_current_rectangle(float delta_time);
	sf::IntRect Animation::get_first_rectangle() { return frame.front(); };
	std::string GetName() { return name; };
	bool is_finished() { return this->isfinished; };;
	bool reset();
	std::string toString();
	int getFrameCount() { return frame.size(); }
	int getCurrentFrameId() {return current_frame;}
	sf::IntRect getRectangle(int id)
	{
		if (id < frame.size() && id >=0)return frame.at(id);
		else return sf::IntRect();
	}
private:
	std::string name = "idle";
	bool is_loop = true;
	bool isfinished = false;
	float animation_speed = 1;
	float current_time = 0;
	unsigned int current_frame = 0;
	std::vector <sf::IntRect> frame;
};
#endif
