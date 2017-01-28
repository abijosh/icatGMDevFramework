//
// Created by abijosh on 10/9/16.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "UserInteraction.h"

bool UserInteraction::left = false;
bool UserInteraction::right = false;
bool UserInteraction::up = false;
bool UserInteraction::down = false;
bool UserInteraction::space = false;
bool UserInteraction::escape = false;
bool UserInteraction::mouseLeftButtonDown = false;
bool UserInteraction::mouseRightButtonDown = false;

double UserInteraction::lastLeftMouseClickX = 0.0;
double UserInteraction::lastLeftMouseClickY = 0.0;
double UserInteraction::lastLeftMouseReleaseX = 0.0;
double UserInteraction::lastLeftMouseReleaseY = 0.0;

double UserInteraction::lastRightMouseClickX = 0.0;
double UserInteraction::lastRightMouseClickY = 0.0;
double UserInteraction::lastRightMouseReleaseX = 0.0;
double UserInteraction::lastRightMouseReleaseY = 0.0;

int UserInteraction::width = 0;
int UserInteraction::height = 0;

UserInteraction::UserInteraction()
{
}
UserInteraction::~UserInteraction()
{
}

void UserInteraction::keyEvent(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	bool keypress = false;
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		keypress = true;
	else if (action == GLFW_RELEASE)
		keypress = false;

	switch (key)
	{
	case GLFW_KEY_LEFT:
		left = keypress;
		break;

	case GLFW_KEY_RIGHT:
		right = keypress;
		break;

	case GLFW_KEY_UP:
		up = keypress;
		break;

	case GLFW_KEY_DOWN:
		down = keypress;
		break;

	case GLFW_KEY_SPACE:
		space = keypress;
		break;

	case GLFW_KEY_ESCAPE:
		escape = keypress;
		break;
	}

}

void UserInteraction::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if (action == GLFW_PRESS){

		if (button == GLFW_MOUSE_BUTTON_1){
			lastLeftMouseClickX = mouseX;
			lastLeftMouseClickY = height - mouseY;
			mouseLeftButtonDown = true;
		}
		if (button == GLFW_MOUSE_BUTTON_2){
			lastRightMouseClickX = mouseX;
			lastRightMouseClickY = height - mouseY;
			mouseRightButtonDown = true;
		}
	}
	else if (action == GLFW_RELEASE){
		if (button == GLFW_MOUSE_BUTTON_1){
			lastLeftMouseReleaseX = mouseX;
			lastLeftMouseReleaseY = height - mouseY;
			mouseLeftButtonDown = false;
		}
		if (button == GLFW_MOUSE_BUTTON_2){
			lastRightMouseReleaseX = mouseX;
			lastRightMouseReleaseY = height - mouseY;
			mouseRightButtonDown = false;
		}
	}

}