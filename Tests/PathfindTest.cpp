#include "stdafx.h"
#include "CppUnitTest.h"
#include "src\game\utility\Node.hpp"
#include "game/map/MapTile/MapTile.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	class TestTileCollidable : public AbstractTile {
		bool isBlocking() override {return true;}
	};


	TEST_CLASS(PathfindUtilsTest)
	{
	public:

		void WriteLine(std::string s)
		{
			Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(s.c_str());
		}

		int const test[10][10] = {
			//0 /1 /2 /3 /4 /5 /6 /7 /8 /9 x  /y
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//0
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//1
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//2
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//3
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//4
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//5
			{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },//6
			{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },//7
			{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },//8
			{ 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 } //9
		};
		MapTile tileNotBlocking;
		MapTile tileBlocking = MapTile(std::make_shared<TestTileCollidable>());
		MapTile * getTileFast(int x, int y)
		{
			//mimic real get tile function
			int value = 0;
			if (x < 0 || y < 0 ||x > 9 || y > 9) return nullptr;
			else value = test[y][x];

			WriteLine(PrettyString(x, y, value!=0).str());
			if (value == 0) return &tileNotBlocking;
			else return &tileBlocking;
		}

		TEST_METHOD(canFitInTile)
		{
			WriteLine("canFitInTile()");

			std::function<MapTile*(int x, int y)> function = std::bind(&PathfindUtilsTest::getTileFast, this, std::placeholders::_1, std::placeholders::_2);;
			AStar::PathfindUtils::getTile = function;

			NavigationNodeCharacterData data;
			data.characterWidth = 2;
			data.characterHeight = 4;

			WriteLine("No collision");
			Assert::IsTrue(AStar::PathfindUtils::canFitInTile(sf::Vector2i(1,17),data));
			WriteLine("Left collision");
			Assert::IsTrue(!AStar::PathfindUtils::canFitInTile(sf::Vector2i(4, 17), data));
			WriteLine("Right collision");
			Assert::IsTrue(!AStar::PathfindUtils::canFitInTile(sf::Vector2i(2, 17), data));
			WriteLine("Top collision");
			Assert::IsTrue(!AStar::PathfindUtils::canFitInTile(sf::Vector2i(7, 17), data));
			WriteLine("Bottom collision");
			Assert::IsTrue(!AStar::PathfindUtils::canFitInTile(sf::Vector2i(7, 18), data));
		}
	};
}