#include "options.h"
#include "game\utility\Logger.hpp"
#include <windows.h>

std::string Options::gameExeLocation = "";
std::string Options::gameFolderLocation = "";
std::string Options::editorExeLocation = "";
std::string Options::textureLocation = "";
std::string Options::spriteLocation = "";
std::string Options::tilesetLocation = "";
void Options::loadIniFile()
{
	std::ifstream ini;
	ini.open(editorExeLocation + "corposeditor.ini");
	corpos::Logger::i("Opening \"" + editorExeLocation + "corposeditor.ini\"");
	std::string line;
	if (ini.good())
	{
		while (std::getline(ini, line))
		{
			int a = line.find("EXE_DIR=");
			if (a != -1)
			{
				line.erase(0, std::string("EXE_DIR=").size());
				gameExeLocation = line;
				break;
			}
		}
		if (gameExeLocation == "") corpos::Logger::i("EXE_DIR in ini file not found");
		else;
		ini.close();
		corpos::Logger::i("Ini file loaded");
		reloadOptions();
	}
	else corpos::Logger::e("Can't load \"corposeditor.ini\"");
}

void Options::saveIniFile()
{
	std::ofstream ini;
	ini.open(editorExeLocation + "corposeditor.ini");
	if (ini.good())
	{
		ini << "EXE_DIR=" + Options::gameExeLocation << std::endl;
		corpos::Logger::i("Ini file saved");
		ini.flush();
		ini.close();
	}
	else corpos::Logger::e("Can't save ini file. Propably \"corposeditor.ini\" don't exist.");
}

void Options::reloadOptions()
{
	// parse exe location
	auto a = Options::gameExeLocation.find_last_of("\\");
	if (std::string::npos == a)a = 0;

	auto b = Options::gameExeLocation.find_last_of("/");
	if (std::string::npos == b)b = 0;

	if (b > a)a = b;
	std::string loc = Options::gameExeLocation;

	loc.erase(a, loc.size() - a);
	//loc += "\\";
	//
	std::ifstream ini;

	Options::gameFolderLocation = loc;

	ini.open(loc + "\\bin\\graphics\\textures\\texture_definition.txt");
	if (ini.good())
	{
		corpos::Logger::i("\"" + loc + "\\bin\\graphics\\textures\\texture_definition.txt\" found");
		Options::textureLocation = loc + "\\bin\\graphics\\textures\\texture_definition.txt";
		ini.close();
	}
	else
	{
		corpos::Logger::e("\"" + loc + "\\bin\\graphics\\textures\\texture_definition.txt\" not found");
	}

	ini.open(loc + "\\bin\\graphics\\sprite\\sprite_definitions.txt");
	if (ini.good())
	{
		corpos::Logger::i("\"" + loc + "\\bin\\graphics\\sprite\\sprite_definitions.txt\" found");
		Options::spriteLocation = loc + "\\bin\\graphics\\sprite\\sprite_definitions.txt";
		ini.close();
	}
	else
	{
		corpos::Logger::e("\"" + loc + "\\bin\\graphics\\sprite\\sprite_definitions.txt\" not found");
	}

	ini.open(loc + "\\bin\\graphics\\tileset\\tileset1.txt");
	if (ini.good())
	{
		corpos::Logger::i("\"" + loc + "\\bin\\graphics\\tileset\\tileset1.txt\" found");
		Options::tilesetLocation = loc + "\\bin\\graphics\\tileset\\tileset1.txt";
		ini.close();
	}
	else
	{
		corpos::Logger::e("\"" + loc + "\\bin\\graphics\\tileset\\tileset1.txt\" not found");
	}
}