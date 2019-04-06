#ifndef TEXTFILEDATA_HPP
#define TEXTFILEDATA_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Shlwapi.h>
#include <algorithm>
#include "Logger.hpp"

class TextItem {
public:

	TextItem() {};
	TextItem(std::vector<std::string> items) : variables(items){};
	TextItem(std::string item) { addVariable(item); };
	TextItem(int item) { addVariable(std::to_string(item)); };
	TextItem(double item) { addVariable(std::to_string(item)); };
	template<typename T>
	TextItem(sf::Vector2<T> item) { addVariable(std::to_string(item.x)); addVariable(std::to_string(item.y)); };
	template<typename T>
	TextItem(sf::Rect<T> item) 
	{
		addVariable(std::to_string(item.left)); 
		addVariable(std::to_string(item.top)); 
		addVariable(std::to_string(item.width));
		addVariable(std::to_string(item.height));
	};

	static TextItem fromString(std::string buffer, std::string * name = nullptr);

	int size() { return variables.size(); }
	void addVariable(std::string variable);

	//Return all variables changed to int
	std::vector <int> toInt();
	//Return all variables changed to float
	std::vector <float> toFloat();
	std::vector <double> toDouble();
	std::vector <std::string> toString();
	template<typename T> std::vector <sf::Rect<T>> toRect();
	template<typename T> std::vector <sf::Vector2<T>> toVector();
	//Return variable changed to int, if not found return 0.
	int toInt(unsigned int index, int default = 0 );
	//Return variable changed to float, if not found return 0.
	float toFloat(unsigned int index, float default = 0);
	double toDouble(unsigned int index, double default = 0);
	std::string toString(unsigned int index, std::string default = "");
	template<typename T> sf::Rect<T> toRect(unsigned int index);
	template<typename T> sf::Vector2<T> toVector(unsigned int index);
	template<typename T> sf::Rect<T> toRect(unsigned int index, sf::Rect<T> default);
	template<typename T> sf::Vector2<T> toVector(unsigned int index, sf::Vector2<T> default);
	bool isEmpty() { return variables.size() <= 0; };

	friend TextItem operator+(TextItem & lhs, const TextItem& rhs);
	friend TextItem operator+(TextItem & lhs, const std::string& rhs);
	friend TextItem& operator+=(TextItem & lhs, const TextItem& rhs) {return lhs+rhs;}

	std::string name;
	std::string element;
	std::string file;

private:
	std::vector <std::string> variables;
};

/// <summary>
/// Contains one region with variables.
/// </summary>
class TextElement : public Loggable
{
public:
	TextElement();
	~TextElement();

	std::string name;
	std::string file;
	std::string toString() override;

	TextItem& operator[](std::string variableName);
	TextItem& getItem(std::string variableName);

	int size() { return variables.size(); }

	friend TextElement operator+(TextElement & lhs, const TextElement& rhs);
	friend TextElement& operator+=(TextElement & lhs, const TextElement& rhs) { return lhs + rhs; };

	TextElement & mergeWith(TextElement & element);

private:
	std::map <std::string, TextItem> variables;
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
	std::string toString();

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

template<typename T>
inline std::vector<sf::Rect<T>> TextItem::toRect()
{
	if (variables.size() < 4)
	{
		Logger::w("Item '{}' in element '{}' in file '{}' dont have enought variables to convert to Rectangle.", 
			"", "", "");
		return std::vector<sf::Rect<T>>();
	}else if (!std::is_integral<T>::value && !std::is_floating_point<T>::value && !std::is_same<T,std::string>::value)
	{
		std::any any = T();
		Logger::w("Item '{}' in element '{}' in file '{}' can not be converted to Rectangle. Class '{}' is not supported.",
			"", "", "", typeid(T).name());
		return std::vector<sf::Rect<T>>();
	}

	auto returnValue = std::vector<sf::Rect<T>>();
	for (int i = 0; i < variables.size() / 4; i++) 
	{
		returnValue.push_back(toRect<T>(i));
	}
	return returnValue;
};

template<typename T>
inline std::vector<sf::Vector2<T>> TextItem::toVector()
{
	if (variables.size() < 2)
	{
		Logger::w("Item '{}' in element '{}' in file '{}' dont have enought variables to convert to Vector.",
			name, "", "");
		return std::vector<sf::Vector2<T>>();
	}
	else if (!std::is_integral(T) && !std::is_floating_point(t) && !std::is_same(T, std::string))
	{
		std::any any = T();
		Logger::w("Item '{}' in element '{}' in file '{}' can not be converted to Rectangle. Class '{}' is not supported.",
			name, "", "", typeid(T).name());
		return std::vector<sf::Vector2<T>>();
	}

	auto returnValue = std::vector<sf::Vector2<T>>();

	for (int i = 0; i < variables.size() / 2; i++)
		returnValue.push_back(toVector<T>(i));

	return returnValue;
};

template<typename T>
inline sf::Rect<T> TextItem::toRect(unsigned int index)
{
	return toRect(index, sf::Rect<T>());
}

template<typename T>
inline sf::Vector2<T> TextItem::toVector(unsigned int index)
{
	return toVector(index, sf::Vector2<T>());
}

template<typename T>
inline sf::Rect<T> TextItem::toRect(unsigned int index, sf::Rect<T> default)
{
	if (variables.size() < index + 4)
	{
		Logger::w("Item '{}' in element '{}' in file '{}' dont have enought variables to convert to Rectangle.",
			name,element, file);
		return default;
	}

	if (std::is_integral<T>::value) return sf::Rect<T>(toInt(index * 4), toInt(index * 4+1), toInt(index * 4+2), toInt(index * 4+3));
	else if (std::is_floating_point<T>::value)	return sf::Rect<T>(toFloat(index * 4), toFloat(index * 4 + 1), toFloat(index * 4 + 2), toFloat(index * 4 + 3));
	else
	{
		Logger::e("Item '{}' in element '{}' in file '{}' can not be converted to Rectangle. Class '{}' is not supported.",
			name, element, file, typeid(T).name());
		throw std::exception("Runtime exception, incorrect class type.");
	}
};

template<typename T>
inline sf::Vector2<T> TextItem::toVector(unsigned int index, sf::Vector2<T> default)
{
	if (variables.size() < index + 2)
	{
		Logger::w("Item '{}' in element '{}' in file '{}' dont have enought variables to convert to Vector.", 
			name, element, file);
		return default;
	}
	if (std::is_integral<T>::value) return sf::Vector2<T>(toInt(index * 2), toInt(index * 2 + 1));
	else if (std::is_floating_point<T>::value) return sf::Vector2<T>(toFloat(index * 2), toFloat(index * 2 + 1));
	else
	{
		Logger::e("Item '{}' in element '{}' in file '{}' can not be converted to Rectangle. Class '{}' is not supported.",
			name, element, file, typeid(T).name());
		throw std::exception("Runtime exception, incorrect class type.");
	}
};


#endif