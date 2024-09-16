#include "Input.h"

#define DEFAULT_SCREEN_WIDTH 960
#define DEFAULT_SCREEN_HEIGHT 720

Mouse::Mouse() {
    m_x = 0;
    m_y = 0;
}
Mouse::~Mouse() { }

double Mouse::GetX() {
    return m_x;
}
double Mouse::GetY() {
    return m_y;
}

void Mouse::SetX(double x) {
    m_x = x;
}
void Mouse::SetY(double y) {
    m_y = y;
}
void Mouse::SetMousePos(double x, double y) {
    m_x = x;
    m_y = y;
}

// Called whenever the window size is changed by the user.
void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    // glViewport resizes everything in the window to be able to fit within
    // The size of the window
    glViewport(0, 0, width, height);
}


// Sets up all of the callback functions that involve inputs by the user.
void setupInputCallbacks(GLFWwindow *window) {
    // Sets the opengl viewport size and sets the framebufferSizeCallback
    // function to be called everytime the window is resized.
    glViewport(0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}