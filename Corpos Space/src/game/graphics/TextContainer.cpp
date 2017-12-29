#include "TextContainer.hpp"
#include "windows.h"
#include "resource.h"


TextContainer* TextContainer::instance = nullptr;



TextContainer::TextContainer()
{

	HRSRC resBlock = FindResource(NULL, MAKEINTRESOURCE(IDR_FONT1), RT_FONT);
	HGLOBAL myGlobal = LoadResource(NULL, resBlock);
	LPVOID firstByte = LockResource(myGlobal);
	DWORD resSize = SizeofResource(NULL, resBlock);
	basicFont.loadFromMemory(firstByte, resSize);
}

TextContainer::TextContainer(const TextContainer &)
{
	//this->basicFont = basicFont;

}

TextContainer::~TextContainer()
{
	delete instance;
}

TextContainer * TextContainer::getInstance()
{
	if (instance == nullptr)
	{
		instance = new TextContainer();
	}

	return instance;
}

sf::Font & TextContainer::getBasicFont()
{
	return basicFont;
}

/*sf::Font TextContainer::getBasicFont()
{
	return TextContainer::getInstance()->getBasicFont();
}*/
