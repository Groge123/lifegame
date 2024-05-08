#include "game.h"


int main()
{
	
	Game* game = new Game;
	while (1)
	{
		game->Line();
		game->MouseOp();
		game->BeginE();
		
	}
	system("pause");
}

