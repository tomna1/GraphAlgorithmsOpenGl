#ifndef ALL_INPUT_H
#define ALL_INPUT_H

#include <GLFW/glfw3.h>

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

void setupInputCallbacks(GLFWwindow *window);

#endif
