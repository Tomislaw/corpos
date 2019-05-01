#include "stdafx.h"
#include "CppUnitTest.h"
#include "game\map\TileMap.h"
using Microsoft::VisualStudio::CppUnitTestFramework::Assert;
using namespace corpos;

namespace Tests
{
	TEST_CLASS(TileMapTest)
	{
	public:

		void WriteLine(std::string s)
		{
			Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(s.c_str());
		}

		TEST_METHOD(LoadMap)
		{
			GameAssetsManager::loadTextures("bin/graphics/textures/texture_definition.txt");
			GameAssetsManager::loadSprites("bin/graphics/sprite/sprite_definitions.txt");
			TileMap map;
			TextFileData file;
			file.loadFile("bin/map/mm.txt");
			auto tm = file.getFirstElementByName("TILEMAP");

			//its important to load tilemap first
			map.loadTileset("bin/graphics/tileset/tileset1.txt");
			map.loadMap(*tm);
		}
	};
}