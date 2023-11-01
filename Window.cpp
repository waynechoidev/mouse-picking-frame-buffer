#include "Window.h"

Window::Window(GLint windowWidth, GLint windowHeight)
{
	_width = windowWidth;
	_height = windowHeight;

	_bufferWidth = _bufferHeight = 0;
	_mainWindow = 0;

	for (size_t i = 0; i < 1024; i++)
	{
		_keys[i] = 0;
	}

	_xChange = 0;
	_yChange = 0;
	_lastX = 0;
	_lastY = 0;
	_mouseFirstMoved = false;
}

void Window::initialise()
{
	if (!glfwInit())
	{
		std::cout << "Error Initialising GLFW";
		glfwTerminate();
	}

	// Setup GLFW Windows Properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatiblity
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	_mainWindow = glfwCreateWindow(_width, _height, "OpenGL Lighting", NULL, NULL);

	if (!_mainWindow)
	{
		std::cout << "Error creating GLFW window!";
		glfwTerminate();
	}

	// Get buffer size information
	glfwGetFramebufferSize(_mainWindow, &_bufferWidth, &_bufferHeight);

	// Set the current context
	glfwMakeContextCurrent(_mainWindow);

	// Handle Key + Mouse Input
	createCallbacks();
	//glfwSetInputMode(_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow modern extension access
	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cout << "Error: %s" << glewGetErrorString(error);
		glfwDestroyWindow(_mainWindow);
		glfwTerminate();
	}

	glEnable(GL_DEPTH_TEST);
	//glCullFace(GL_BACK);

	// Create Viewport
	glViewport(0, 0, _bufferWidth, _bufferHeight);

	glfwSetWindowUserPointer(_mainWindow, this);

}

void Window::clear(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(_mainWindow, handleKeys);
	glfwSetCursorPosCallback(_mainWindow, handleMouse);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = _xChange;
	_xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = _yChange;
	_yChange = 0.0f;
	return theChange;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->_keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->_keys[key] = false;
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->_mouseFirstMoved)
	{
		theWindow->_lastX = (GLfloat)xPos;
		theWindow->_lastY = (GLfloat)yPos;
		theWindow->_mouseFirstMoved = false;
	}

	theWindow->_xChange = (GLfloat)xPos - theWindow->_lastX;
	theWindow->_yChange = theWindow->_lastY - (GLfloat)yPos;

	theWindow->_lastX = (GLfloat)xPos;
	theWindow->_lastY = (GLfloat)yPos;
}

Window::~Window()
{
	glfwDestroyWindow(_mainWindow);
	glfwTerminate();
}
