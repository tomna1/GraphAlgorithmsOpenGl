#ifndef ALL_DISPLAY_H
#define ALL_DISPLAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Contains all information about the window being used to render opengl
// and its size. Might be expanded in the future to contains other things
class Display {
private:
	GLFWwindow *m_window;
public:
	// Initialises glew and setups up the glfw window. Glfw must be initialised
	// before this constructor will work.
	Display(int width, int height);
	
	int GetWidth();
	int GetHeight();
	GLFWwindow *GetWindow();
};

#endif