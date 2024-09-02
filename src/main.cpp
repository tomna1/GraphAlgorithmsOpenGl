#define GLEW_STATIC

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
    ShaderProgram s1("res\\shaders\\vertexShader.shader", "res\\shaders\\fragmentShader.shader");
    s1.use();

    // Camera setup
    Camera cam = Camera();

    // GraphNode setup
    GraphNode n[3];

    n[0] = GraphNode();
    n[1] = GraphNode(1, 5);
    n[2] = GraphNode(-2, -7);


    // model matrix consists of translations, scaling and rotations applied
    // to all objects to place then in the correct global world space.
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.5f, 0.0f));

    // A projection matrix does some stuff with perspective honestly im not sure.
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 960.0f / 720.0f, 0.1f, 100.0f);

    s1.setMatrix4("model", model);
    s1.setMatrix4("view", cam.getViewMatrix());
    s1.setMatrix4("projection", projection);

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

    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * 36 * sizeof(float), &positions, GL_STATIC_DRAW);
    
    // Position attributes.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // Colour attributes.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // Clear what was previously drawn on the window.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Timing stuff
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, &cam);

        // Draws 10 rainbow cubes in various places and rotations
        /*
        for (unsigned int i = 0; i < 10; i++)
        {
            // create 10 cubes at different positions and rotations
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            s1.setMatrix4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        */

        // Draw all the nodes in the graph.
        for (int i = 0; i < 3; i++) {
            glm::mat4 model = n[i].generateModelMatrix();
            s1.setMatrix4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
       
        s1.setMatrix4("view", cam.getViewMatrix());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    s1.destroy();
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
