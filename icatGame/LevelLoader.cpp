#include "LevelLoader.h"


LevelLoader::LevelLoader(IcatGame* icatGame)
{
	this->icatGame = icatGame;
}


LevelLoader::~LevelLoader()
{
}

Scene* LevelLoader::load(int levelNum, b2World* worldPtr){
	currentWorldPtr = worldPtr;
	std::string levelData = readLevelData(levelNum);
	if (levelData != "")
		return createScene(levelData);
	else
		return nullptr;
}

std::string LevelLoader::readLevelData(int levelNum){
	std::stringstream padedLevelNumStr;
	padedLevelNumStr << std::setw(3) << std::setfill('0') << levelNum;
	std::string fileLocation = "./assets/levelDetails/" + padedLevelNumStr.str() + ".txt";

	std::string levelDataStr;
	std::ifstream levelDataStream(fileLocation, std::ios::in);
	if (levelDataStream.is_open()){
		std::string line = "";
		while (getline(levelDataStream, line))
			levelDataStr += "\n" + line;
		levelDataStream.close();
		return levelDataStr;
	}
	else {
		printf("Impossible to open %s. Are you in the right directory?\n", &fileLocation[0]);
		getchar();
		return "";
	}
}

Scene* LevelLoader::createScene(std::string levelData){
	Scene *scene = new Scene();
	glm::vec3 position(0, 720, 0);
	float offset = 40;
	for (char c : levelData){
		switch (c)
		{
		case '0':
			position.x += offset;
			break;
		case '1':
			scene->addEntity(createPlatform(position));
			position.x += offset;
			break;
		case '2':
			scene->addEntity(createBrick(position));
			position.x += offset;
			break;
		case '3':
			scene->addEntity(createPlayer(position));
			position.x += offset;
			break;
		case '\n':
			position.x = 0;
			position.y -= offset;
			break;
		}
	}
	return scene;
}

PhysicsEntity *LevelLoader::createBrick(const glm::vec3& position){
	Entity* entity = icatGame->createEntity("./assets/environment/brick.png");
	entity->setPosition(position);
	b2Body *physicsBody = createPhysicsBody(position.x, position.y, b2_staticBody);
	return new PhysicsEntity(entity, physicsBody);
}
PhysicsEntity *LevelLoader::createPlatform(const glm::vec3& position){
	Entity* entity = icatGame->createEntity("./assets/environment/platform.png");
	b2Body *physicsBody = createPhysicsBody(position.x, position.y, b2_dynamicBody);
	entity->setPosition(position);
	return new PhysicsEntity(entity, physicsBody);
}
PhysicsEntity *LevelLoader::createPlayer(const glm::vec3& position){
	Entity* entity = icatGame->createEntity("./assets/gamePlay/player/idle/01.png");
	b2Body *physicsBody = createPhysicsBody(position.x, position.y, b2_dynamicBody);
	entity->setPosition(position);
	return new PhysicsEntity(entity, physicsBody);
}


b2Body* LevelLoader::createPhysicsBody(float x, float y, b2BodyType bodyType) {

	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position.Set(x, y);
	b2Body* physicsBody = currentWorldPtr->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(20.0f, 20.0f);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;

	physicsBody->CreateFixture(&boxFixtureDef);

	return physicsBody;
}