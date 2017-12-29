#ifndef PARTICLE_HPP
#define PARTICLE_HPP
struct Particle
{
	sf::Vector2f position;
	sf::Vector2f velocity;
	float lifetime = -1;
};
#endif