#include "Header.h"

DisplayManager::DisplayManager()
{
}


DisplayManager::~DisplayManager()
{
}

bool DisplayManager::createDisplay(int width, int height, const char* title){
	WIDTH = width;
	HEIGHT = height;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_pWindow = glfwCreateWindow(WIDTH, HEIGHT, title, glfwGetPrimaryMonitor(), nullptr);
	//good practice again!!!
	if (m_pWindow){
		return true;
	}
	return false;
}

void DisplayManager::setCurrentContext(){
	glfwMakeContextCurrent(m_pWindow);
}

GLFWwindow* DisplayManager::getWindowPointer(){
	return m_pWindow;
}

bool DisplayManager::isCloseRequested() {
	return glfwWindowShouldClose(m_pWindow);
}

void DisplayManager::closeWindow() {
	glfwSetWindowShouldClose(m_pWindow, true);
}

void DisplayManager::pollEvents(){
	glfwPollEvents();
}

void DisplayManager::update(float deltaTime){
}
