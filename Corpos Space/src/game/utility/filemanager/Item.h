
#ifndef FILEMANAGER_FILE_H
#define FILEMANAGER_FILE_H
#include <SFML/Graphics.hpp>


namespace FileManager {

	class Item {
	public:
		std::string name;
	
		Item(std::string name) : name(name) {}


		class Strings{
			public:
				std::string operator[](int id) { parent->variables[id]; };
				int size() { parent->variables.size(); }
			private:
				Item * parent;

		};

	private:
		std::vector<std::string> variables;
	};
}

#endif
