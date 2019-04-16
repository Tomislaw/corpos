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
	props.clear();
	characters.clear();
	landscapes.clear();
	bullets.clear();
	entities.clear();

	//if (tilemapPtr == nullptr)return;
	//tree = Quadtree(sf::Vector2f(), tilemapPtr->getMapSize(), 0, 4, 5);

	if (tileMapPtr == nullptr)return;
	tree = Quadtree(sf::Vector2f(), tileMapPtr->getMapSize(), 0, 8, 1);

	auto map_props = file.getAllElementsByName("PROP");
	for (int i = 0; i < map_props.size(); i++)
	{
		auto p = std::shared_ptr<Prop>(new  Prop(map_props.at(i), this));
		addProp(p);
	}

	auto map_characters = file.getAllElementsByName("CHARACTER");
	for (int i = 0; i < map_characters.size(); i++)
	{
		auto p = CharacterFactory::create(map_characters.at(i), this);
		addCharacter(p);
	}

	auto map_landscapes = file.getAllElementsByName("LANDSCAPE");
	for (int i = 0; i < map_landscapes.size(); i++)
	{
		auto p = std::shared_ptr<Landscape>(new Landscape(map_landscapes.at(i)));
		addLandscape(p);
	}
	setPlayerEntity("@player");
}

void EntityList::addCharacter(std::shared_ptr<Character> & ent)
{
	if (ent == nullptr) return;
	entities.push_back(ent);
	characters.push_back(ent);
	if (ent->getName() != "@player") {
		ent->getAiController() = std::make_shared<TestAi>(*ent.get(), characters.at(0).get());
	}
}

void EntityList::addProp(std::shared_ptr<Prop>& ent)
{
	entities.push_back(ent);
	props.push_back(ent);
}

void EntityList::addLandscape(std::shared_ptr<Landscape>& ent)
{
	entities.push_back(ent);
	landscapes.push_back(ent);
}

void EntityList::addBullet(std::shared_ptr<Bullet>& bullet)
{
	bullets.push_back(bullet);
}

std::shared_ptr<Entity> EntityList::findEntity(std::string name)
{
	std::vector<std::shared_ptr <Entity>> ents;
	for (auto entity : entities)
		if (entity->getName() == name) ents.push_back(entity);
	return std::shared_ptr <Entity>();
}

std::vector<std::shared_ptr<Entity>> EntityList::findEntities(std::string name)
{
	std::vector<std::shared_ptr <Entity>> ents;
	for (auto entity : entities) 
		if (entity->getName() == name) ents.push_back(entity);
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
	auto bullet = bullets.begin();


	while (bullet != bullets.end())
	{
		bullet->get()->update(time);
		checkBulletCollision(bullet->get());
		if (bullet->get()->isDestroyed())
			bullet = bullets.erase(bullet);
		else
			++bullet;
	}

	player.update(time);
	tree.Clear();
	auto character = characters.begin();
	while (character != characters.end())
	{
		character->get()->update(time);
		if (character->get()->getPosition().y > tileMapPtr->getMapSize().y)
			character->get()->destroy();

		resolveActions(character->get()->actions());

		if (character->get()->isDestroyed())
			character = characters.erase(character);
		else
		{
			tree.AddObject(character->get());
			++character;
		}
	}
	auto prop = props.begin();
	while (prop != props.end())
	{
		resolveActions(prop->get()->actions());
		prop->get()->update(time);
		if (prop->get()->isDestroyed())
			prop = props.erase(prop);
		else
		{
			tree.AddObject(prop->get());
			++prop;
		}
	}
	auto landscape = landscapes.begin();
	while (landscape != landscapes.end())
	{
		resolveActions(landscape->get()->actions());
		landscape->get()->update(time);
		landscape++;
		/*if (it4->get()->isDestroyed())it4 = landscapes.erase(it2);
		else
		{
			tree.AddObject(it2->get());
			++it2;
		}*/
	}
	particleSystem.update(time);
}

void EntityList::draw(sf::RenderWindow & window)
{
	auto it = characters.begin();
	while (it != characters.end())
	{
		it->get()->draw(window);
		++it;
	}
	auto it2 = props.begin();
	while (it2 != props.end())
	{
		it2->get()->draw(window);
		++it2;
	}
	auto it3 = bullets.begin();
	while (it3 != bullets.end())
	{
		it3->get()->draw(window);
		++it3;
	}
	auto it4 = landscapes.begin();
	while (it4 != landscapes.end())
	{
		if (it4->get()->isForeground()) it->get()->draw(window);
		++it4;
	}
	window.draw(particleSystem);
	//tree.draw(window);

	cursorPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void EntityList::drawBackground(sf::RenderWindow & window)
{
	std::vector<std::shared_ptr <Landscape>>::iterator it = landscapes.begin();
	while (it != landscapes.end())
	{
		if (!it->get()->isForeground()) it->get()->draw(window);
		++it;
	}
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
			if (bullet->isDestroyed() || bullet->isDuringDestroying()) return false;
			auto damageable = dynamic_cast<Damageable*>(ent);
			if (damageable != nullptr)
				damageable->bulletCollision(bullet);
		}

		auto tilesInLine = this->tileMapPtr->getTilesFromLine(bullet->getPreviousPosition(), bullet->getPosition());

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

void EntityList::resolveActions(ActionManager manager)
{
	for (auto &action : manager.outputs.pendingActions) {

		if (action.targetName == "@world")
			actionManager.inputs.invokeInput(action);
		else
			for (auto entity : findEntities(action.targetName))
				entity->actions().inputs.invokeInput(action);
	}
}
