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
			scene->addDynamicEntity(player);
			position.x += offset;
			break;
		case '4':
			position.x += offset * 0.5f;
			createEntryPortal(position, scene);
			scene->addDynamicEntity(entryPortal);
			position.x += offset * 0.5f;
			break;
		case '5':
			position.x += offset * 0.5f;
			createExitPortal(position, scene);
			scene->addDynamicEntity(exitPortal);
			position.x += offset * 0.5f;
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
	entity->setType(Entity::WALL);
	entity->setPosition(position);
	b2Body *physicsBody = physicsBodyCreator(position.x, position.y, 2.0f, 2.0f, b2_staticBody, currentWorldPtr, true);
	return new PhysicsEntity(entity, physicsBody);
}
PhysicsEntity *LevelLoader::createPlatform(const glm::vec3& position){
	Entity* entity = icatGame->createEntity("./assets/environment/platform.png");
	entity->setType(Entity::PLATFORM);
	entity->setPosition(position);
	b2Body *physicsBody = physicsBodyCreator(position.x, position.y, 2.0f, 2.0f, b2_staticBody, currentWorldPtr, true);
	return new PhysicsEntity(entity, physicsBody);
}
void LevelLoader::createEntryPortal(const glm::vec3& position, Scene *scene){
	Entity* entity = icatGame->createEntity("./assets/environment/portal/portal.png");
	entity->setType(Entity::PORTAL);
	entity->setPosition(position);
	b2Body *physicsBody = physicsBodyCreator(position.x, position.y + 4.0f, 4.0f, 2.0f, b2_staticBody, currentWorldPtr, true);

	entryPortal = new EntryPortal(new PhysicsEntity(entity, physicsBody), 0.3f, 0.8f, getEnemyData(), scene, currentWorldPtr);
}

EnemyData* LevelLoader::getEnemyData(){
	Entity* entity = icatGame->createEntity("./assets/gamePlay/enemy/smallEnemy/1.png");
	EnemyData* enemyData = new EnemyData(entity, 0.9f, 0.8f, 10, 2, b2Vec2(20,0));
	return enemyData;
}
void LevelLoader::createExitPortal(const glm::vec3& position, Scene *scene){
	Entity* entity = icatGame->createEntity("./assets/environment/portal/fire.png");
	entity->setType(Entity::PORTAL);
	entity->setPosition(position);
	b2Body *physicsBody = physicsBodyCreator(position.x, position.y - 4.0f, 4.0f, 2.0f, b2_staticBody, currentWorldPtr, true);
	exitPortal = new ExitPortal(new PhysicsEntity(entity, physicsBody), entryPortal);
}
void LevelLoader::createPlayer(const glm::vec3& position){
	Entity* entity = icatGame->createEntity("./assets/gamePlay/player/idle/01.png");
	entity->setType(Entity::PLAYER);
	b2Body *physicsBody = physicsBodyCreator(position.x, position.y, 1.0f, 1.0f, b2_dynamicBody, currentWorldPtr, true);
	entity->setPosition(position);
	player = new Player( new PhysicsEntity(entity, physicsBody)	, createPistol(position));
}

Weapon* LevelLoader::createPistol(const glm::vec3& position){
	Entity* entity = icatGame->createEntity("./assets/gamePlay/weapons/pistol.png");
	b2Body *physicsBody = physicsBodyCreator(1.0f, 0.7f, 0.45f, 0.3f, b2_dynamicBody, currentWorldPtr, true);
	entity->setPosition(1.0f, 0.7f, 0.0f);
	entity->setType(Entity::WEAPON);

	Entity* aEntity = icatGame->createEntity("./assets/gamePlay/ammo/bullet.png");
	entity->setType(Entity::BULLET);
	aEntity->setPosition(0.50f, 0.0f, 0.0f);
	return new Weapon(new PhysicsEntity(entity, physicsBody),
		AmmoData(aEntity, 0.5f, 0.0f, 0.3f, 0.1f, 5.0f, 3.0f, b2_dynamicBody, b2Vec2(10, 0)));

}