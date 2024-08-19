#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>


/**
* Sets up all of the libraries needed and returns a pointer to the main
* window being used. The pointer is a nullptr pointer if any of the
* initialisations failed.
*/
GLFWwindow *setUp();