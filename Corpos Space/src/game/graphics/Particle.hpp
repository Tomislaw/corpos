#ifndef PARTICLE_HPP
#define PARTICLE_HPP
// simple particle struct

namespace corpos
{
	struct Particle
	{
		sf::Vector2f position;
		sf::Vector2f velocity;
		float lifetime = -1;
	};
}
#endif