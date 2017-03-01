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
	glm::vec3 position(0.0f, 74.0f, 0.0f);
	float offset = 4.0f;
	for (char c : levelData){
		switch (c)
		{
		case '0':
		case ' ':
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
			createPlayer(position);
			scene->addEntity(players[players.size()-1]);
			position.x += offset;
			break;
		case '4':
			position.x += offset;
			scene->addEntity(createEntryPortal(position));
			position.x += offset;
			break;
		case '5':
			position.x += offset;
			scene->addEntity(createExitPortal(position));
			position.x += offset;
			break;
		case '\n':
			position.x = 2.f;
			position.y -= offset;
			break;
		}
	}
	return scene;
}

PhysicsEntity *LevelLoader::createBrick(const glm::vec3& position){
	Entity* entity = icatGame->createEntity("./assets/environment/brick.png");
	entity->setPosition(position);
	b2Body *physicsBody = createPhysicsBody(position.x, position.y, 2.0f, 2.0f, b2_staticBody);
	return new PhysicsEntity(entity, physicsBody);
}
PhysicsEntity *LevelLoader::createPlatform(const glm::vec3& position){
	Entity* entity = icatGame->createEntity("./assets/environment/platform.png");
	b2Body *physicsBody = createPhysicsBody(position.x, position.y, 2.0f, 2.0f, b2_staticBody);
	entity->setPosition(position);
	return new PhysicsEntity(entity, physicsBody);
}
PhysicsEntity *LevelLoader::createEntryPortal(const glm::vec3& position){
	Entity* entity = icatGame->createEntity("./assets/environment/portal/portal.png");
	entity->setPosition(position);
	b2Body *physicsBody = createPhysicsBody(position.x, position.y, 4.0f, 2.0f, b2_staticBody);
	return new PhysicsEntity(entity, physicsBody);
}
PhysicsEntity *LevelLoader::createExitPortal(const glm::vec3& position){
	Entity* entity = icatGame->createEntity("./assets/environment/portal/fire.png");
	entity->setPosition(position);
	b2Body *physicsBody = createPhysicsBody(position.x, position.y, 4.0f, 2.0f, b2_staticBody);
	return new PhysicsEntity(entity, physicsBody);
}
void LevelLoader::createPlayer(const glm::vec3& position){
	Entity* entity = icatGame->createEntity("./assets/gamePlay/player/idle/01.png");
	b2Body *physicsBody = createPhysicsBody(position.x, position.y, 1.0f, 1.0f, b2_dynamicBody);
	entity->setPosition(position);
	players.push_back( new Player( new PhysicsEntity(entity, physicsBody)
		, createPistol(position)));
}

Weapon* LevelLoader::createPistol(const glm::vec3& position){
	Entity* entity = icatGame->createEntity("./assets/gamePlay/weapons/pistol.png");
	b2Body *physicsBody = createPhysicsBody(1.0f, 0.7f, 0.45f, 0.30f, b2_dynamicBody);
	entity->setPosition(1.0f, 0.7f, 0.0f);

	Entity* aEntity = icatGame->createEntity("./assets/gamePlay/ammo/bullet.png");
	aEntity->setPosition(0.50f, 0.0f, 0.0f);
	return new Weapon(new PhysicsEntity(entity, physicsBody),
		AmmoData(aEntity, 0.5f, 0.0f, 0.3f, 0.1f, b2_dynamicBody, b2Vec2(10, 0)));

}


b2Body* LevelLoader::createPhysicsBody(float x, float y, float halfWidth, float halfHeight, b2BodyType bodyType) {

	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position.Set(x, y);
	b2Body* physicsBody = currentWorldPtr->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(halfWidth, halfHeight);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;

	physicsBody->CreateFixture(&boxFixtureDef);

	return physicsBody;
}