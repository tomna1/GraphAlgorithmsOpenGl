#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>

#include "ShaderProgram.h"
#include "setup.h"
#include "Camera.h"
#include "MappedGraph.h"
#include "GraphNode.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Renderer.h"


// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

/**
* The function in which all of the input code should be handled. This function
* should be called every render loop.
*/
void processInput(GLFWwindow *window, Camera *cam);


// THERE IS VERY MINIMAL ERROR HANDLING IN THIS PRORGAM SO IF SOMETHING GOES
// WRONG, EVERYTHING WILL GO WRONG. IT IS NOT A BUG, IT IS A FEATURE.
int main(void) {
    GLFWwindow* window = setUp();

    // Shader setup
    ShaderProgram shader1("res\\shaders\\vertexShader.shader", "res\\shaders\\fragmentShader.shader");

    // Camera setup
    Camera cam = Camera();

    // model matrix consists of translations, scaling and rotations applied
    // to all objects to place then in the correct global world space.
    glm::mat4 model = glm::mat4(1.0f);
    // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.5f, 0.0f));

    // A projection matrix does some stuff with perspective honestly im not sure.
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 960.0f / 720.0f, 0.1f, 100.0f);

    shader1.SetMatrix4("model", model);
    shader1.SetMatrix4("view", cam.GetViewMatrix());
    shader1.SetMatrix4("projection", projection);

    // cube vertices array
    float positions[] = {
         // positions         // colour
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.5f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    float GraphNodeVertices[] = {
        // just a simple hexagon for now.
        -0.5f,  0.25f, // top left
         0.0f,  0.5f, // top middle
         0.5f,  0.25f, // top right
         0.5f, -0.25f, // bottom right
         0.0f, -0.5f, // bottom middle
        -0.5f, -0.25f // bottom left
    };
    unsigned int GNindices[] = {
        0, 1, 2, // top triangle
        3, 4, 5, // bottom triangle
        5, 0, 2, // square p1
        2, 3, 5  // square p2
    };

    VertexArray va = VertexArray();
    va.Bind();

    VertexBuffer vb = VertexBuffer(GraphNodeVertices, 6 * 2 * sizeof(float));
    vb.Bind();

    VertexArrayLayout layout1 = VertexArrayLayout();
    layout1.AddAttribute(VertexAttribute{GL_FLOAT, 2, GL_FALSE});
    va.AddLayout(vb, layout1);

    IndexBuffer ib = IndexBuffer(GNindices, 12);
    ib.Bind();

    Renderer renderer = Renderer();

    // Loop until the user closes the window.
    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();

        // Timing stuff
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Updates the camera and processes additional input
        processInput(window, &cam);

        // shader unform setters
        shader1.SetMatrix4("view", cam.GetViewMatrix());

        // Draw the vb.
        renderer.Draw(va, ib, shader1, cam);

        // Swap front and back buffers 
        glfwSwapBuffers(window);

        // Poll for and process events 
        glfwPollEvents();
    }

    shader1.Destroy();
    glfwTerminate();
    return 0;
}

// ESC to exit, TAB to go into wireframe mode and LEFT_SHIFT to go back
// into fill mode. WASD to move the camera, Q to zoom out and E to zoom in.
void processInput(GLFWwindow *window, Camera *cam) {
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
        cam->ProcessKeyboardMovement(Keys::W_KEY, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam->ProcessKeyboardMovement(Keys::S_KEY, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam->ProcessKeyboardMovement(Keys::A_KEY, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam->ProcessKeyboardMovement(Keys::D_KEY, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cam->ProcessKeyboardMovement(Keys::Q_KEY, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cam->ProcessKeyboardMovement(Keys::E_KEY, deltaTime);
}

