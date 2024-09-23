#include "Input.h"

#include <iostream>

#define DEFAULT_SCREEN_WIDTH 960
#define DEFAULT_SCREEN_HEIGHT 720

Mouse::Mouse() {
    m_x = 0;
    m_y = 0;
    m_previousRMBstate = GLFW_RELEASE;
    m_RMBstate = GLFW_RELEASE;
    m_previousLMBstate = GLFW_RELEASE;
    m_LMBstate = GLFW_RELEASE;
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

void Mouse::SetLMB(unsigned int state) {
    m_previousLMBstate = m_LMBstate;
    m_LMBstate = state;
}
void Mouse::SetRMB(unsigned int state) {
    m_previousRMBstate = m_RMBstate;
    m_RMBstate = state;
}

bool Mouse::LMBclicked() {
    if ((m_previousLMBstate == GLFW_RELEASE) && (m_LMBstate == GLFW_PRESS)) return true;
    return false;
}
bool Mouse::RMBclicked() {
    if ((m_previousRMBstate == GLFW_RELEASE) && (m_RMBstate == GLFW_PRESS)) return true;
    return false;
}
bool Mouse::LMBreleased() {
    if ((m_previousLMBstate == GLFW_PRESS) && (m_LMBstate == GLFW_RELEASE)) return true;
    return false;
}
bool Mouse::RMBreleased() {
    if ((m_previousRMBstate == GLFW_PRESS) && (m_RMBstate == GLFW_RELEASE)) return true;
    return false;
}


// Selecting nodes when mouse is pressed on them, adding nodes to other
// coordinates, selecting edges between nodes, added edges between nodes.
// left clicking one node and then another node should create an edje between them.
// left clicking empty tile should create a new node there
// left clicking an edge should allow to edit the edge.
// right clicking should remove all currently selected nodes.
void Mouse::processMouseInput(const Window &window, MappedGraph &graph, Camera &cam, Scene &scene) {
    double xPos, yPos;
    glfwGetCursorPos(window.GetWindow(), &xPos, &yPos);

    // if mouse pos within correct bounds, update mouse.
    if (xPos > 0 && xPos < window.GetWidth()) SetX(xPos);
    if (yPos > 0 && yPos < window.GetHeight()) SetY(yPos);

    // left and right mouse buttons.
    int lmbstate = glfwGetMouseButton(window.GetWindow(), GLFW_MOUSE_BUTTON_LEFT);
    int rmbstate = glfwGetMouseButton(window.GetWindow(), GLFW_MOUSE_BUTTON_RIGHT);
    SetLMB(lmbstate);
    SetRMB(rmbstate);

    if (RMBreleased()) {
        scene.DeselectAllModels();
    }

    // If hovering over an empty point, add a new node.
    glm::vec2 point = cam.ScreenToWorld(GetX(), GetY(), window);
    if (LMBreleased() &&
        !graph.HasNodeAtPoint(static_cast<int>(std::round(point.x)), static_cast<int>(std::round(point.y))))
    {
        // mouse coordinate and graph coordinate use different system.
        // need to convert mouse coordinates to graph coordinates.
        graph.AddNodeAtPoint(static_cast<int>(std::round(point.x)), static_cast<int>(std::round(point.y)));
        std::string hexMesh = "hexagonMesh";
        Model2D model = Model2D(hexMesh, std::round(point.x), std::round(point.y));
        scene.AddModel(model);
    }

    // if hovering over an already existing node, select it.
    if (LMBreleased() &&
        graph.HasNodeAtPoint(static_cast<int>(std::round(point.x)), static_cast<int>(std::round(point.y))))
    {
        scene.SelectModelAtPoint(std::round(point.x), std::round(point.y));
    }
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

