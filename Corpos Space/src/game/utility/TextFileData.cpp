#include "game\utility\TextFileData.hpp"

class TextElement;
class TextFileData;
class TextItem;
////////////////////////////////////TEXTELEMENT

TextElement::TextElement()
{
	name == "Empty element";
}

TextElement::TextElement(std::string name)
{
	this->name = name;
}

TextElement::~TextElement()
{
}

std::string TextElement::toString()
{
	auto displaytext = "Name " + name + "\n{";

	for (auto item = variables.begin(); item != variables.end(); ++item) {
		displaytext += item->first + " = \"";
		for (int i = 0; i < item->second.size(); i++) {
			if (i != item->second.size() - 1)
				displaytext += item->second.toString(i) + "\"\n";
			else
				displaytext += item->second.toString(i) + ",";
		}
	}

	displaytext += '}\n';
	return displaytext;
}

TextItem & TextElement::operator[](std::string variableName)
{
	return get(variableName);
}

TextItem & TextElement::get(std::string variableName)
{
	TextItem & item = variables[variableName];
	item.parent = this;
	item.name = variableName;
	return item;
}

TextElement & TextElement::mergeWith(TextElement & element)
{
	for each (auto item in element.variables)
	{
		this->variables[item.first] = item.second;
	}
	return *this;
}

TextItem operator+(TextItem & lhs, const TextItem & rhs)
{
	for each (auto var in rhs.variables)
		lhs.addVariable(var);
	return lhs;
}

TextItem operator+(TextItem & lhs, const std::string & rhs)
{
	lhs.addVariable(rhs);
	return lhs;
}

TextElement operator+(TextElement & lhs, const TextElement & rhs)
{
	for each (auto item in rhs.variables)
	{
		lhs.variables[item.first] += item.second;
	}
	return lhs;
}

////////////////////////////////TEXTFILEDATA

TextFileData::TextFileData(std::string fileLocation) : filePath(fileLocation)
{
	loadFile(fileLocation);
}

TextFileData::TextFileData(std::vector<TextElement> &elements) : filePath()
{
	setElements(elements);
}

TextFileData::~TextFileData()
{
}

TextElement & TextFileData::operator[](std::string variableName)
{
	return getFirst(variableName);
}

TextElement & TextFileData::getFirst(std::string variableName)
{
	std::list<TextElement>::iterator it;
	for (it = element.begin(); it != element.end(); ++it)
		if (it->name == variableName) return *it;

	element.push_back(TextElement(variableName));
	element.back().parent = this;
	return element.back();
}

std::vector<TextElement*> TextFileData::get(std::string variableName)
{
	std::vector <TextElement*> allElements;
	std::list<TextElement>::iterator it;
	for (it = element.begin(); it != element.end(); ++it)
		if (it->name == variableName) allElements.push_back(&*it);

	return allElements;
}

//getters

std::vector<TextElement*> TextFileData::getAllElementsByName(std::string element_name)
{
	std::vector <TextElement*> all_elements;
	std::list<TextElement>::iterator it;
	for (it = element.begin(); it != element.end(); ++it)
		if (it->name == element_name)
		{
			TextElement & element = *it;
			all_elements.push_back(&element);
		}
	return all_elements;
}

TextElement * TextFileData::getFirstElementByName(std::string element_name)
{
	std::list<TextElement>::iterator it;
	for (it = element.begin(); it != element.end(); ++it)
		if (it->name == element_name)
		{
			TextElement & element = *it;
			return &element;
		}

	return nullptr;
}

std::vector<TextElement> TextFileData::getAllElements()
{
	std::vector <TextElement> all_elements;
	for (auto it = element.begin(); it != element.end(); ++it)
		all_elements.push_back(*it);

	return all_elements;
}

std::string TextFileData::toString()
{
	std::string displaytext;
	displaytext += "File name " + filePath + "\n";
	for (auto it = element.begin(); it != element.end(); ++it)
		displaytext += it->toString();
	return displaytext;
}

// setters

void TextFileData::setElements(std::vector<TextElement> set)
{
	element.clear();
	for each (auto var in set)
		element.push_back(var);
}

// load & save

bool TextFileData::saveToFile(std::string localization)
{
	std::fstream file(localization, std::ios::out);
	if (file.good())
	{
		std::string text_data;

		text_data += "CORPOSFILE\r\n";

		for (auto it = element.begin(); it != element.end(); ++it)
			text_data += it->toString();

		text_data += "CORPOSFILE_END";

		file << text_data;

		file.close();

		return true;
	}
	else
	{
		return false;
	}
}

bool TextFileData::loadFile(std::string file_txt)
{
	//std::string file_txt = getExeLocation();
	//if (location.size() == 0)return false;
	//if (location[0] != '/')file_txt.push_back('/');
	//file_txt += location;

	this->element.clear();
	this->endOfFile = false;

	std::fstream file;
	file.open(file_txt);
	if (!file.good())
	{
		Logger::e("Can't open file " + file_txt);
		return false;
	}

	std::string buffor;
	while (!file.eof())
	{
		safeGetline(file, buffor);

		if (buffor.find("CORPOSFILE") == std::string::npos) { file.close(); return 0; }

		while (!endOfFile)
		{
			if (loadTextElement(file) == false)
			{
				Logger::e("File \"" + file_txt + "\" not loaded!");
				return false;
			}
		}
	}
	file.close();
	return true;
}

//Get location of executable

std::string TextFileData::getExeLocation()
{
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(hModule, path, MAX_PATH);

	std::wstring wpath(path);
	std::replace(wpath.begin(), wpath.end(), '\\', '/');
	auto pos = wpath.find_last_of('/');
	wpath.erase(wpath.begin() + pos, wpath.end());

	// your new String
	return std::string(wpath.begin(), wpath.end());
}

bool TextFileData::loadTextElement(std::fstream &file)
{
	std::string buffor;
	std::getline(file, buffor, '{');

	if (buffor.find("CORPOSFILE_END") != std::string::npos)
	{
		endOfFile = true;
		return true;
	}

	if (buffor.size() > 1)
	{
		buffor.erase(remove(buffor.begin(), buffor.end(), '\n'), buffor.end());
		buffor.erase(remove(buffor.begin(), buffor.end(), '\r'), buffor.end());
		TextElement textElement = buffor;
		while (buffor.find('}') == std::string::npos)
		{
			safeGetline(file, buffor);
			if (file.eof())
			{
				Logger::e("Missing bracket \"}\"");
				return false;
			}
			if (buffor.size() > 7)
			{
				std::string name;
				textElement[name] += TextItem::fromString(buffor, &name);
			}
		}
		element.push_back(textElement);
		element.back().parent = this;
		return true;
	}
	else
	{
		for (int i = 0; i < 1000; i++)
		{
			safeGetline(file, buffor);
			if (buffor.find("CORPOSFILE_END") != std::string::npos)
			{
				endOfFile = true;
				return true;
			}
			if (file.eof() == true) break;
		}
	}
	Logger::e("Missing \"CORPOSFILE_END\"");
	return false;
}

;

TextItem TextItem::fromString(std::string variable_line, std::string * varName)
{
	char quotationMark = 34;
	char comma = ',';
	if (variable_line.size() < 7 || variable_line.find(" = ") == std::string::npos || variable_line.find(quotationMark) == std::string::npos)
	{
		TextItem var;
		Logger::w("Wrong variable -> " + variable_line);
		return var;
	}
	else
	{
		TextItem var1;

		std::string name = variable_line;
		name = name.erase(variable_line.find(" = "), name.size());

		if (varName != nullptr) varName->assign(name);

		std::string variable_all = variable_line;
		variable_all.erase(0, variable_line.find(" = ") + 4);
		int variable_count = 1;

		for (int i = 0; i < variable_all.size(); i++)
		{
			if (variable_all[i] == ',') variable_count += 1;
			if (variable_count > 999)
			{
				Logger::e("Variable " + name + "have too many args, max is 999");
				break;
			}
		}

		std::string variable_value;
		char variable_char;
		for (int i = 0; i < variable_all.size(); i++)
		{
			variable_char = variable_all[i];
			if (variable_char == comma)
			{
				var1.addVariable(variable_value);
				variable_value.clear();
			}
			else
			{
				if (variable_char == quotationMark)
				{
					var1.addVariable(variable_value);
					return var1;
				}
				else
				{
					variable_value += variable_char;
				}
			}
		}
		return var1;
	}
}

void TextItem::addVariable(std::string variable)
{
	variables.push_back(variable);
}

std::vector<int> TextItem::toInt()
{
	std::vector <int> table;
	for (int i = 0; i < variables.size(); i++)
	{
		table.push_back(atoi(variables[i].c_str()));
	}
	return table;
}

std::vector<float> TextItem::toFloat()
{
	std::vector <float> table;
	for (int i = 0; i < variables.size(); i++)
	{
		table.push_back(atof(variables[i].c_str()));
	}
	return table;
}

std::vector<double> TextItem::toDouble()
{
	std::vector <double> table;
	for (int i = 0; i < variables.size(); i++)
	{
		table.push_back(atof(variables[i].c_str()));
	}
	return table;
}

std::vector<std::string> TextItem::toString()
{
	return std::vector<std::string>();
}

int TextItem::toInt(unsigned int index, int default)
{
	if (index < variables.size()) return atoi(variables[index].c_str());
	return default;
}

float TextItem::toFloat(unsigned int index, float default)
{
	if (index < variables.size()) return atof(variables[index].c_str());
	return default;
}

double TextItem::toDouble(unsigned int index, double default)
{
	if (index < variables.size()) return atof(variables[index].c_str());
	return default;
}

std::string TextItem::toString(unsigned int index, std::string default)
{
	if (index < variables.size()) return variables[index];
	return default;
}