#include "Animation.hpp"

Animation::Animation()
{
	name = "idle";
	animation_speed = 1;
	frame.push_back(sf::IntRect(0, 0, 32, 32));
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
	if (isfinished)frame[current_frame];

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

	// Set animation name
	auto varName = spritetext->get("Name");
	if (!varName.isEmpty()) name = varName.toString(0);
	else
		Logger::e("Animation is missing name!");

	auto varAnimationSpeed = spritetext->get("Animation_speed");
	if (!varAnimationSpeed.isEmpty())animation_speed = varAnimationSpeed.toFloat(0);
	else Logger::e("Animation " + name + " is missing speed!");

	int frames = 0;
	// Get frames count
	auto varFrames = spritetext->get("Frame_count");
	if (!varFrames.isEmpty()) frames = varFrames.toInt(0);

	//Get is loop
	auto varIsLoop = spritetext->get("isLoop");
	if (!varIsLoop.isEmpty()) is_loop = varIsLoop.toInt(0);
	else is_loop = false;

	if (frames < 0) frames = 0;

	for (int i = 0; i < frames; i++)
	{
		std::string frame_str = "Frame_" + std::to_string(i);
		// Set frame
		auto data = spritetext->get(frame_str);
		if (!data.isEmpty()) frame.push_back(data.toRect<int>(0));
		else Logger::e("Animation " + name + " is missing frame " + std::to_string(i));
	}
	if (animation_speed < 0 || frames == 0)isfinished = 1;

	return true;
}

void Animation::finish()
{
	current_time = frame.size()*animation_speed;
	current_frame = frame.size() - 1;
	isfinished = true;
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
		"Name: " + name + "\n"
		"Is loop: " + std::to_string(is_loop) + "\n"
		"Animation_speed: " + std::to_string(animation_speed) + "\n"
		//"Current frame: " + std::toString(current_frame) + "\n"
		"Frame count: " + std::to_string(frame.size())
	);
}