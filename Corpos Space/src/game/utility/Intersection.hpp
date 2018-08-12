#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <SFML\Graphics.hpp>

namespace Intersection
{ 

template <class Numeric>
sf::Vector2<Numeric> LineLineIntersectionPoint(sf::Vector2<Numeric> &a, sf::Vector2<Numeric> &b,
										sf::Vector2<Numeric> &c, sf::Vector2<Numeric> &d)
{
	// Get A,B of first line - points : ps1 to pe1
	double A1 = b.y - a.y;
	double B1 = a.x - b.x;
	// Get A,B of second line - points : ps2 to pe2
	double A2 = d.y - c.y;
	double B2 = c.x - d.x;
	
	// Get delta and check if the lines are parallel
	double delta = A1*B2 - A2*B1;
	if (delta == 0) sf::Vector2<Numeric>(std::numeric_limits<Numeric>::max(), std::numeric_limits<Numeric>::max());
	// Get C of first and second lines
	double C2 = A2*c.x + B2*c.y;
	double C1 = A1*a.x + B1*a.y;
	//invert delta to make division cheaper
	double invdelta = 1 / delta;
	// now return the Vector2 intersection point
	return sf::Vector2<Numeric>((Numeric)((B2*C1 - B1*C2)*invdelta), (Numeric)((A1*C2 - A2*C1)*invdelta));
}

template <class Numeric>
bool isLineSegLineSegIntersect(sf::Vector2<Numeric> &a, sf::Vector2<Numeric> &b, sf::Vector2<Numeric> &c, sf::Vector2<Numeric> &d)
{
	double denominator = ((b.x - a.x) * (d.y - c.y)) - ((b.y - a.y) * (d.x - c.x));
	double numerator1 = ((a.y - c.y) * (d.x - c.x)) - ((a.x - c.x) * (d.y - c.y));
	double numerator2 = ((a.y - c.y) * (b.x - a.x)) - ((a.x - c.x) * (b.y - a.y));

	// Detect coincident lines
	if (denominator == 0) return numerator1 == 0 && numerator2 == 0;

	double r = numerator1 / denominator;
	double s = numerator2 / denominator;

	return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
}

template <class Numeric>
bool LineSegLineSegIntersectionPoint(sf::Vector2<Numeric> &a, sf::Vector2<Numeric> &b,
	sf::Vector2<Numeric> &c, sf::Vector2<Numeric> &d, sf::Vector2<Numeric> &intersect)
{
	if (isLineSegLineSegIntersect(a, b, c, d))
	{
		intersect = LineLineIntersectionPoint(a, b, c, d);
		return true;
	}
	return false;
}

template <class Numeric>
bool LineSegRectIntersectionPoint(sf::Vector2<Numeric> &start, sf::Vector2<Numeric> &end,
	sf::Rect<Numeric> rect, sf::Vector2<Numeric> &intersect)
{
	auto a = sf::Vector2<Numeric>(rect.left, rect.top);
	auto b = sf::Vector2<Numeric>(rect.left + rect.width, rect.top);
	auto c = sf::Vector2<Numeric>(rect.left + rect.width, rect.top + rect.height);
	auto d = sf::Vector2<Numeric>(rect.left, rect.top + rect.height);

	if (start.y < a.y)
	{
		if (isLineSegLineSegIntersect(start, end, a, b))
		{
			intersect = LineLineIntersectionPoint(start, end, a, b);
			return true;
		}
	}
	if (start.x > a.x)
	{
		if (isLineSegLineSegIntersect(start, end, b, c))
		{
			intersect = LineLineIntersectionPoint(start, end, b, c);
			return true;
		}
	}
	if (start.y > a.y)
	{
		if (isLineSegLineSegIntersect(start, end, c, d))
		{
			intersect = LineLineIntersectionPoint(start, end, c, d);
			return true;
		}
	}
	if (start.x < a.x)
	{
		if (isLineSegLineSegIntersect(start, end, d, a))
		{
			intersect = LineLineIntersectionPoint(start, end, d, a);
			return true;
		}
	}
	return false;
}
}
#endif