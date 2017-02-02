
#include "Header.h"


ModelLoader::ModelLoader()
{
}

ModelLoader::~ModelLoader()
{
}

Entity* ModelLoader::loadModel(const char* fileName){
	int width, height;
	Entity* retVal = nullptr;
	int textureID = bufferLoader.loadTexture(fileName, &width, &height);
	if (textureID >= 0) {
		TexturedModel* texturedQuad = createTexturedQuad((float)width, (float)height, new Material(textureID, ShaderPtr));

		retVal = new(getAllignedSpace(sizeof(Entity), 16)) Entity(texturedQuad, glm::vec3(0.0f), glm::vec3(1.0f));

		Entitys.push_back(retVal);
	}
	return retVal;
}


void* ModelLoader::getAllignedSpace(size_t objectSize, size_t alignment) {
	return(_aligned_malloc(objectSize, alignment));
}

void ModelLoader::deallocAlignedMemory(void* ptr) {
	_aligned_free(ptr);
}

void ModelLoader::createBasicShader() {
	ShaderPtr = new Shader();
	ShaderPtr->createShader("./Shaders/vs.mvp.glsl", "./Shaders/fs.mvp.glsl");
}

TexturedModel* ModelLoader::createTexturedQuad(float width, float height, Material* MaterialPtr) {

	std::vector<float> positions;
	std::vector<float> uv;
	std::vector<int> indices;

	//left top triangle
	positions.push_back(0);
	positions.push_back(0);
	positions.push_back(0);
	
	uv.push_back(0);
	uv.push_back(1);

	positions.push_back(0);
	positions.push_back(height);
	positions.push_back(0);
	
	uv.push_back(0);
	uv.push_back(0);

	positions.push_back(width);
	positions.push_back(height);
	positions.push_back(0);
	
	uv.push_back(1);
	uv.push_back(0);

	positions.push_back(width);
	positions.push_back(0);
	positions.push_back(0);
	
	uv.push_back(1);
	uv.push_back(1);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	RawModel* RawModelPtr = bufferLoader.loadToBuffer(positions, uv, indices);

	positions.clear();
	uv.clear();
	indices.clear();

	return new TexturedModel(RawModelPtr, MaterialPtr);
}

void ModelLoader::freeMemory() {
	delete ShaderPtr;
	bufferLoader.freeBuffer();
	for (Entity* e : Entitys) {
		e->~Entity();
		deallocAlignedMemory(e);
	}
}