#include "Logger.hpp"


Logger::Logger(const Logger &)
{
	this->logs = logs;
	this->callback = callback;
}

Logger & Logger::getInstance()
{
	static Logger instance;
	return instance;
}

void Logger::i(std::string info)
{
	Logger::getInstance().log(info,0);
}

void Logger::d(std::string info)
{
	Logger::getInstance().log(info, 1);
}

void Logger::e(std::string info)
{
	Logger::getInstance().log(info, 2);
}

void Logger::log(std::string info , int type)
{


	std::string stime;

	time_t rawtime = time(0);
	struct tm timeinfo;
	errno_t error = localtime_s(&timeinfo, &rawtime);

	stime = std::toString(timeinfo.tm_year + 1900) + "-";

	if (timeinfo.tm_mon > 9)stime += std::toString(timeinfo.tm_mon) + "-";
	else stime += "0" + std::toString(timeinfo.tm_mon) + "-";

	if (timeinfo.tm_mday > 9)stime += std::toString(timeinfo.tm_mday) + " | ";
	else stime += "0" + std::toString(timeinfo.tm_mday) + " | ";

	if (timeinfo.tm_hour > 9)stime += std::toString(timeinfo.tm_hour) + ":";
	else stime += "0" + std::toString(timeinfo.tm_hour) + ":";

	if (timeinfo.tm_min > 9)stime += std::toString(timeinfo.tm_min) + ":";
	else stime += "0" + std::toString(timeinfo.tm_min) + ":";

	if (timeinfo.tm_sec > 9)stime += std::toString(timeinfo.tm_sec);
	else stime += "0" + std::toString(timeinfo.tm_sec);


	std::string sinfo;
	if (type == 0)sinfo = "[info] ";
	if (type == 1)sinfo = "[debug] ";
	if (type == 2)sinfo = "[error!] ";
	std::string i = sinfo + stime + " - " + info + "\n";

	std::cout << i;
	logs += i;

	if (callback != nullptr)callback(i);
}
