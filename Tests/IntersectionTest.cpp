#include "stdafx.h"
#include "CppUnitTest.h"
#include "game\utility\Intersection.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(IntersectionTest)
	{
	public:

		void WriteLine(std::string s)
		{
			Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(s.c_str());
		}

		TEST_METHOD(LineLineIntersectionPoint)
		{
			sf::Vector2f target;
			sf::Rect<float> rect = sf::FloatRect(5, 5, 45, 45);

			bool test = Intersection::LineSegRectIntersectionPoint
			(sf::Vector2f(20, 0), sf::Vector2f(20, 50), rect, target);
			Assert::IsTrue(test);

			test = Intersection::LineSegRectIntersectionPoint
			(sf::Vector2f(0, 0), sf::Vector2f(50, 50), rect, target);
			Assert::IsTrue(test);

			test = Intersection::LineSegRectIntersectionPoint
			(sf::Vector2f(0, 30), sf::Vector2f(50, 30), rect, target);
			Assert::IsTrue(test);

			test = Intersection::LineSegRectIntersectionPoint
			(sf::Vector2f(50, 30), sf::Vector2f(0, 30), rect, target);
			Assert::IsTrue(test);

			test = Intersection::LineSegRectIntersectionPoint
			(sf::Vector2f(0, 0), sf::Vector2f(30, 30), rect, target);
			Assert::IsTrue(test);

			test = Intersection::LineSegRectIntersectionPoint
			(sf::Vector2f(0, 0), sf::Vector2f(0, 50), rect, target);
			Assert::IsFalse(test);
		}
	};
}