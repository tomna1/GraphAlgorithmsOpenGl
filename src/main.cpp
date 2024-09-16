#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>

#include "ShaderProgram.h"
#include "Camera.h"
#include "MappedGraph.h"
#include "GraphNode.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Input.h"
#include "Errors.h"

#define DEFAULT_SCREEN_WIDTH 960
#define DEFAULT_SCREEN_HEIGHT 720


GLFWwindow *setUp() {
    // sets up glfw.
    if (!glfwInit()) {
        std::cerr << "GLFW failed to initialise." << std::endl;
        exit(1);
    }

    // Sets up glfw window.
    GLFWwindow *window = glfwCreateWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "Hello World", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Window failed to open" << std::endl;
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);


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

    return window;
}


// THERE IS VERY MINIMAL ERROR HANDLING IN THIS PRORGAM SO IF SOMETHING GOES
// WRONG, EVERYTHING WILL GO WRONG. IT IS NOT A BUG, IT IS A FEATURE.
int main(void) {
    GLFWwindow* window = setUp();

    ShaderProgram shader1("res\\shaders\\vertexShader.shader", "res\\shaders\\fragmentShader.shader");
    Camera cam = Camera();
    Renderer renderer = Renderer();
    Mouse mouse = Mouse();

    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // model matrix consists of translations, scaling and rotations applied
    // to all objects to place then in the correct global world space.
    glm::mat4 model = glm::mat4(1.0f);

    // A projection matrix does some stuff with perspective honestly im not sure.
    // TODO: maybe i should put this in my camera class idk.
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 960.0f / 720.0f, 0.1f, 100.0f);

    shader1.SetMatrix4("model", model);
    shader1.SetMatrix4("view", cam.GetViewMatrix());
    shader1.SetMatrix4("projection", projection);


    std::vector<glm::vec2> hexagonVertices = {
        {-0.5f,  0.25f}, // top left
        {0.0f,  0.5f}, // top middle
        {0.5f,  0.25f}, // top right
        {0.5f, -0.25f}, // bottom right
        {0.0f, -0.5f}, // bottom middle
        {-0.5f, -0.25f} // bottom left
    };

    std::vector<unsigned int> hexagonIndices = {
        0, 1, 2, // top triangle
        3, 4, 5, // bottom triangle
        5, 0, 2, // square p1
        2, 3, 5  // square p2
    };

    // I am going to use the hexagon mesh to draw the graphnodes.
    Mesh2D hexagonMesh = Mesh2D(hexagonVertices, hexagonIndices);
    hexagonVertices.resize(0);
    hexagonIndices.resize(0);


    // The grid can either be stored as 2 lines which i translate with a model matrix
    // multiple times to make a grid or multiple lines which are all stored in the
    // gridVertices array which make up the grid and the entire grid can be translated by a model matrix.
    std::vector<glm::vec2> gridVertices;
    int gridSize = 100;
    int startX = -(gridSize / 2);
    int startY = -(gridSize / 2);;

    for (int i = 0; i < gridSize; i++) {
        // Adding X line
        gridVertices.push_back({ startX + i, startY });
        gridVertices.push_back({ startX + i, startY + gridSize });

        // Adding Y line.
        gridVertices.push_back({ startX, startY + i });
        gridVertices.push_back({ startX + gridSize, startY + i });
    }
 
    Mesh2D gridMesh = Mesh2D(gridVertices);
    gridMesh.UpdateColour({ 0.5f, 0.0f, 0.0f });
    gridVertices.resize(0);


    MappedGraph graph = MappedGraph();
    graph.AddNode({ 0, 0 });
    graph.AddNode({ 10, 10 });
    graph.AddNode({ -10, -10 });
    
    std::vector<glm::ivec2> nodesPos = {};

    // Loop until the user closes the window.
    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();

        // Timing stuff
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Updates the camera and processes additional input
        processInput(window, cam, deltaTime);
        processMouseInput(window, mouse);

        // Changing camera view.
        shader1.SetMatrix4("view", cam.GetViewMatrix());

        // Draws the graph nodes.
        nodesPos = graph.GetNodesPosition();
        for (int i = 0; i < nodesPos.size(); i++) {
            renderer.Draw(hexagonMesh, shader1, nodesPos[i].x, nodesPos[i].y);
        }

        // Draws the grid.
        renderer.DrawLines(gridMesh, shader1, 0, 0);

        // Swap front and back buffers 
        glfwSwapBuffers(window);
        // Poll for and process events 
        glfwWaitEvents();
    }

    glfwTerminate();
    return 0;
}


