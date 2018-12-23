#include "ParticleSystem.hpp"
#include "game\map\TileMap.h"

static float particleSize = 1.5f;

ParticleSystem::ParticleSystem(unsigned int count)
{
	vertices.resize(count * 4);
	vertices.setPrimitiveType(sf::Quads);
	particles.resize(count, Particle());
}

void ParticleSystem::update(float elapsed)
{
	for (std::size_t i = 0; i < particles.size(); ++i)
	{
		// update the particle lifetime
		Particle& p = particles[i];
		p.lifetime -= elapsed;

		// if the particle is dead, respawn it
		if (p.lifetime <= 0)
		{
			continue;
		}

		// update the position of the corresponding vertex
		p.position += p.velocity * elapsed;

		if (tileMapPtr != nullptr)
		{
			auto tile = tileMapPtr->getTile(tileMapPtr->getTileId(p.position));
			bool isColideWithTile = tile != nullptr && tile->isBlocking();
			if (isColideWithTile)
			{
				p.velocity.x = -p.velocity.x;
				p.velocity.y = -p.velocity.y;

				p.position.x += p.velocity.x * elapsed;
				p.position.y += p.velocity.y * elapsed;

				p.velocity.x /= 2;
				p.velocity.y /= 2;
			}
			else
			{
			}
		}

		p.velocity.y += 2000 * elapsed;

		vertices[i * 4].position = p.position + sf::Vector2f(-particleSize, -particleSize);
		vertices[i * 4 + 1].position = p.position + sf::Vector2f(particleSize, -particleSize);
		vertices[i * 4 + 2].position = p.position + sf::Vector2f(particleSize, particleSize);
		vertices[i * 4 + 3].position = p.position + sf::Vector2f(-particleSize, particleSize);

		// update the alpha (transparency) of the particle according to its lifetime
		float ratio = p.lifetime / particeLifetime;
		vertices[i * 4].color.a = static_cast<sf::Uint8>(ratio * 255);
		vertices[i * 4 + 1].color.a = static_cast<sf::Uint8>(ratio * 255);
		vertices[i * 4 + 2].color.a = static_cast<sf::Uint8>(ratio * 255);
		vertices[i * 4 + 3].color.a = static_cast<sf::Uint8>(ratio * 255);
	}
}

void ParticleSystem::setTileMapPointer(TileMap * tilemap)
{
	this->tileMapPtr = tilemap;
}

void ParticleSystem::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = NULL;

	// draw the vertex array
	target.draw(vertices, states);
}

void ParticleSystem::addParticle(sf::Vector2f position, sf::Vector2f velocity, sf::Color color)
{
	Particle p;
	p.velocity = velocity;
	p.lifetime = particeLifetime;
	p.position = position;

	vertices[lastVertice * 4].position = position + sf::Vector2f(-particleSize, -particleSize);
	vertices[lastVertice * 4 + 1].position = position + sf::Vector2f(particleSize, -particleSize);
	vertices[lastVertice * 4 + 2].position = position + sf::Vector2f(particleSize, particleSize);
	vertices[lastVertice * 4 + 3].position = position + sf::Vector2f(-particleSize, particleSize);

	vertices[lastVertice * 4].color = color;
	vertices[lastVertice * 4 + 1].color = color;
	vertices[lastVertice * 4 + 2].color = color;
	vertices[lastVertice * 4 + 3].color = color;

	particles.at(lastVertice) = p;
	lastVertice += 1;
	if (lastVertice >= vertices.getVertexCount() / 4) lastVertice = 0;
}

void ParticleSystem::onTileDestroy(MapTile * tile)
{
	if (tile == nullptr)
	{
		Logger::i("Trying to add particles from empty tile.");
		return;
	}
	if (tile->getMainTile() != nullptr)
	{
		auto definition = tile->getMainTile()->getTileDefinition();

		for (int i = 0; i < 10; i++)
		{
			Particle p;
			p.lifetime = 3;

			int randx = tile->getMainTile()->getPosition().x - TILE_SIZE / 2 + std::rand() % (int)TILE_SIZE;
			int randy = tile->getMainTile()->getPosition().y - TILE_SIZE / 2 + std::rand() % (int)TILE_SIZE;

			p.position.x = randx;
			p.position.y = randy;

			randx = -100 + std::rand() % 200;
			randy = -100 + std::rand() % 200;

			p.velocity.x = randx;
			p.velocity.y = randy;
			addParticle(p.position, p.velocity, definition.getRandomColor());
		}
	}
}