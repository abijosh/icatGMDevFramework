



#include "IcatGame.h"
#include "Game.h"

IcatGame icatGame;
Game game(&icatGame);

void initGame(){
	game.initLevel(1);
}

int main(){
	if (icatGame.initializeWindow(1280, 720)) {
		initGame();
		do {
			// update game(deltaTime);
			icatGame.updateWindow();

		} while (!icatGame.ifWindowShouldClose());
		icatGame.terminate();
	}

	return 0;
}
