#pragma once
#include "Header.h"
class IcatGame
{
public:
	IcatGame();
	~IcatGame();

	bool initializeWindow(int width = 1280, int height = 720, const char* title = "Icat IM OGL Wrapper Library");
	bool ifWindowShouldClose(){ return displayManager.isCloseRequested(); }
	void terminate();

	Entity* createEntity(const char* filename);

	void windowCallBack(GLFWwindow* window, int width, int height){
		renderer.setAspectRatio((float)width / (float)height);
	}
	
	float getDeltaTime(){ return deltaTime; }
	float getElapsedTime(){ return glfwGetTime(); }

	void setScenePtr(Scene* scenePtr)	{	this->scenePtr = scenePtr;	}
	void updateWindow();

private:
	void freeResources();

private:
	float prevTime{ 0.0f }, deltaTime{ 0.0f };
	DisplayManager displayManager;
	ModelLoader modelLoader;
	Renderer renderer;
	UserInteraction oUserInteraciton;
	Scene *scenePtr;
};

