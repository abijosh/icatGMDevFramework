#pragma once
class BufferLoader
{
public:
	BufferLoader();
	~BufferLoader();

	RawModel* loadToBuffer(std::vector<float> positions, std::vector<float> uv, std::vector<int> indices);
	unsigned int loadTexture(const char* filename, int *width, int *height);

private:
	unsigned int createVAO();
	void storeToVBO(std::vector<float> data, unsigned int length, unsigned int index);
	void storeElementsToVBO(std::vector<int> indices);
	void unbindVAO();

private:
	std::vector<int> vboList, vaoList, textureList;

};

