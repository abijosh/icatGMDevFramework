#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "RawModel.h"
#include "Shader.h"
#include "Material.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "Scene.h"
#pragma once
class Renderer
{
public:
	Renderer();
	~Renderer();

	void setWindowPointer(GLFWwindow* windowPointer);
	void initializeCamera(int windowWidth, int windowHeight);
	Camera* getCamera();

    void setAspectRatio(float aspectRatio);
	void prepare();
	void postRender();
	void renderScene(Scene* EntityPointer);
private:
	void renderEntity(Entity* EntityPointer);
	void updateShaderLocationValues(Entity* EntityPointer);


private:
	GLFWwindow* mp_window;
	Camera *m_pCamera;
	float m_red, m_green, m_blue, m_alpha;
};

