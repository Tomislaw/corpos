#include "game\utility\TextFileData.hpp"

std::vector <int> Variable::toInt()
{
	std::vector <int> table;
	for (int i = 0; i < var.size();i++)
	{
		table.push_back(atoi(var[i].c_str()));
	}
	return table;
}

std::vector <float> Variable::toFloat()
{
	std::vector <float> table;
	for (int i = 0; i < var.size();i++)
	{
		table.push_back(atoi(var[i].c_str()));
	}
	return table;
}

int Variable::toInt(unsigned int index)
{
	if (index < var.size())
	{
		return atoi(var[index].c_str());
	}
	return 0;
}

float Variable::toFloat(unsigned int index)
{
	if (index < var.size())
	{
		return atof(var[index].c_str());
	}
	return 0;
}

std::string Variable::toString(unsigned int id)
{
	if (id < var.size())
	{
		return var[id];
	}
	return std::string();
}


Variable set_variable(std::string variable_line)
{
	char cudzyslow = 34;
	char przecinek = ',';
	if (variable_line.size() < 7 || variable_line.find(" = ") == std::string::npos || variable_line.find(cudzyslow) == std::string::npos)
	{
		Variable var;
		var.name == "ERROR";
		var.var.push_back("ERROR");
		Logger::e("Wrong variable -> " + variable_line);
		return var;
	}
	else
	{
		Variable var1;
		std::string name = variable_line;
		name.erase(variable_line.find(" = "), name.size());
		var1.name = name;
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
		for (int i = 0; i < variable_all.size();i++)
		{
			variable_char = variable_all[i];
			if (variable_char == przecinek)
			{
				var1.var.push_back(variable_value);
				variable_value.clear();
			}
			else
			{
				if (variable_char == cudzyslow)
				{
					var1.var.push_back(variable_value);
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

////////////////////////////////////TEXTELEMENT

TextElement::TextElement()
{
	name == "Empty element";
}

TextElement::~TextElement()
{

}

std::string TextElement::display()
{
	std::string displaytext;
	displaytext += "Name " + name + "\n";
	for (int i = 0; i < variable.size();i++)
	{
		displaytext += variable[i].name + " ";
		for (int j = 0; j < variable[i].var.size();j++)
		{
			displaytext += variable[i].var[j] + " ";
		}
		displaytext += '\n';
	}
	displaytext += '\n';
	return displaytext;
}
Variable *TextElement::getVariableByName(std::string var_name)
{
	for (int i = 0; i < variable.size();i++)
	{
		if (variable[i].name == var_name) return &variable[i];
	}

	Logger::d("In " + name + ", variable " + var_name + " not found");
	return nullptr;
}

std::vector<Variable*> TextElement::getAllVariablesByName(std::string var_name)
{
	std::vector<Variable*> vars;
	for (int i = 0; i < variable.size();i++)
	{
		if (variable[i].name == var_name) vars.push_back(&variable[i]);
	}
	if (vars.size()==0)Logger::d("In " + name + ", variable " + var_name + " not found");
	
	return vars;
}


////////////////////////////////TEXTFILEDATA


TextFileData::TextFileData()
{
}

TextFileData::TextFileData(std::vector<TextElement> &elements)
{
	setElements(elements);
}

TextFileData::~TextFileData()
{
}

//getters

std::vector<TextElement*> TextFileData::getAllElementsByName(std::string element_name)
{
	std::vector <TextElement*> all_elements;
	for (int i = 0; i < element.size();i++)
	{
		if (element[i].name == element_name) all_elements.push_back(&element[i]);
	}
	return all_elements;
}

TextElement * TextFileData::getFirstElementByName(std::string element_name)
{
	for (int i = 0; i < element.size();i++)
	{
		if (element[i].name == element_name) return &element[i];
	}

	return nullptr;
}

std::vector<TextElement> TextFileData::getAllElements()
{
	return element;
}

std::string TextFileData::display()
{
	std::string displaytext;
	displaytext += "File name " + name + "\n";
	for (int i = 0; i < element.size();i++)
	{
		displaytext += element[i].display();
	}
	return displaytext;
}

// setters

void TextFileData::setElements(std::vector<TextElement> set)
{
	element = set;
}

void TextFileData::replaceElement(TextElement replace, std::string id)
{
	for (int i = 0; i < element.size(); i++)
	{
		if (element[i].name == id)
		{
			element[i] = replace;
			break;
		}
	}


}

// load & save

bool TextFileData::saveToFile(std::string localization)
{

	std::fstream file(localization, std::ios::out);
	if (file.good())
	{

		std::string text_data;

		text_data += "CORPOSFILE\r\n";
		for (int i = 0; i < element.size(); i++)
		{
			text_data += element[i].name + "\r\n";
			text_data += "{\r\n";
			for (int j = 0; j < element[i].variable.size(); j++)
			{
				text_data += element[i].variable[j].name + " = " + '"';
				for (int k = 0; k < element[i].variable[j].var.size() - 1; k++)
				{
					text_data += element[i].variable[j].var[k] + ',';
				}
				if (element[i].variable[j].var.size() > 0)
				{
					text_data += element[i].variable[j].var[element[i].variable[j].var.size() - 1] + '"' + "\n";
				}

			}
			text_data += "}\r\n";
		}
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



/*bool TextFileData::loadFile(std::string file_txt)
{
	//std::string file_txt = getExeLocation();
	//if (location.size() == 0)return false;
	//if (location[0] != '/')file_txt.push_back('/');
	//file_txt += location;


	std::fstream plik;
	plik.open(file_txt);
	if (!plik.good())
	{
		Logger::e("Can't open file " + file_txt);
		return false; //Nie uda³o siê otworzyæ pliku
	}


	std::string sWiersz;
	while (!plik.eof())
	{
		std::getline(plik, sWiersz);
		//	std::cout << sWiersz << std::endl; // Nazwa typu pliku
		
		if (sWiersz.find("CORPOSFILE") == std::string::npos) { plik.close(); return 0; }
		name = file_txt;

		bool startNextTextElement = true;


		while (sWiersz != "CORPOSFILE_END")
		{
			/////////Wczytywanie danych do struktury

			if(startNextTextElement==true)
			{ 
				std::getline(plik, sWiersz,'{');
				if (sWiersz.size() == 0)
				{
	
					if (sWiersz.find("CORPOSFILE_END") != std::string::npos){ plik.close(); return 0; }

				}

			}
			if (sWiersz == "CORPOSFILE_END")return 1;
			if (sWiersz.size() > 1)
			{
				TextElement txtelement;
				txtelement.name = sWiersz;
				//	std::cout << sWiersz << std::endl;
				std::getline(plik, sWiersz);
				if (sWiersz != "{") return 0;
				for (int i = 0; i < 2000; i++)
				{

					std::getline(plik, sWiersz);
					if (sWiersz == "}") break;
					if (sWiersz == "{") return 0;
					txtelement.variable.push_back(set_variable(sWiersz));

				}
				element.push_back(txtelement);
			}
		}
	}
	plik.close();
	return true;
}*/

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
		return false; //Nie uda³o siê otworzyæ pliku
	}


	std::string buffor;
	while (!file.eof())
	{
		std::getline(file, buffor);
		//	std::cout << sWiersz << std::endl; // Nazwa typu pliku

		if (buffor.find("CORPOSFILE") == std::string::npos) { file.close(); return 0; }
		name = file_txt;


		while (!endOfFile)
		{
			/////////Wczytywanie danych do struktury

				if(loadTextElement(file)==false)
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
	std::getline(file, buffor,'{');

	if (buffor.find("CORPOSFILE_END") != std::string::npos)
	{
		endOfFile = true;
		return true;
	}

	if (buffor.size() > 1)
	{
		buffor.erase(remove(buffor.begin(), buffor.end(), '\n'), buffor.end());
		buffor.erase(remove(buffor.begin(), buffor.end(), '\r'), buffor.end());
		TextElement e;
		e.name = buffor;
		while (buffor.find('}') == std::string::npos)
		{
			std::getline(file, buffor);
			if (file.eof())
			{
				Logger::e("Missing bracket \"}\"");
				return false;
			}
			if(buffor.size() > 7)e.variable.push_back(set_variable(buffor));
		}
		this->element.push_back(e);
		return true;
	}
	else
	{
		for (int i = 0; i < 1000; i++)
		{
	
			std::getline(file, buffor);
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

