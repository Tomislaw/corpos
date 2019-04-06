#ifndef AIBASIC_HPP
#define AIBASIC_HPP
#include "game\engine\Character.hpp"
#include "NavigationNode.hpp"
#include <queue>
#include "game\utility\Pathfind.hpp"
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>

class AiAction {
public:
	enum ActionResult {
		NOT_FINISHED, FAILED, SUCCEED
	};

	AiAction(Character & controlledCharacter) : character(controlledCharacter) {};
	virtual bool start() = 0;
	virtual void update(float delta) = 0;
	virtual void stop() = 0;
	virtual void drawDebugData(sf::RenderTarget &target) {}
	virtual ActionResult status() { return result; }
protected:
	Character & character;
	ActionResult result = NOT_FINISHED;
};

class MoveToTile : public AiAction {
public:
	MoveToTile(Character & controlledCharacter, sf::Vector2i target) : AiAction(controlledCharacter),
		pathfind(controlledCharacter.getNavigationNodeCharacterData()),
		targetTile(target) {
	};

	virtual void drawDebugData(sf::RenderTarget &target);

	bool start()  override {
		auto position = character.getCenteredPosition();
		findPathThread = std::thread([this, position]() {
			auto startNode = AStar::Node(position);
			auto tilePos = targetTile * 2 + sf::Vector2i(1, 1);
			path = pathfind.findPath(startNode, tilePos);
			isRouteCalculated = true;
		});
		return true;
	}

	void update(float delta) override {
		if (!isRouteCalculated)return;
		if (!path.empty())
		{
			// delete node if reached
			AStar::Node node;
			AStar::Node *previousNode = nullptr;

			if (path.front().isReached(character, previousNode))
			{
				node = path.front();
				path.pop_front();
				if (path.empty()) { character.stop(); return; }
			}

			path.front().timeSpend -= delta;
			//clear queue if reaching takes too much time
			if (path.front().timeSpend < 0)
			{
				while (!path.empty()) path.pop_front();
				character.stop();
				return;
			}

			int type = path.front().type;

			switch (type)
			{
			case AStar::Node::AFTER_JUMP:
			case AStar::Node::JUMP:
				if (character.getCenteredPosition().x > node.getPosition().x) {
					if (character.getVelocity().x < 0)
						character.jump();
				}
				else {
					if (character.getVelocity().x > 0)
						character.jump();
				}

			case AStar::Node::WALK:
			case AStar::Node::BEFORE_JUMP:
			case AStar::Node::CENTER_POSITION:
			case AStar::Node::FALL:

				if (character.getCenteredPosition().x > path.front().getPosition().x)
					character.walkLeft();
				else
					character.walkRight();

				break;
			default:

				break;
			}
		}
		else if (result == NOT_FINISHED) {
			result = SUCCEED;
			stop();
		}
	}

	void stop() override {

		pathfind.stop();
		if (findPathThread.joinable()) findPathThread.join();

		if (result == NOT_FINISHED)
			result = FAILED;
	}

private:

	AStar::PathFind pathfind;
	AStar::NodeDeque path;
	std::thread findPathThread;
	std::atomic<bool> isRouteCalculated = false;

	sf::Vector2i targetTile;
};

class AiBasic
{
public:
	AiBasic(Character & character);

	virtual void update(float delta);
	~AiBasic();


	virtual void drawDebugData(sf::RenderTarget &target);

	enum Behavior { IDLE, ALERTED, ENGAGE, SUSPICIOUS, PANIC };

	void moveToTile(sf::Vector2i tile);

	void getPath(sf::Vector2i tile);

protected:
	std::shared_ptr<AiAction> action = nullptr;

	Character & character;
	EntityList * entityListPtr = nullptr;
	TileMap * tilemapPtr = nullptr;

	int behavior = 0;
	bool isInitialized = false;
	sf::Text entityDebugText;
};

class TestAi: public AiBasic {
public:

	TestAi(Character & character, Entity * target) : AiBasic(character)
	{
		this->target = target;
	}

	virtual void update(float delta)  override
	{
		timeToSearchAgain -= delta;
		if (timeToSearchAgain < 0) {
			timeToSearchAgain = 0.5 + (rand() % 100) * 0.008;;

			if (Character* d = dynamic_cast<Character*>(target)) 
			{
			auto distance = character.getPosition().x - d->getPosition().x;
			auto distanceY = abs(character.getPosition().y - d->getPosition().y);

			if (distance < 60 && distance > 0 && distanceY < 10) {
				character.walkLeft();
			}
			else if (distance > -60 && distance < 0 && distanceY < 10) {
				character.walkRight();
			}else if (!(distance > 700 || distance < -700))
				getPath(d->getStandingTileId());
			}
		}
		AiBasic::update(delta);
	}

private:
	Entity * target;
	float timeToSearchAgain = 1;
};


#endif