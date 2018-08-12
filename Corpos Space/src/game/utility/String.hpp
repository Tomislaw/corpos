#ifndef STRING_HPP
#define STRING_HPP

#include <string>
#include <sstream>
#include <vector>
#include <iterator>
namespace String
{

	template<typename Out>
	void split(const std::string &s, char delim, Out result);

	std::vector<std::string> split(const std::string &s, char delim);
}

#endif