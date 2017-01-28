#include <vector>
#include "Shader.h"
#pragma once
class Material
{
public:
	Material(unsigned int textureID, Shader* ShaderPtr);
	~Material();

	unsigned int getTextureID() {return textureID; }
	Shader* getShaderPointer();

private:
	unsigned int textureID;
	Shader* ShaderPtr;
};

