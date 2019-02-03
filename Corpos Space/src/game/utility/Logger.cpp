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

void Logger::log(std::string info, int type)
{
	std::string stime;

	time_t rawtime = time(0);
	struct tm timeinfo;
	errno_t error = localtime_s(&timeinfo, &rawtime);

	stime = std::to_string(timeinfo.tm_year + 1900) + "-";

	if (timeinfo.tm_mon > 9)stime += std::to_string(timeinfo.tm_mon) + "-";
	else stime += "0" + std::to_string(timeinfo.tm_mon) + "-";

	if (timeinfo.tm_mday > 9)stime += std::to_string(timeinfo.tm_mday) + " | ";
	else stime += "0" + std::to_string(timeinfo.tm_mday) + " | ";

	if (timeinfo.tm_hour > 9)stime += std::to_string(timeinfo.tm_hour) + ":";
	else stime += "0" + std::to_string(timeinfo.tm_hour) + ":";

	if (timeinfo.tm_min > 9)stime += std::to_string(timeinfo.tm_min) + ":";
	else stime += "0" + std::to_string(timeinfo.tm_min) + ":";

	if (timeinfo.tm_sec > 9)stime += std::to_string(timeinfo.tm_sec);
	else stime += "0" + std::to_string(timeinfo.tm_sec);

	std::string sinfo;
	if (type == LOGLEVEL::DEBUG)sinfo = "[debug] ";
	if (type == LOGLEVEL::INFO)sinfo = "[info ] ";
	if (type == LOGLEVEL::WARNING)sinfo = "[warn ] ";
	if (type == LOGLEVEL::FATAL)sinfo = "[error] ";
	std::string i = sinfo + stime + " - " + info + "\n";

	std::cout << i;
	logs += i;

	if (callback != nullptr)callback(i);
}

std::string PrettyString::str() {
	std::string returnValue;
	for each (auto var in values)
	{
		returnValue += var.first + " ";
	}
	return returnValue;
}

std::string PrettyString::formatted(std::string message) {

	unsigned int objectCounter = 0;
	std::string formattedMessage;

	for (int i = 0; i < message.size(); i++) {
		if (message[i] == '{') {

			if (i + 1 < message.size() && message[i + 1] == '}') {
				formattedMessage += getValueToInsert(objectCounter);
				objectCounter++;
				i++;
				continue;
			}
			if (i + 2 < message.size() && message[i + 2] == '}' &&  isdigit(message[i + 1])) {

				int objectPos = message[i + 1] - '0';
				formattedMessage += getValueToInsert(objectPos);
				i += 2;
				continue;
			}

		}
		formattedMessage += message[i];
	}

	for each (auto var in values)
	{
		if (!var.second) formattedMessage += " " + var.first;
	}

	return formattedMessage;
}
