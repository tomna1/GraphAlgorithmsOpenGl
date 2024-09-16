#ifndef ALL_INPUT_H
#define ALL_INPUT_H

#include <GLFW/glfw3.h>

#include "Camera.h"

class Mouse {
private:
	double m_x, m_y;

public:
	Mouse();
	~Mouse();
	
	double GetX();
	double GetY();

	void SetX(double x);
	void SetY(double y);
	void SetMousePos(double x, double y);
};

// Processes keyboard inputs.
// ESC to exit, TAB to go into wireframe mode and LEFT_SHIFT to go back
// into fill mode. WASD to move the camera, Q to zoom out and E to zoom in.
void processInput(GLFWwindow *window, Camera &cam, float deltaTime);

// Processes mouse inputs.
// Selecting nodes when mouse is pressed on them, adding nodes to other
// coordinates, selecting edges between nodes, added edges between nodes.
void processMouseInput(GLFWwindow *window, Mouse &mouse);

// will setup all callback functions involving any user inputs.
void setupInputCallbacks(GLFWwindow *window);

#endif
