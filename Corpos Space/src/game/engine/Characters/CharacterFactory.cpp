#include "CharacterFactory.hpp"

std::shared_ptr<Character> CharacterFactory::create(TextElement * data, EntityList * entityListPtr)
{
	std::string a = data->get("CharacterDefinition").toString(0);
	TextFileData file = a;
	if (!file.isEmpty())
	{
		auto characterdata = file.getFirstElementByName("ENTITY_DEFINITION");
		std::string type = characterdata->get("CharacterType").toString(0);
		if (type == "soldier")
		{
			auto character = std::shared_ptr<Character>(new  Soldier(&characterdata->mergeWith(*data), entityListPtr));
			return character;
		}
		if (type == "crawler")
		{
			auto character = std::shared_ptr<Character>(new  Crawler(&characterdata->mergeWith(*data), entityListPtr));
			return character;
		}
	}
	else return nullptr;
}