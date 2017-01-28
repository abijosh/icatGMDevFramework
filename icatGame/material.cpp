#include "Header.h"


Material::Material(unsigned int textureID, Shader* ShaderPtr)
	: textureID(textureID)
    , ShaderPtr(ShaderPtr)
{
}

Material::~Material()
{
}

Shader* Material::getShaderPointer(){
	return ShaderPtr;
}
