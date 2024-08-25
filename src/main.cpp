#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "shaderProcessing.h"
#include "setup.h"


/**
* The function in which all of the input code should be handled. This function
* should be called every render loop.
*/
void processInput(GLFWwindow *window);

// THERE IS VERY MINIMAL ERROR HANDLING IN THIS PRORGAM SO IF SOMETHING GOES
// WRONG, EVERYTHING WILL GO WRONG. IT IS NOT A BUG, IT IS A FEATURE.
int main(void) {
    GLFWwindow* window = setUp();

    // Shader setup
    GLuint shaderProgramId = setUpShaderProgram();

    // Uniform setup
    //GLint location = glGetUniformLocation(shaderProgramId, "u_Color");
    //if (location == -1) {
    //    std::cerr << "Uniform variable location could not be found." << std::endl;
    //}
    //glUniform4f(location, 0.2f, 0.8f, 0.3f, 1.0f);

    float positions[] = {
        -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // bottom left
         0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // bottom right
         0.5f,  0.5f,  0.0f, 0.0f, 1.0f, // top right
        -0.5f,  0.5f,  0.5f, 0.5f, 0.5f  // top left
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * 5 * sizeof(float), &positions, GL_STATIC_DRAW);
    
    // Position attributes.
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    // Colour attributes.
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &indices, GL_STATIC_DRAW);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // Make the triangle go blue.
        // float timeValue = glfwGetTime();
        // float blueValue = sin(timeValue) / 2.0f + 0.5f;
        // glUniform4f(location, 0.0f, 0.0f, blueValue, 1.0f);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


// ESC to exit, TAB to go into wireframe mode and LEFT_SHIFT to go back
// into fill mode.
void processInput(GLFWwindow *window) {
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
}
