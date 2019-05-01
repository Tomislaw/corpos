#include "stdafx.h"
#include "CppUnitTest.h"
#include "src\game\utility\TextFileData.hpp"
#include <vector>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace corpos;
/*
namespace Tests
{
	TEST_CLASS(TextFileDataTest)
	{
	public:

		TEST_METHOD(saveFile)
		{
			TextFileData file;
			std::vector<TextElement>elemets;
			TextElement element1;
			element1.name = "element1";

			Variable v1;
			v1.name = "v1";
			v1.var.push_back("0.5");
			v1.var.push_back("5");
			element1.variable.push_back(v1);

			elemets.push_back(element1);

			file.setElements(elemets);

			bool ok = file.saveToFile("tests/test.txt");
			Assert::AreEqual(true, ok);
		}

		TEST_METHOD(loadFile)
		{
			TextFileData file;

			bool load = file.loadFile("tests/test.txt");
			Assert::AreEqual(true, load);

			auto element = file.getFirstElementByName("element1");
			Assert::AreEqual("element1", element->name.c_str());
			auto var = element->getVariableByName("v1");
			Assert::AreEqual(var->toFloat(0), 0.5f);
			Assert::AreEqual(var->toInt(1), 5);
		}

		TEST_METHOD(findElement)
		{
			TextFileData file;
			std::vector<TextElement>elemets;

			TextElement element1;
			element1.name = "element1";

			elemets.push_back(element1);

			file.setElements(elemets);

			auto a = file.getFirstElementByName("element1");
			Assert::AreEqual(true, a->name == "element1");

			auto b = file.getFirstElementByName("element2");

			Assert::AreEqual(true, b == nullptr);
		}

		TEST_METHOD(replaceElement)
		{
			TextFileData file;
			std::vector<TextElement>elemets;

			TextElement element1;
			element1.name = "element1";

			TextElement element2;
			element2.name = "element2";

			Variable v1;
			v1.name = "v1";
			v1.var.push_back("0.5");
			v1.var.push_back("5");
			element2.variable.push_back(v1);

			elemets.push_back(element1);

			file.setElements(elemets);
			file.replaceElement(element2, "element1");

			auto element = file.getFirstElementByName("element2");
			Assert::AreEqual(true, element->name == "element2");
			Assert::AreEqual(size_t(1), element->variable.size());

			auto var = element->getVariableByName("v1");

			Assert::AreEqual(var->toFloat(0), 0.5f);
			Assert::AreEqual(var->toInt(1), 5);
		}
	};
}*/