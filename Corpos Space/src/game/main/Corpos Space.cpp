// Corpos Space.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "game\main\Game.hpp"
#include "game\engine\Entity.hpp"

using namespace corpos;

int main(int argc, char * argv[])
{
	srand((unsigned)time(NULL));
	Game game(argc, argv);
	game.run();
	return 0;
}