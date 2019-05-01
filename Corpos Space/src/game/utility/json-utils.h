#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include "game/utility/json.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "game/utility/Logger.hpp"

using nlohmann::json;
namespace sf
{
	template<typename T>
	void to_json(json& j, const Vector2<T>& p) {
		j = json{ p.x, p.y };
	}

	template<typename T>
	void from_json(const json& j, Vector2<T>& p) {
		j.at(0).get_to(p.x);
		j.at(1).get_to(p.y);
	}

	template<typename T>
	void to_json(json& j, const Rect<T>& p) {
		j = json{ p.left, p.top, p.width, p.height };
	}

	template<typename T>
	void from_json(const json& j, Rect<T>& p) {
		j.at(0).get_to(p.left);
		j.at(1).get_to(p.top);
		j.at(2).get_to(p.width);
		j.at(3).get_to(p.height);
	}
}

namespace json_utils
{
	extern std::string localDiretory;
	extern json from_file(std::string directory);
	extern void to_file(json & data, std::string directory);
}

#endif