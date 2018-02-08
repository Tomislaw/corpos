#include "stdafx.h"
#include "CppUnitTest.h"
#include "src\game\engine\logic\ai\NavigationNode.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(NavigationNodeTest)
	{
	public:

		void WriteLine(std::string s)
		{
			Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(s.c_str());
		}

		int const test[10][10] = {
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 1, 1, 0, 0, 1, 0, 0, 0, 1, 1 }
		};
		Tile air2;
		Tile * getTileFast(sf::Vector2i v)
		{

			//mimic real get tile function
			int value = 0;
			if (v.x < 0 || v.y < 0 || v.x > 9 || v.y > 9)value = 0;
			else value = test[v.y][v.x];

			value = v.x + v.y * 500;
			return &air2;
		}

		Tile * getTile(sf::Vector2i v)
		{
			Tile air;


			TileDefinition d;
			d.is_blocking = true;
			d.name = "block";
			Tile block(&d, std::vector<sf::Vertex*>(), sf::Vector2f());

			int value = 0;;
			if (v.x < 0 || v.y < 0 || v.x > 9 || v.y > 9)
			{
				std::string debugStr = "";
				debugStr += "nullptr";
				debugStr += " (" + std::to_string(v.x) + "," + std::to_string(v.y) + ")";
				WriteLine(debugStr);
				return nullptr;
			}
			else value = test[v.y][v.x];

			std::string debugStr = "";
			debugStr += std::to_string(value);
			debugStr += " (" + std::to_string(v.x) + "," + std::to_string(v.y) + ")";
			WriteLine(debugStr);
			if (value == 1)
				return &block;
			else
				return &air;

			
		}
		TEST_METHOD(canStand)
		{
			WriteLine("canStand()");

			NavigationNodeCharacterData data;
			data.characterWidth = 1;

			NavigationNode node;
			node.setFunctionGetTile(std::bind(&NavigationNodeTest::getTile, this, std::placeholders::_1));
			node.setCharacterData(&data);

			WriteLine("   size 1");
			WriteLine("test1");
			Assert::AreEqual(true, node.canStand(1, 8));
			WriteLine("test2");
			Assert::AreEqual(false, node.canStand(1, 7));


			data.characterWidth = 2;
			node.setCharacterData(&data);

			WriteLine("   size 2");
			WriteLine("test1");
			Assert::AreEqual(false,node.canStand(6,8));
			WriteLine("test2");
			Assert::AreEqual(true,node.canStand(2, 8));

			data.characterWidth = 3;
			node.setCharacterData(&data);

			WriteLine("   size 3");
			WriteLine("test1");
			Assert::AreEqual(false, node.canStand(6, 8));
			WriteLine("test2");
			Assert::AreEqual(true, node.canStand(5, 8));
			WriteLine("test completed positive");



		}
		TEST_METHOD(canFit)
		{
			WriteLine("canFit()");

			NavigationNodeCharacterData data;
			data.characterWidth = 1;
			data.characterHeight = 3;
			

			NavigationNode node;
			node.setFunctionGetTile(std::bind(&NavigationNodeTest::getTile, this, std::placeholders::_1));
			node.setCharacterData(&data);
			WriteLine("   size 1x3");
			WriteLine("test1");
			Assert::AreEqual(false, node.canFit(0, 8));
			WriteLine("test2");
			Assert::AreEqual(true, node.canFit(1, 8));
			WriteLine("test2");
			Assert::AreEqual(false, node.canFit(1, 9));

			data.characterWidth = 3;
			node.setCharacterData(&data);

			WriteLine("   size 3x2");
			WriteLine("test1");
			Assert::AreEqual(false, node.canFit(1, 8));
			WriteLine("test2");
			Assert::AreEqual(true, node.canFit(2, 8));

			data.characterWidth = 2;
			node.setCharacterData(&data);

			WriteLine("   size 2x2");
			WriteLine("test1");
			Assert::AreEqual(false, node.canFit(1, 8));
			WriteLine("test2");
			Assert::AreEqual(true, node.canFit(2, 8));

		}
		TEST_METHOD(canMoveToTile)
		{

			WriteLine("canMoveToTile()");

			NavigationNodeCharacterData data;
			data.characterWidth = 2;
			data.characterHeight = 2;

			NavigationNode node;
			node.x = 1;
			node.y = 8;

			node.setCharacterData(&data);
			node.setFunctionGetTile(std::bind(&NavigationNodeTest::getTile, this, std::placeholders::_1));


			WriteLine("test1");
			Assert::AreEqual(true,node.canWalkToTile(2,8));

			node.x = 2;
			node.y = 8;
			WriteLine("test2");
			Assert::AreEqual(false, node.canWalkToTile(3, 8));

			node.x = 3;
			node.y = 8;

			WriteLine("test3");
			Assert::AreEqual(false, node.canWalkToTile(2, 8));

			node.x = 8;
			node.y = 8;

			WriteLine("test4");
			Assert::AreEqual(true, node.canWalkToTile(7, 8));

			node.x = 7;
			node.y = 8;

			WriteLine("test5");
			Assert::AreEqual(false, node.canWalkToTile(6, 8));

		}


		TEST_METHOD(canWalk_Speedtestx500)
		{
			NavigationNodeCharacterData data;
			data.characterWidth = 3;
			data.characterHeight = 3;


			NavigationNode node;
			node.setFunctionGetTile(std::bind(&NavigationNodeTest::getTileFast, this, std::placeholders::_1));
			node.setCharacterData(&data);

			for (int i = 0; i < 250; i++)
			{
				Assert::AreEqual(true, node.canFit(2, 8));
			}

			data.characterWidth = 2;
			node.setCharacterData(&data);

			for (int i = 0; i < 250; i++)
			{
				Assert::AreEqual(true, node.canFit(2, 8));
			}
			
		}

		TEST_METHOD(canStand_Speedtestx500)
		{
			NavigationNodeCharacterData data;
			data.characterWidth = 3;
			data.characterHeight = 3;


			NavigationNode node;
			node.setFunctionGetTile(std::bind(&NavigationNodeTest::getTileFast, this, std::placeholders::_1));
			node.setCharacterData(&data);

			for (int i = 0; i < 250; i++)
			{
				Assert::AreEqual(false, node.canStand(2, 8));
			}

			data.characterWidth = 2;
			node.setCharacterData(&data);

			for (int i = 0; i < 250; i++)
			{
				Assert::AreEqual(false, node.canStand(2, 8));
			}

		}

	};
}