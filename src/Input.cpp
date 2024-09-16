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


// ESC to exit, TAB to go into wireframe mode and LEFT_SHIFT to go back
// into fill mode. WASD to move the camera, Q to zoom out and E to zoom in.
void processInput(GLFWwindow *window, Camera &cam, float deltaTime) {
    // Use to make the simulation run smoother. See glfw event processing for
    // more details.
    glfwPostEmptyEvent();

    // If the esc key is pressed then the window closes.
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
        // TODO: SWITCH BETWEEN LINES AND FILLED RATHER THAN JUST SWITCHING
        // TO LINES AND NOT BEING ABLE TO SWITCH BACK
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.ProcessKeyboardMovement(Keys::W_KEY, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.ProcessKeyboardMovement(Keys::S_KEY, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.ProcessKeyboardMovement(Keys::A_KEY, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.ProcessKeyboardMovement(Keys::D_KEY, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cam.ProcessKeyboardMovement(Keys::Q_KEY, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cam.ProcessKeyboardMovement(Keys::E_KEY, deltaTime);
}


// Selecting nodes when mouse is pressed on them, adding nodes to other
// coordinates, selecting edges between nodes, added edges between nodes.
void processMouseInput(GLFWwindow *window, Mouse &mouse) {
    // if the left mouse button is not pressed, do nothing.
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state != GLFW_PRESS) return;

    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    int screenSize[4];
    glGetIntegerv(GL_VIEWPORT, screenSize);

    // if mouse pos within correct bounds, update mouse.
    if (xPos > 0 && xPos < screenSize[2]) mouse.SetX(xPos);
    if (yPos > 0 && yPos < screenSize[3]) mouse.SetY(yPos);


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