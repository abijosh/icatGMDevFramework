#pragma once
class Shader
{
public:
	Shader();
	~Shader();

	bool createShader(const char * vertex_file_path, const char * fragment_file_path);
	void start();
	void stop();

	int gettextureLocation();
    int getTransformMatrixLocation();
	int getViewMatrixLocation();

private:
	void bindAttributes();

private:
	int ShaderID;
	int textureLocation;
	int transformMatrixLocation, viewMatrixLocation;

public:
	const char* const* outputVector;
};