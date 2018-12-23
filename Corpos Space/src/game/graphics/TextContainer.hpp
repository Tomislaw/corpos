#include "SFML\Graphics.hpp"
#include "windows.h"
#include "resource.h"

#ifndef TEXTCONTAINER_HPP
#define TEXTCONTAINER_HPP

// Class with all fonts, TODO: add localization handling here
class TextContainer
{
public:

protected:
	static TextContainer* instance;
	TextContainer();
	TextContainer(const TextContainer &);

public:
	~TextContainer();
	static TextContainer * TextContainer::getInstance();
	//int dothing() { basicFont.getInfo(); return 5; };
	sf::Font & getBasicFont();
private:
	sf::Font basicFont;
};
#endif