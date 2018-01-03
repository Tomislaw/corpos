#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <vector>
#include <SFML\Graphics.hpp>
#include "Particle.hpp"
class Tilemap;

// particle systen
class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

	ParticleSystem(unsigned int count);
	// update all particles
	void update(float elapsed);
	// set tilemap pointer used in checking collision
	void setTilemapPointer(Tilemap * tilemap);
	// add particle
	void addParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Color color);
private:

	// draw it
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:



	

	std::vector<Particle> particles;
	sf::VertexArray vertices;
	size_t lastVertice = 0;
	float particeLifetime = 5; // in seconds
	Tilemap * tilemapPtr = nullptr;
};

#endif