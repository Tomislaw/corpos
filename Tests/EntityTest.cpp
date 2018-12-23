#include "stdafx.h"
#include "CppUnitTest.h"
#include "game\engine\Entity.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(EntityTest)
	{
	public:

		TEST_METHOD(constructor)
		{
			TextElement e;
			Variable name;
			name.name = "Name";
			name.var.push_back("test1");

			Variable position;
			position.name = "Position";
			position.var.push_back("20");
			position.var.push_back("10");

			e.variable.push_back(name);
			e.variable.push_back(position);

			Entity ent = Entity(nullptr);
			ent = Entity(&e);

			Assert::AreEqual("test1", ent.getName().c_str());

			Assert::AreEqual(20.f, ent.getPosition().x);

			Assert::AreEqual(10.f, ent.getPosition().y);
		}

		TEST_METHOD(update)
		{
			Entity e;

			e.setPosition(sf::Vector2f(50, 50));
			Assert::AreEqual(e.getPosition().y, sf::Vector2f(50, 50).y);

			e.setVelocity(sf::Vector2f(50, 50));
			e.update(50);

			sf::Vector2f position;
			position.x += 50 * 50;
			position.y += 50 * 50;
			position += sf::Vector2f(50, 50);

			Assert::AreEqual(e.getPosition().x, position.x);
			// TODO: Your test code here
		}
		TEST_METHOD(parent)
		{
			Entity e;

			Entity e2;

			e2.attachToEntity(&e);

			e.setPosition(sf::Vector2f(-500, -200));
			e.setVelocity(sf::Vector2f(50, 50));
			e.update(10);
			e2.update(10);

			Assert::AreEqual(e.getPosition().x, e2.getPosition().x);
			Assert::AreEqual(e.getPosition().y, e2.getPosition().y);

			e.update(0.4);
			e2.update(0.4);

			Assert::AreEqual(e.getPosition().x, e2.getPosition().x);
			Assert::AreEqual(e.getPosition().y, e2.getPosition().y);

			e2.setAttachOffset(sf::Vector2f(5, 0));

			e.update(10);
			e2.update(1);

			Assert::AreEqual(e.getPosition().x, e2.getPosition().x - 5);
			Assert::AreEqual(e.getPosition().y, e2.getPosition().y);

			e2.attachToEntity(nullptr);

			e.update(0.4);
			e2.update(0.4);

			Assert::AreNotEqual(e.getPosition().x, e2.getPosition().x - 5);
			Assert::AreNotEqual(e.getPosition().y, e2.getPosition().y);
		}
	};
}