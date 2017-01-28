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
    void createBasicShader();
private:
	TexturedModel* createTexturedQuad(float width, float height, Material* MaterialPtr);
	Material* createMaterial(const char* filename, unsigned int count, float maxDuration);
	
private:
	BufferLoader bufferLoader;
    Shader* ShaderPtr;
	std::vector<Entity*> Entitys;
};

