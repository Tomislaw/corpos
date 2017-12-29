#ifndef TEXTFILEDATA_HPP
#define TEXTFILEDATA_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Shlwapi.h>
#include <algorithm>
#include "game\utility\Logger.hpp"
/// <summary>
/// Contains single variable in table.
/// </summary>
struct Variable
{
	std::string name = "NULL";
	std::vector <std::string> var;
	//Return all variables changed to int
	std::vector <int> to_int();
	//REturn all variables changed to float
	std::vector <float> to_float();
	std::vector <std::string> to_string();
	//Return variable changed to int, if not found return 0.
	int to_int(unsigned int index);
	//Return variable changed to float, if not found return 0.
	float to_float(unsigned int index);
	std::string to_string(unsigned int index);
	//True if empty.
	bool is_null()
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

	Variable *get_variable_by_name(std::string var_name);
	std::vector<Variable *> get_aLL_variables_by_name(std::string var_name);

private:

};





/// <summary>
/// Loading data from file.
/// </summary>
class TextFileData
{
public:
	TextFileData();
	~TextFileData();



	//getters
	std::vector <TextElement*> get_all_elements_by_name(std::string element_name);
	TextElement *get_first_element_by_name(std::string element_name);
	std::vector < TextElement > get_all_elements();
	std::string display();

	// setters
	void set_elements(std::vector < TextElement > set);
	void replace_element(TextElement replace, std::string id);

	// load & save
	bool save_to_file(std::string localization);
	bool load_file(std::string file_txt);

private:
	std::string name;
	std::vector < TextElement > element;

	//Empty variable
	TextElement null;

	//Get location of executable
	std::string getExeLocation();
};

#endif