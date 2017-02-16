
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class UserInteraction {
public:
	UserInteraction();
	~UserInteraction();

	static void keyEvent(GLFWwindow* window, int key, int scancode, int action, int mode);

	static bool left, right, up, down, space, escape, mouseLeftButtonDown, mouseRightButtonDown;
	static int width, height;
	static double lastLeftMouseClickX, lastLeftMouseClickY, lastLeftMouseReleaseX, lastLeftMouseReleaseY;
	static double lastRightMouseClickX, lastRightMouseClickY, lastRightMouseReleaseX, lastRightMouseReleaseY;
	static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
	static bool changed;

};
