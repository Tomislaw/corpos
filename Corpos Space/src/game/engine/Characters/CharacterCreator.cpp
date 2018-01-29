#include "CharacterCreator.hpp"

std::shared_ptr<Character> CharacterCreator::create(TextElement * data, EntityList * entityListPtr)
{
	std::string a = data->getVariableByName("CharacterDefinition")->var[0];
	TextFileData file;
	if (file.loadFile(a))
	{
		auto characterdata = file.getFirstElementByName("ENTITY_DEFINITION");
		std::string type = characterdata->getVariableByName("CharacterType")->var[0];
		if (type == "soldier")
		{
			auto character = std::shared_ptr<Character>(new  Soldier(data, entityListPtr));
			character->setCharacter(characterdata);
			return character;
		}
		if (type == "crawler")
		{
			auto character = std::shared_ptr<Character>(new  Crawler(data, entityListPtr));
			character->setCharacter(characterdata);
			return character;
		}
	}
	else return nullptr;

}
