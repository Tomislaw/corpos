#include "Animation.hpp"


Animation::Animation()
{
	name = "idle";
	animation_speed = 1;
	frame.push_back(sf::IntRect(0,0,32,32));
}

Animation::Animation(TextElement *spritetext)
{
	SetAnimation(spritetext);
}

Animation::Animation(sf::IntRect r)
{
	name = "idle";
	animation_speed = 1;
	frame.push_back(r);
}

Animation::~Animation()
{
}

sf::IntRect Animation::get_current_rectangle(float delta_time)
{
	if(isfinished)frame[current_frame];

	if (animation_speed*frame.size() > current_time)
	{
		current_frame = current_time / animation_speed;

	}

	if (current_frame > frame.size())
	{
		current_frame = 0;
	}

	if (is_loop && animation_speed*frame.size() < current_time)
	{
		current_time = 0;
	}
	if (!is_loop && animation_speed*frame.size() < current_time)
	{
		isfinished = true;
	}
	current_time += delta_time;

	return frame[current_frame];
}


bool Animation::SetAnimation(TextElement *spritetext)
{
	if (frame.size() != 0)frame.clear();
	
	name = spritetext->getVariableByName("Name")->var[0];
	animation_speed = spritetext->getVariableByName("Animation_speed")->toFloat(0);

	int frames = spritetext->getVariableByName("Frame_count")->toInt(0);
	is_loop = spritetext->getVariableByName("isLoop")->toInt(0);
	if (frames < 0) frames = 0;

	for (int i = 0; i < frames; i++)
	{
		std::string frame_str = "Frame_" + std::toString(i);
		auto data = spritetext->getVariableByName(frame_str);
		sf::IntRect f(data->toInt(0), data->toInt(1), data->toInt(2), data->toInt(3));
		frame.push_back(f);
	}
	if (animation_speed < 0|| frames==0)isfinished = 1;

	return true;
}

bool Animation::reset()
{
	current_time = 0;
	current_frame = 0;
	isfinished = false;
	return true;
}

std::string Animation::toString()
{
	return std::string(
		"Name: " + name +"\n"
		"Is loop: " + std::toString(is_loop) + "\n"
		"Animation_speed: " + std::toString(animation_speed) + "\n"
		//"Current frame: " + std::toString(current_frame) + "\n"
		"Frame count: " + std::toString(frame.size()) 
	);
}
