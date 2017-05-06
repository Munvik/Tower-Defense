#include "pch.hpp"
#include "game.hpp"

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main()
{
	srand(unsigned int(time(NULL)));
	game Game;

	Game.run();

	return 0;
}