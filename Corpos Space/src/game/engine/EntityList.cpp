#include "EntityList.hpp"
#include "World.hpp"
#include "src\game\main\Cursor.hpp"
#include "src\game\engine\logic\ai\AiBasic.hpp"

EntityList::EntityList()
	: particleSystem(100)
{
}

EntityList::~EntityList()
{
}

void EntityList::loadMap(TextFileData & file)
{
	//if (tilemapPtr == nullptr)return;
	//tree = Quadtree(sf::Vector2f(), tilemapPtr->getMapSize(), 0, 4, 5);

	if (tileMapPtr == nullptr)return;
	tree = Quadtree(sf::Vector2f(), tileMapPtr->getMapSize(), 0, 4, 5);

	auto map_props = file.getAllElementsByName("PROP");
	for (int i = 0; i < map_props.size(); i++)
	{
		auto p = std::shared_ptr<Prop>(new  Prop(map_props.at(i)));
		addProp(p);
	}

	auto map_characters = file.getAllElementsByName("CHARACTER");
	for (int i = 0; i < map_characters.size(); i++)
	{
		auto p = CharacterFactory::create(map_characters.at(i), this);
		addCharacter(p);
	}

	setPlayerEntity("@player");
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
		if (it->get()->getName() == name) ents.push_back(it->get());
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

void EntityList::events(sf::Event & e)
{
	player.events(e);

	//TODO: delete this
	switch (e.type)
	{
	case sf::Event::MouseButtonPressed:

		if (e.mouseButton.button == sf::Mouse::Right)
		{
			auto ents = tree.GetObjectsAt(player.getCharacter()->getPosition());
			std::cout << "Entities at player pos :" << std::endl;
			for each (Entity* var in ents)
			{
				std::cout << var->getName() << " " << var->getPosition().x << " " << var->getPosition().y << std::endl;
			}

			auto tile = tileMapPtr->getTileId(cursorPos.x, cursorPos.y);
			std::cout << "Going to: " << tile.x << " " << tile.y << std::endl;
			player.getCharacter()->getAiController()->getPath(tile);

			return;
		}
		break;
	case sf::Event::Resized:
		//camera.
		break;
	}
}

void EntityList::update(float time)
{
	std::vector<std::shared_ptr <Bullet>>::iterator it3 = bullets.begin();
	while (it3 != bullets.end())
	{
		it3->get()->update(time);
		checkBulletCollision(it3->get());
		if (it3->get()->isDestroyed())it3 = bullets.erase(it3);
		else
		{
			++it3;
		}
	}

	player.update(time);
	tree.Clear();
	std::vector<std::shared_ptr <Character>>::iterator it = characters.begin();
	while (it != characters.end())
	{
		it->get()->update(time);
		if (it->get()->isDestroyed())it = characters.erase(it);
		else
		{
			tree.AddObject(it->get());
			++it;
		}
	}
	std::vector<std::shared_ptr <Prop>>::iterator it2 = props.begin();
	while (it2 != props.end())
	{
		it2->get()->update(time);
		if (it2->get()->isDestroyed())it2 = props.erase(it2);
		else
		{
			tree.AddObject(it2->get());
			++it2;
		}
	}

	particleSystem.update(time);
}

void EntityList::draw(sf::RenderWindow & window)
{
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
	tree.draw(window);

	cursorPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

bool EntityList::checkBulletCollision(Bullet * bullet)
{
	if (bullet->isDestroyed() || bullet->isDuringDestroying())return false;
	if (tileMapPtr == nullptr)
	{
		bullet->kill();
		return true;
	}
	else {
		auto ents = tree.GetObjectsAt(bullet->getPosition());
		for each (Entity* ent in ents)
		{
			if (bullet->isDestroyed() || bullet->isDuringDestroying())return false;
			auto damageable = dynamic_cast<Damageable*>(ent);
			if (damageable != nullptr)
			{
				damageable->bulletCollision(bullet);
			}
		}

		auto tilesInLine = this->tileMapPtr->getTilesFromLine(bullet->getPreviousPosition(), bullet->getPosition());

		bool collided = false;

		for each (MapTile* mapTile in tilesInLine)
		{
			if (mapTile == nullptr)
			{
				bullet->destroy();
				return true;
			}

			if (mapTile->getMainTile() == nullptr)
			{
				continue;
			}

			auto tile = mapTile->getMainTile();
			sf::Vector2f collisionPoint = bullet->getPosition();
			if (tile->collide(bullet->getPreviousPosition(), bullet->getPosition(), collisionPoint))
			{
				DefaultTile* defaultTile = dynamic_cast<DefaultTile*>(tile.get());
				if (defaultTile == nullptr)
				{
					bullet->destroy();
					return true;
				}
				int damage = bullet->getDamage();
				bullet->decreaseDamage(defaultTile->getHealth());
				defaultTile->damage(damage);

				if (tile->isDestroyed())
				{
					sf::Vector2i tilePos = tileMapPtr->getTileId(tile->getPosition());
					tileMapPtr->destroyTile(tilePos.x, tilePos.y);
					particleSystem.onTileDestroy(tileMapPtr->getTile(tilePos.x, tilePos.y));
				}
				if (bullet->isDestroyed() || bullet->isDuringDestroying())
				{
					bullet->setPosition(collisionPoint);
					return false;
				}

				collided = true;
			}
			return collided;
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
			if (tileMapPtr != nullptr) {
				camera = Camera(
					sf::IntRect(0, 0, tileMapPtr->getMapSize().x, tileMapPtr->getMapSize().y),
					it->get());
			}
			return;
		}
		++it;
	}
	Logger::e("Character with name \"" + name + "\" not found!");
}

//void EntityList::setTilemapPtr(Tilemap * ptr)
//{
//	tilemapPtr = ptr;
//	particleSystem.setTilemapPointer(ptr);
//}

void EntityList::setTileMapPtr(TileMap * ptr)
{
	tileMapPtr = ptr;
	particleSystem.setTileMapPointer(ptr);
}