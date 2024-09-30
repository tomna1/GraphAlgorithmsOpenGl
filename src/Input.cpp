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


    // deselect all models if right click.
    if (RMBreleased()) {
        scene.DeselectAllModels();
    }

    // If hovering over an empty point, add a new node.
    glm::vec2 point = cam.ScreenToWorld(GetX(), GetY(), window);
    int x = static_cast<int>(std::round(point.x));
    int y = static_cast<int>(std::round(point.y));
    if (LMBreleased() && !graph.HasNodeAtPoint(x, y)) {
        
        // mouse coordinate and graph coordinate use different system.
        // need to convert mouse coordinates to graph coordinates.
        std::string name = "Node " + std::to_string(x) + "," + std::to_string(y);
        GraphNode node = GraphNode(name, x, y);
        graph.AddNode(node);
        std::string hexMesh = "hexagonMesh";
        Model2D model = Model2D(hexMesh, (float)x, (float)y);
        scene.AddModel(model);
        return;
    }

    // if left click on a node with no other selected models or a single other
    // selected model, select the model. If left click on a model when 2 models
    // already selected, deselect one and select new one. If left shift is down
    // selects the model regardless of how many other models are selected.
    if (LMBreleased() && graph.HasNodeAtPoint(x, y)) {
        if (scene.GetSelectedModelCount() <= 1) {
            scene.SelectModelAtPoint(std::round(point.x), std::round(point.y));
            return;
        }
        
        if (glfwGetKey(window.GetWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            scene.SelectModelAtPoint(std::round(point.x), std::round(point.y));
            return;
        }
        
        while (scene.GetSelectedModelCount() >= 2) {
            scene.DeselectLastModelSelected(1);
        }
        scene.SelectModelAtPoint(std::round(point.x), std::round(point.y));
    }
}


// ESC to exit, TAB to go into wireframe mode and LEFT_SHIFT to go back
// into fill mode. WASD to move the camera, Q to zoom out and E to zoom in.
void processInput(GLFWwindow *window, Camera &cam, float deltaTime) {
    // Use to make the simulation run smoother. See glfw event processing for
    // more details.
    glfwPostEmptyEvent();

    static bool isWireframeMode = false;

    // If the esc key is pressed then the window closes.
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
        if (isWireframeMode) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        isWireframeMode = !isWireframeMode;
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

