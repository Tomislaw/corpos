#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <vector>
#include <SFML\Graphics.hpp>
#include "Particle.hpp"
class Tilemap;
class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

	ParticleSystem(unsigned int count);
	void update(float elapsed);
	void setTilemapPointer(Tilemap * tilemap);
	void addParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Color color);
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:



	

	std::vector<Particle> particles;
	sf::VertexArray vertices;
	size_t lastVertice = 0;
	float particeLifetime = 5; // in seconds
	Tilemap * tilemapPtr = nullptr;
};

#endif