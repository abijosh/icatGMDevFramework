#include "IcatGame.h"


IcatGame::IcatGame()
{
	physicsWorld = nullptr;
	scenePtr = nullptr;
}

IcatGame::~IcatGame()
{
}



void IcatGame::initializeWindow(int width, int height, const char* title)
{

	if (!glfwInit()){
		fprintf(stderr, "Failed to initialize glfw!!!");
		
	}


	if (!displayManager.createDisplay(width, height, title)){
		fprintf(stderr, "Failed to create GLFW window!!!");
		glfwTerminate();
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

	
}

Entity* IcatGame::createEntity(const char* filename){
	return modelLoader.loadModel(filename); 
}

bool IcatGame::createPhysicsWorld(float gravity){
	bool retVal = false;
	if (!physicsWorld){
		physicsWorld = new b2World(b2Vec2(0, gravity));
		retVal = true;
	}
	else
		std::cout << "Unable to create physics world or physics world already exists!!";
	return retVal;
}

PhysicsEntity* IcatGame::createPhysicsEntity(const char* filename, b2BodyDef bodyDefinition, b2FixtureDef bodyFixtureDef){
	PhysicsEntity* physicsEntity = nullptr;
	if (physicsWorld){
		Entity* entity = modelLoader.loadModel(filename);
		b2Body* physicsBody = physicsWorld->CreateBody(&bodyDefinition);
		physicsBody->CreateFixture(&bodyFixtureDef);
		physicsEntity = new PhysicsEntity(entity, physicsBody);
	}
	return physicsEntity;
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