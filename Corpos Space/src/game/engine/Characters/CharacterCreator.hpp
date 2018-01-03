#ifndef CHARACTERCREATOR_HPP
#define CHARACTERCREATOR_HPP
#include "Soldier.hpp"
namespace CharacterCreator
{
	// Function returning shared ptr
	// Creates character from text element and assignt it tilemap pointer
	// TODO: add null pointer handling
	// TODO: add more character types

	std::shared_ptr <Character> create(TextElement * data, Tilemap * tilemap);

}

#endif
