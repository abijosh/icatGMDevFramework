#include "Header.h"

TexturedModel::TexturedModel(RawModel* RawModelPtr, Material* MaterialPtr)
{
	mp_RawModel = RawModelPtr;
	mp_Material = MaterialPtr;
}


TexturedModel::~TexturedModel()
{
	delete mp_RawModel;
	delete mp_Material;
}

RawModel* TexturedModel::getRawModel(){
	return mp_RawModel;
}

Material* TexturedModel::getMaterial(){
	return mp_Material;
}