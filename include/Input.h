#ifndef ALL_INPUT_H
#define ALL_INPUT_H
#include "Camera.h"
#include "MappedGraph.h"
#include "Window.h"
#include "Scene.h"

#include <GLFW/glfw3.h>



class Mouse {
private:
	double m_x, m_y;

	// Should all either be GLFW_PRESS or GLFW_RELEASE.
	unsigned int m_previousRMBstate;
	unsigned int m_RMBstate;
	unsigned int m_previousLMBstate;
	unsigned int m_LMBstate;
public:
	Mouse();
	~Mouse();
	
	double GetX();
	double GetY();

	void SetX(double x);
	void SetY(double y);
	void SetMousePos(double x, double y);

	void SetLMB(unsigned int state);
	void SetRMB(unsigned int state);

	bool LMBclicked();
	bool RMBclicked();

	bool LMBreleased();
	bool RMBreleased();

	// Processes mouse inputs.
	// Selecting nodes when mouse is pressed on them, adding nodes to other
	// coordinates, selecting edges between nodes, added edges between nodes.
	void processMouseInput(const Window &window, MappedGraph &graph, Camera &cam, Scene &scene);
};

// Processes keyboard inputs.
// ESC to exit, TAB to go into wireframe mode and LEFT_SHIFT to go back
// into fill mode. WASD to move the camera, Q to zoom out and E to zoom in.
void processInput(GLFWwindow *window, Camera &cam, float deltaTime);


#endif
