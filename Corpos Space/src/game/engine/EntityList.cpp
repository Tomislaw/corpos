#include "EntityList.hpp"
#include "World.hpp"
#include "src\game\main\Cursor.hpp"
std::vector <GameSprite> EntityList::game_sprite_definitions = std::vector <GameSprite>();

EntityList::EntityList()
	: particleSystem(100)
{
	particleSystem.addParticle(sf::Vector2f(83,-150), sf::Vector2f(10,10),sf::Color::Red);
	particleSystem.addParticle(sf::Vector2f(85, -130), sf::Vector2f(-10,10), sf::Color::Red);
	particleSystem.addParticle(sf::Vector2f(82, -130), sf::Vector2f(-6, 10), sf::Color::Red);
	particleSystem.addParticle(sf::Vector2f(87, -110), sf::Vector2f(-30, 10), sf::Color::Red);
	particleSystem.addParticle(sf::Vector2f(89, -100), sf::Vector2f(15, 10), sf::Color::Red);
}


EntityList::~EntityList()
{
}

void EntityList::addCharacter(std::shared_ptr<Character> & ent)
{
	characters.push_back(ent);

}

void EntityList::addProp(std::shared_ptr<Prop>& ent)
{
	props.push_back(ent);
}
void EntityList::addBullet(std::shared_ptr<Bullet>& bullet)
{
	bullets.push_back(bullet);
}

Entity * EntityList::findEntity(std::string name)
{
	//character search
	std::vector<std::shared_ptr <Character>>::iterator it = characters.begin();
	while (it != characters.end())
	{

		if (it->get()->getName() == name)return it->get();
		++it;
	}

	//prop search
	std::vector<std::shared_ptr <Prop>>::iterator it2 = props.begin();
	while (it2 != props.end())
	{

		if (it2->get()->getName() == name)return it2->get();
		++it2;
	}
	return nullptr;
}

std::vector<Entity*> EntityList::findEntities(std::string name)
{
	std::vector<Entity*> ents;
	std::vector<std::shared_ptr <Character>>::iterator it = characters.begin();
	while (it != characters.end())
	{

		if(it->get()->getName() == name) ents.push_back(it->get());
		++it;
	}

	std::vector<std::shared_ptr <Prop>>::iterator it2 = props.begin();
	while (it2 != props.end())
	{

		if (it2->get()->getName() == name) ents.push_back(it2->get());
		++it2;
	}
	return ents;
}

GameSprite * EntityList::getSpriteDefinition(std::string name)
{
	std::vector<GameSprite>::iterator it = game_sprite_definitions.begin();
	while (it != game_sprite_definitions.end())
	{

		if (it->getName() == name)
		{
			return it._Ptr;
		}
		++it;
	}
	return nullptr;
}

void EntityList::loadSpriteDefinition(std::string location)
{
	
	TextFileData file; //Loading sprites
	file.loadFile(location);
	auto entities = file.getAllElementsByName("ENTITY_DEFIINITION");
	Logger::i("Found " + std::to_string(entities.size()) + " game sprites");
	for (int i = 0; i < entities.size(); i++)
	{
		std::string s = entities.at(i)->getVariableByName("Texture")->var[0];
		std::string n = entities.at(i)->getVariableByName("Name")->var[0];
		sf::Texture * t = World::getTexture(s);
		if (t == nullptr)
		{
			Logger::e("Texture \"" + s + "\" not found! Sprite \"" + n + "\" not created!");
			continue;
		}
		GameSprite sprite(*t,entities.at(i));
		game_sprite_definitions.push_back(sprite);
	}

}

void EntityList::events(sf::Event & e)
{
	player.events(e);

	//TODO: delete this
	switch (e.type)
	{
	case sf::Event::MouseButtonPressed:
		sf::Vector2f v;
		v = Cursor::getCursorPosition();
		v -= player.getCharacter()->getPosition();

		auto p = std::shared_ptr<Bullet>(new  Bullet("bullet_blue",150,player.getCharacter()->getPosition(),v));
		addBullet(p);
		break;
	}
}

void EntityList::update(float time)
{
	player.update(time);
	std::vector<std::shared_ptr <Character>>::iterator it = characters.begin();
	while (it != characters.end())
	{

		it->get()->update(time);
		++it;
	}
	std::vector<std::shared_ptr <Prop>>::iterator it2 = props.begin();
	while (it2 != props.end())
	{
		it2->get()->update(time);
		if(it2->get()->isDestroyed())it2 = props.erase(it2);
		else ++it2;
	}
	std::vector<std::shared_ptr <Bullet>>::iterator it3 = bullets.begin();
	while (it3 != bullets.end())
	{
		it3->get()->update(time);
		checkBulletCollision(it3->get());
		if (it3->get()->isDestroyed())it3 = bullets.erase(it3);
		else ++it3;
		
	}
	particleSystem.update(time);
}

void EntityList::draw(sf::RenderWindow & window)
{
	camera.setNormalView(window);
	std::vector<std::shared_ptr <Character>>::iterator it = characters.begin();
	while (it != characters.end())
	{

		it->get()->draw(window);
		++it;
	}
	std::vector<std::shared_ptr <Prop>>::iterator it2 = props.begin();
	while (it2 != props.end())
	{

		it2->get()->draw(window);
		++it2;
	}
	std::vector<std::shared_ptr <Bullet>>::iterator it3 = bullets.begin();
	while (it3 != bullets.end())
	{

		it3->get()->draw(window);
		++it3;
	}
	window.draw(particleSystem);
}

bool EntityList::checkBulletCollision(Bullet * bullet)
{

	if (bullet->isDestroyed() || bullet->isDuringDestroying())return false;
	if (tilemapPtr == nullptr)
	{
		bullet->kill();
		return true;
	}
	else {
		for (size_t i = 0; i < props.size(); i++)
		{
			if (props.at(i)->bulletCollision(bullet)) return true;;
		}

		auto tilesInLine = this->tilemapPtr->getTilesFromLine(bullet->getPreviousPosition(), bullet->getPosition());

		for each (Tile* tile in tilesInLine)
		{
			if (tile == nullptr)
			{
				bullet->destroy();
				return true;
			}
			if (tile->isBlocking())
			{
				int damage = bullet->getDamage();
				bullet->decreaseDamage(tile->getHealth());
				tile->damage(damage);

				if (tile->isDestroyed())
				{
					sf::Vector2i tilePos = tilemapPtr->getTileId(tile->getPosition());
					tilemapPtr->refreashNearTiles(tilePos.x, tilePos.y);

					for (size_t i = 0; i < 8; i++)
					{
						auto p = tile->getRandomParticle();
						particleSystem.addParticle(p.position, p.velocity, tile->getRandomParticleColor());
					}
				}
				if (bullet->isDestroyed() || bullet->isDuringDestroying())
				{
					bullet->correctBulletPositionAfterDestroy(tile->getCollisionBox());
				}

				return true;
			}
		}

	}

	return false;
}

Camera & EntityList::getCurrentCamera()
{
	return camera;
}

void EntityList::setPlayerEntity(std::string name)
{
	std::vector<std::shared_ptr <Character>>::iterator it = characters.begin();
	while (it != characters.end())
	{

		if (it->get()->getName() == name)
		{
			player.setCharacter(it->get());
			if(tilemapPtr!= nullptr)camera = Camera(
				sf::IntRect(0,0,tilemapPtr->getMapSize().x, tilemapPtr->getMapSize().y), 
				it->get());

			return;
		}
		++it;
	}
	Logger::e("Character with name \"" + name + "\" not found!");
}

void EntityList::setTilemapPtr(Tilemap * ptr)
{
	tilemapPtr = ptr;
	particleSystem.setTilemapPointer(ptr);
}
