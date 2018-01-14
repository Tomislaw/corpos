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
	//True if empty.
	bool isNull()
	{
		if (var.size() <= 0)return 1;
		return 0;
	}
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
	Variable null;
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

private:
	std::string name;
	std::vector < TextElement > element;

	bool endOfFile = false;

	//Empty variable
	TextElement null;

	//Get location of executable
	std::string getExeLocation();

	bool loadTextElement(std::fstream &file);
};

#endif