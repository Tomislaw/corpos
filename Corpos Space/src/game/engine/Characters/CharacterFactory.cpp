#include "CharacterFactory.hpp"

using namespace corpos;

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

std::shared_ptr<Character> CharacterFactory::create(json & data, EntityList * entityListPtr)
{
	auto type = data["characterType"].get("");
	auto characterData = json_utils::from_file(data["characterDefinition"].get(""));
	characterData.update(data);
	if (type == "soldier")
		return  std::shared_ptr<Character>(new  Soldier(characterData, entityListPtr));
	else if (type == "crawler")
		return std::shared_ptr<Character>(new  Crawler(characterData, entityListPtr));
	else
		return nullptr;
	//return std::shared_ptr<Character>();
}