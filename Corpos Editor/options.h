#ifndef OPTIONS_H
#define OPTIONS_H
#include <iostream>
#include <fstream>
#include <string>

struct Options
{
	static std::string textureLocation;
	static std::string spriteLocation;
	static std::string editorExeLocation;
	static std::string gameExeLocation;
	static std::string tilesetLocation;
	static void loadIniFile();
	static void saveIniFile();
	static void reloadOptions();
};

#endif