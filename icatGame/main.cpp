



#include "IcatGame.h"

IcatGame icatGame;

void createScene()
{

	Scene *scene = new Scene();
	scene->addEntity(icatGame.createEntity("./assets/Icat.png"));
	icatGame.setScenePtr(scene);
}


int main(){

	if (icatGame.initializeWindow()) {
		createScene();

		do {

			// update game(deltaTime);
			icatGame.updateWindow();

		} while (!icatGame.ifWindowShouldClose());
		icatGame.terminate();
	}

	return 0;
}
