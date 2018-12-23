#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <iostream>
#include <string>
#include <ctime>
#include <functional>
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
};

#endif