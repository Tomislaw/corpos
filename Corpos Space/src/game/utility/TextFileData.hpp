#ifndef TEXTFILEDATA_HPP
#define TEXTFILEDATA_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Shlwapi.h>
#include <algorithm>
#include "Logger.hpp"
/// <summary>
/// Contains single variable in table.
/// </summary>
struct Variable
{
	std::string name = "NULL";
	std::vector <std::string> var;
	//Return all variables changed to int
	std::vector <int> toInt();
	//Return all variables changed to float
	std::vector <float> toFloat();
	std::vector <std::string> toString();
	//Return variable changed to int, if not found return 0.
	int toInt(unsigned int index);
	//Return variable changed to float, if not found return 0.
	float toFloat(unsigned int index);
	std::string toString(unsigned int index);
};

/// <summary>
/// Contains one region with variables.
/// </summary>
class TextElement
{
public:
	TextElement();
	~TextElement();

	std::string name;
	std::vector <Variable > variable;
	std::string display();

	Variable *getVariableByName(std::string var_name);
	std::vector<Variable *> getAllVariablesByName(std::string var_name);

private:
};

/// <summary>
/// Loading data from file.
/// </summary>
class TextFileData
{
public:
	TextFileData();
	TextFileData(std::string fileLocation);
	TextFileData(std::vector<TextElement> &elements);
	~TextFileData();

	//getters
	std::vector <TextElement*> getAllElementsByName(std::string element_name);
	TextElement *getFirstElementByName(std::string element_name);
	std::vector < TextElement > getAllElements();
	std::string display();

	// setters
	void setElements(std::vector < TextElement > set);
	void replaceElement(TextElement replace, std::string id);

	// load & save
	bool saveToFile(std::string localization);
	bool loadFile(std::string file_txt);

	static std::istream& safeGetline(std::istream& is, std::string& t)
	{
		t.clear();

		// The characters in the stream are read one-by-one using a std::streambuf.
		// That is faster than reading them one-by-one using the std::istream.
		// Code that uses streambuf this way must be guarded by a sentry object.
		// The sentry object performs various tasks,
		// such as thread synchronization and updating the stream state.

		std::istream::sentry se(is, true);
		std::streambuf* sb = is.rdbuf();

		for (;;) {
			int c = sb->sbumpc();
			switch (c) {
			case '\n':
				return is;
			case '\r':
				if (sb->sgetc() == '\n')
					sb->sbumpc();
				return is;
			case std::streambuf::traits_type::eof():
				// Also handle the case when the last line has no line ending
				if (t.empty())
					is.setstate(std::ios::eofbit);
				return is;
			default:
				t += (char)c;
			}
		}
	}

private:
	std::string name;
	std::vector < TextElement > element;

	bool endOfFile = false;

	//Empty variable

	//Get location of executable
	std::string getExeLocation();

	bool loadTextElement(std::fstream &file);
};

#endif