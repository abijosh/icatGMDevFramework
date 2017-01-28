#include "Header.h"

BufferLoader::BufferLoader()
{
}


BufferLoader::~BufferLoader()
{
	//need to delete buffers
}

RawModel* BufferLoader::loadToBuffer(std::vector<float> positions, std::vector<float> uv, std::vector<int> indices){
	unsigned int vaoID = createVAO();
	storeToVBO(positions, 3, 0);
	storeToVBO(uv, 2, 1);
	storeElementsToVBO(indices);
	unbindVAO();
	vaoList.push_back(vaoID);
	return new RawModel(vaoID, indices.size() / 3);
}

unsigned int BufferLoader::createVAO(){
	unsigned int vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}

void BufferLoader::storeToVBO(std::vector<float> data, unsigned int length, unsigned int index){

	unsigned int vboID;
	glGenBuffers(1, &vboID);

	float* floatBufferPtr = new float[data.size()];
	std::vector<float>::iterator current = data.begin();
	std::vector<float>::iterator end = data.end();
	for (int i = 0; current != end; current++, i++){
		floatBufferPtr[i] = *current;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float),
		floatBufferPtr, GL_STATIC_DRAW);
	
	glVertexAttribPointer(index, length, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(index);
		
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	vboList.push_back(vboID);
}

void BufferLoader::storeElementsToVBO(std::vector<int> indices){
	unsigned int vboID;
	glGenBuffers(1, &vboID);

	int* intBufferPtr = new int[indices.size()];
	std::vector<int>::iterator current = indices.begin();
	std::vector<int>::iterator end = indices.end();
	for (int i = 0; current != end; current++, i++){
		intBufferPtr[i] = *current;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int),
		intBufferPtr, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BufferLoader::unbindVAO(){
	glBindVertexArray(0);
}

unsigned int BufferLoader::loadTexture(const char* filename, int *width, int *height){
	GLuint textureID;
	unsigned char * image;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load, create texture and generate mipmaps
	image = SOIL_load_image(filename, width, height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	textureList.push_back(textureID);

	return textureID;
}
