#pragma once

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

class Window
{
public:
	Window(GLint windowWidth, GLint windowHeight);

	Window() : Window(800, 600) {}

	void initialise();

	GLint getBufferWidth() { return _bufferWidth; }
	GLint getBufferHeight() { return _bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(_mainWindow); }
	GLFWwindow* getWindow() { return _mainWindow; }

	bool* getsKeys() { return _keys; }
	GLfloat getXChange();
	GLfloat getYChange();
	glm::vec2 getCursor() { return glm::vec2(_lastX, _lastY); }

	void clear(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

	void swapBuffers() { glfwSwapBuffers(_mainWindow); }

	~Window();

private:
	GLFWwindow* _mainWindow;

	GLint _width, _height;
	GLint _bufferWidth, _bufferHeight;

	bool _keys[1024];

	GLfloat _lastX;
	GLfloat _lastY;
	GLfloat _xChange;
	GLfloat _yChange;
	bool _mouseFirstMoved;

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};