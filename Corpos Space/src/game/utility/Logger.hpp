#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <iostream>
#include <string>
#include <ctime>
#include <functional>
#include <any>
#include <SFML/Graphics.hpp>
class Logger
{
protected:
	Logger() = default;
	Logger(const Logger &);
	void log(std::string info, int type);
	std::string logs;
public:
	static Logger & getInstance();
	static void i(std::string info);
	static void d(std::string info);
	static void e(std::string info);

	std::function<void(std::string)> callback;

	template<class... Unknown>
	void prettyString(Unknown... params) {
		for (int i = 0; i < params.size; i++) {
			PrettyString();
		}
	}
};

class PrettyString {
public:

	template<typename... ArgTypes>
	PrettyString(ArgTypes... args) {
		parse(args...);
	}

	std::string str() {
		return value;
	}

	
private:
	std::string value;

	template< typename... ArgTypes> void parse(ArgTypes... args) {}

	template<typename T, typename... ArgTypes>
	void parse(T t, ArgTypes... args) {
		std::any object = t;
		
		value += object.type().name();
		value += +'#';
		value += object.type().hash_code();

		parse(args...);
	}

	template<typename T, typename... ArgTypes>
	void parse(sf::Vector2<T> vector, ArgTypes... args) {
		value += "{ x = " + PrettyString(vector.x).str() + ", y = " + PrettyString(vector.y).str() + " }"; parse(args...);
	}

	template<typename T, typename... ArgTypes>
	void parse(std::vector<T> vector, ArgTypes... args) {

		value += "{";
		for (int i = 0; i < vector.size(); i++) {
			value += PrettyString(vector.at(i)).str();
			if (i == vector.size() - 1) continue();
			value += ", "
		}
		parse(args...);
	}

	template<typename... ArgTypes>
	void parse(int integer, ArgTypes... args) {
		value += std::to_string(integer); parse(args...);
		std::to_string
	}

	template<typename... ArgTypes>
	void parse(unsigned long long int number, ArgTypes... args) {
		value += std::to_string(number); parse(args...);
	}

	template<typename... ArgTypes>
	void parse(long long int number, ArgTypes... args) {
		value += std::to_string(number); parse(args...);
	}

	template<typename... ArgTypes>
	void parse(long double number, ArgTypes... args) {
		value += std::to_string(number);  parse(args...);
	}

	template<typename... ArgTypes>
	void parse(std::string str, ArgTypes... args) {
		value += str;	parse(args...);
	}

	template<typename... ArgTypes>
	void parse(char character, ArgTypes... args) {
		value += character; parse(args...);
	}

	template<> void parse() {}
};

#endif