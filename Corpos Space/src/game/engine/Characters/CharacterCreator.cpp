#include "CharacterCreator.hpp"

std::shared_ptr<Character> CharacterCreator::create(TextElement * data, Tilemap * tilemap)
{
	std::string a = data->get_variable_by_name("CharacterDefinition")->var[0];
	TextFileData file;
	if (file.load_file(a))
	{
	auto characterdata = file.get_first_element_by_name("ENTITY_DEFINITION");
	std::string type = characterdata->get_variable_by_name("CharacterType")->var[0];
	if (type == "soldier")
	{
	auto character = std::shared_ptr<Character>(new  Soldier(data, tilemap));
	character->setCharacter(characterdata);
	return character;
	}
	}
	else return nullptr;

}
