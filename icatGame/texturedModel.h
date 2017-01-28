#pragma once
class TexturedModel
{
public:
	TexturedModel(RawModel* RawModelPtr, Material* MaterialPtr);
	~TexturedModel();

	RawModel* getRawModel();
	Material* getMaterial();

private:
	RawModel* mp_RawModel;
	Material* mp_Material;
};

