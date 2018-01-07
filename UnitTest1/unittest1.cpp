#include "stdafx.h"
#include "CppUnitTest.h"
#include <TextFileData.hpp>
#include <Logger.hpp>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestValueIsValid)
		{
			TextFileData file;
			file.loadFile("test1.txt");
			std::string expected = "name";
			Assert::AreEqual(file.getFirstElementByName("TILEMAP")->getVariableByName("Name")->toString(0),expected);
		}

		TEST_METHOD(TestValueIsNull)
		{
			TextFileData file;
			std::cout << file.loadFile("test1.txt");
			std::string expected = "";

			Assert::AreEqual(expected, file.getFirstElementByName("TILEMAP")->getVariableByName("Name")->toString(0));
		}

	};
}