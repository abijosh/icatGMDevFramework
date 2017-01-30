#pragma once
#include "Header.h"
class IcatGame
{
public:
	IcatGame();
	~IcatGame();

	bool initializeWindow(int width = 1024, int height = 720, const char* title = "Icat IM OGL Wrapper Library");
	bool ifWindowShouldClose(){ return displayManager.isCloseRequested(); }
	void terminate() { glfwTerminate(); }

	Entity* createEntity(const char* filename);

	bool createPhysicsWorld(float gravity = -9.8f);
	PhysicsEntity* createPhysicsEntity(const char* filename, b2BodyDef bodyDefinition, b2FixtureDef bodyFixtureDef);

	void windowCallBack(GLFWwindow* window, int width, int height){
		renderer.setAspectRatio((float)width / (float)height);
	}
	
	float getDeltaTime(){ return deltaTime; }

	void setScenePtr(Scene* scenePtr)	{	this->scenePtr = scenePtr;	}
	void updateWindow();

private:
	float prevTime{ 0.0f }, deltaTime{ 0.0f };
	DisplayManager displayManager;
	ModelLoader modelLoader;
	Renderer renderer;
	UserInteraction oUserInteraciton;
	Scene *scenePtr;
	b2World* physicsWorld;
};

