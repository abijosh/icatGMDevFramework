



#include "IcatGame.h"

IcatGame icatGame;

void createScene()
{

	Scene *scene = new Scene();
	scene->addEntity(icatGame.createEntity("./assets/IcatIM.png"));
	icatGame.setScenePtr(scene);

	/*
	
		retVal = modelLoader.loadModel(filename);

		std::vector<glm::vec3> vertices = retVal->getModelPointer()->getRawModel()->getVertices();
		b2Vec2* b2Vertices = getB2Vertices(vertices);

		b2BodyDef definition;
		definition.type = b2_dynamicBody;
		definition.position.Set(b2Vertices[0].x, b2Vertices[0].y);
		definition.angle = 0.0f;

		b2Body* dynamicBody = physicsWorld->CreateBody(&definition);

		b2PolygonShape shape;
		shape.Set(b2Vertices, vertices.size());
		
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1;

		dynamicBody->CreateFixture(&fixtureDef);

		retVal->setBox2DReferences(dynamicBody);
	*/
}


int main(){

	icatGame.initializeWindow();
	createScene();
	
	do{
				
		// update game(deltaTime);
		icatGame.updateWindow();

	} while (!icatGame.ifWindowShouldClose());

	glfwTerminate();
	return 0;
}
