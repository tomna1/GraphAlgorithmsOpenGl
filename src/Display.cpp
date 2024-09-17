#include "Display.h"

#include "Errors.h"

#include <iostream>

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
	std::cout << "new width: " << width << ", new height: " << height << std::endl;
}

Display::Display(int width, int height) {
	// Sets up glfw window.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(width, height, "Hello World", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Window failed to open" << std::endl;
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	m_window = window;
	
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// Sets up glew.
	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW failed to initialise." << std::endl;
		glfwTerminate();
		exit(1);
	}

	std::cout << "Currently using OpenGL version " << glGetString(GL_VERSION)
		<< std::endl;

	// Sets up debug message callback function
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(Errors::debugMessageCallback, nullptr);

	// Sets the background colour of the window.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// GL_DEPTH_TEST is used to make sure that sides that are closes to the 
	// camera are drawn over sides that are further away
	glEnable(GL_DEPTH_TEST);
}

int Display::GetWidth() {
	// 3rd value is screen. width, 4th value is screen height.
	int screenSize[4];
	glGetIntegerv(GL_VIEWPORT, screenSize);
	return screenSize[2];
}

int Display::GetHeight() {
	// 3rd value is screen. width, 4th value is screen height.
	int screenSize[4];
	glGetIntegerv(GL_VIEWPORT, screenSize);
	return screenSize[3];
}

GLFWwindow *Display::GetWindow() {
	return m_window;
}
