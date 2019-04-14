#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <iostream>
#include <string>
#include <ctime>
#include <functional>
#include <any>
#include <SFML/Graphics.hpp>
#include <ctype.h>

class Loggable {
public:
	virtual std::string toString() = 0;
};

class Logger
{
protected:
	Logger() = default;
	Logger(const Logger &);
	void log(std::string info, int type);
	std::string logs;

	enum LOGLEVEL
	{
		DEBUG,
		INFO,
		WARNING,
		FATAL
	};

public:
	static Logger & getInstance();
	std::function<void(std::string)> callback;

	static void d(std::string message)
	{
		Logger::getInstance().log(message, LOGLEVEL::DEBUG);
	}
	static void i(std::string message)
	{
		Logger::getInstance().log(message, LOGLEVEL::INFO);
	}
	static void w(std::string message)
	{
		Logger::getInstance().log(message, LOGLEVEL::WARNING);
	}
	static void e(std::string message)
	{
		Logger::getInstance().log(message, LOGLEVEL::FATAL);
	}

	template<typename... Params> static void d(std::string message, Params... params)
	{
		Logger::getInstance().log(PrettyString(params...).formatted(message), LOGLEVEL::DEBUG);
	}
	template<typename... Params> static void i(std::string message, Params... params)
	{
		Logger::getInstance().log(PrettyString(params...).formatted(message), LOGLEVEL::INFO);
	}
	template<typename... Params> static void w(std::string message, Params... params)
	{
		Logger::getInstance().log(PrettyString(params...).formatted(message), LOGLEVEL::WARNING);
	}
	template<typename... Params> static void e(std::string message, Params... params)
	{
		Logger::getInstance().log(PrettyString(params...).formatted(message), LOGLEVEL::FATAL);
	}
};

class PrettyString {
public:

	template<typename... ArgTypes>
	PrettyString(ArgTypes... args) {
		parse(args...);
	}

	std::string str();

	std::string formatted(std::string message);

private:
	std::vector<std::pair<std::string, bool>> values;

	std::string getValueToInsert(unsigned int id) {
		if (id >= values.size()) return "";

		values.at(id).second = true;
		return values.at(id).first;
	}

	void add(std::string str) {
		values.push_back(std::pair<std::string, bool>(str, false));
	}

	template< typename... ArgTypes> void parse(ArgTypes... args) {}

	template<typename T, typename... ArgTypes>
	void parse(T t, ArgTypes... args) {
		if (Loggable * loggable = dynamic_cast<T&>(&t))
		{
			add(loggable->toString());
			parse(args...);
			return;
		}

		std::any object = t;
		std::string value = "("; value += object.type().name(); value += "#)";
		add(value);
		parse(args...);
	}

	template<typename T, typename... ArgTypes>
	void parse(T* t, ArgTypes... args) {
		std::string name = typeid(T).name();
		std::string value = "("; value += name; value += "-ptr#" + std::to_string((int)t);
		add(value);
		parse(args...);
	}

	template<typename T, typename... ArgTypes>
	void parse(sf::Vector2<T> vector, ArgTypes... args) {
		add("{ x = " + PrettyString(vector.x).str() + ", y = " + PrettyString(vector.y).str() + " }"); parse(args...);
	}

	template<typename T, typename... ArgTypes>
	void parse(std::vector<T> vector, ArgTypes... args) {
		std::string value = "{";
		for (int i = 0; i < vector.size(); i++) {
			value += PrettyString(vector.at(i)).str();
			if (i == vector.size() - 1) continue;
			value += ", ";
		}
		value += '}';
		add(value);
		parse(args...);
	}

	template<typename... ArgTypes> void parse(int integer, ArgTypes... args) { add(std::to_string(integer)); parse(args...); }
	template<typename... ArgTypes> void parse(unsigned int number, ArgTypes... args) { add(std::to_string(number)); parse(args...); }
	template<typename... ArgTypes> void parse(long int number, ArgTypes... args) { add(std::to_string(number)); parse(args...); }
	template<typename... ArgTypes> void parse(unsigned long int number, ArgTypes... args) { add(std::to_string(number)); parse(args...) }
	template<typename... ArgTypes> void parse(long long int number, ArgTypes... args) { add(std::to_string(number)); parse(args...); }
	template<typename... ArgTypes> void parse(unsigned long long int number, ArgTypes... args) { add(std::to_string(number)); parse(args...); }
	template<typename... ArgTypes> void parse(float number, ArgTypes... args) { add(std::to_string(number));  parse(args...); }
	template<typename... ArgTypes> void parse(double number, ArgTypes... args) { add(std::to_string(number)); parse(args...); }
	template<typename... ArgTypes> void parse(long double number, ArgTypes... args) { add(value += std::to_string(number)); parse(args...); }

	template<typename... ArgTypes> void parse(std::string str, ArgTypes... args) { add(str); parse(args...); }
	template<typename... ArgTypes> void parse(char *character, ArgTypes... args) { add("" + character); parse(args...); }
	template<typename... ArgTypes> void parse(const char *character, ArgTypes... args) { add(std::string(character)); parse(args...); }
	template<typename... ArgTypes> void parse(char character, ArgTypes... args) { add("" + character); parse(args...); }
	template<typename... ArgTypes> void parse(bool is, ArgTypes... args) { if (is) add("true"); else add("false"); parse(args...); }

	template<> void parse() {}
};

#endif