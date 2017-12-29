#ifndef CHARACTERCREATOR_HPP
#define CHARACTERCREATOR_HPP
#include "Soldier.hpp"
namespace CharacterCreator
{

	std::shared_ptr <Character> create(TextElement * data, Tilemap * tilemap);

}

#endif
