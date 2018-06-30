#include "EntityList.hpp"
#include "World.hpp"
#include "src\game\main\Cursor.hpp"
#include "src\game\engine\logic\ai\AiBasic.hpp"
std::vector <GameSprite> EntityList::game_sprite_definitions = std::vector <GameSprite>();

EntityList::EntityList()
	: particleSystem(100)
{
}


EntityList::~EntityList()
{
}

void EntityList::loadMap(TextFileData & file)
{
	if (tilemapPtr == nullptr)return;
	tree = Quadtree(sf::Vector2f(), tilemapPtr->getMapSize(), 0, 4, 5);
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
		sf::Texture * t = GameAssetsManager::getTexture(s);
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

		if (e.mouseButton.button == sf::Mouse::Right)
		{
			auto ents = tree.GetObjectsAt(player.getCharacter()->getPosition());
			std::cout << "Entities at player pos :" << std::endl;
			for each (Entity* var in ents)
			{
				std::cout << var->getName() << " " << var->getPosition().x << " " << var->getPosition().y << std::endl;
			}
			
			auto tile = tilemapPtr->getTileId(cursorPos.x, cursorPos.y);
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
		if(it2->get()->isDestroyed())it2 = props.erase(it2);
		else
		{
			tree.AddObject(it2->get());
			++it2;
		}
	}
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
	particleSystem.update(time);
}

void EntityList::draw(sf::RenderWindow & window)
{
	camera.setForegroundView(window);
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
	if (tilemapPtr == nullptr)
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
