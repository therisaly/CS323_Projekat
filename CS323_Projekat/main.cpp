#include "Game.h"
#include <iostream>

int main()
{
	{
		ComponentManager compMan;
		EntityManager entityMan(compMan);

		Game game(compMan, entityMan);

		game.Go();
	}

	std::cin.get();

	return 0;
}