#pragma once
#include <vector>
#include <iosfwd>
#include <string>

#include "RawModel.h"
#include "Shader.h"
#include "Material.h"
#include "TexturedModel.h"
#include "BufferLoader.h"

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	Entity* loadModel(const char* filename);
	Entity* loadAnimatedModel(const char* filename, unsigned int count, float maxDuration);

    void createBasicShader();
	void freeMemory();
private:
	void* getAllignedSpace(size_t objectSize, size_t alignment);
	void deallocAlignedMemory(void* ptr);
	TexturedModel* createTexturedQuad(float width, float height, Material* MaterialPtr);
	Material* createAnimatedMaterial(const char* filename, unsigned int count, float maxDuration);
	
private:
	BufferLoader bufferLoader;
    Shader* ShaderPtr;
	std::vector<Entity*> Entitys;
};

