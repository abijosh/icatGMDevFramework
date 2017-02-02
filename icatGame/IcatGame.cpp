#include "IcatGame.h"


IcatGame::IcatGame()
{
	scenePtr = nullptr;
}

IcatGame::~IcatGame()
{
}



bool IcatGame::initializeWindow(int width, int height, const char* title)
{

	if (!glfwInit()){
		fprintf(stderr, "Failed to initialize glfw!!!");
		return false;
		
	}


	if (!displayManager.createDisplay(width, height, title)){
		fprintf(stderr, "Failed to create GLFW window!!!");
		glfwTerminate();
		return false;
	}
	
	displayManager.setCurrentContext();
	glewExperimental = true;
	glewInit();

	modelLoader.createBasicShader();

	renderer.setWindowPointer(displayManager.getWindowPointer());
	renderer.initializeCamera(width, height);

	glfwSetKeyCallback(displayManager.getWindowPointer(), UserInteraction::keyEvent);
	glfwSetMouseButtonCallback(displayManager.getWindowPointer(), UserInteraction::mouse_button_callback);
	//glfwSetWindowSizeCallback(displayManager.getWindowPointer(), IcatGame::windowCallBack);

	return true;
}

Entity* IcatGame::createEntity(const char* filename){
	return modelLoader.loadModel(filename); 
}

void IcatGame::updateWindow(){

	renderer.prepare();
	if (scenePtr)
		renderer.renderScene(scenePtr);
	renderer.postRender();
	displayManager.pollEvents();

	float currentTime = (float)glfwGetTime();
	deltaTime = currentTime - prevTime;
	prevTime = currentTime;
}

void IcatGame::terminate() {
	freeResources();
	glfwTerminate();
}

void IcatGame::freeResources() {
	modelLoader.freeMemory();
}