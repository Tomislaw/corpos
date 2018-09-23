#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <vector>
#include <SFML\Graphics.hpp>
#include "Particle.hpp"
class TileMap;
class MapTile;

// particle systen
class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

	ParticleSystem(unsigned int count);
	// update all particles
	void update(float elapsed);
	// set tilemap pointer used in checking collision
	void setTileMapPointer(TileMap * tilemap);
	// add particle
	void addParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Color color);
	void onTileDestroy(MapTile * tile);
private:

	// draw it
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	TileMap * tileMapPtr = nullptr;

	std::vector<Particle> particles;
	sf::VertexArray vertices;
	size_t lastVertice = 0;
	float particeLifetime = 5; // in seconds
	
};

#endif