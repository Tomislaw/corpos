#include "game/utility/json-utils.h"

// for convenience
using json = nlohmann::json;
using namespace corpos;
#include "stdafx.h"
#include "CppUnitTest.h"
#include "game\utility\Intersection.hpp"

namespace Tests
{
	TEST_CLASS(JsonTest)
	{
	public:

		void WriteLine(std::string s)
		{
			Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(s.c_str());
		}

		TEST_METHOD(ReadWrite)
		{
			json j;
			j["name"] = "test";
			j["size"] = { 1.1,"",3 };

			auto a = j["size"].get(std::vector<int>());

			WriteLine(std::to_string(a.size()));

			std::ofstream("pretty.json") << j << std::endl;
			//std::ofstream("pretty.json") << std::setw(4) << j << std::endl;
		}
	};
}