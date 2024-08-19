#define GLEW_STATIC

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shaderProcessing.h"


/**
* Sets up all of the libraries needed and returns a pointer to the main
* window being used. The pointer is a nullptr pointer if any of the 
* initialisations failed.
*/
GLFWwindow *setUp();


/**
* This is the callback function used when the window has been resized by the
* user.
*/
void framebufferSizeCallback(GLFWwindow *window, int width, int height);


void GLAPIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id
    , GLenum severity, GLsizei length, const GLchar* message, const void* userParam);


/**
* The function in which all of the input code should be handled. This function
* should be called every render loop.
*/
void processInput(GLFWwindow *window);

// THERE IS VERY MINIMAL ERROR HANDLING IN THIS PRORGAM SO IF SOMETHING GOES
// WRONG, EVERYTHING WILL GO WRONG. IT IS NOT A BUG, IT IS A FEATURE.
int main(void)
{
    GLFWwindow* window = setUp();
    if (window == nullptr) {
        return -1;
    }

    // Shader setup
    GLuint shaderProgramId = setUpShaderProgram();

    // Uniform setup
    GLint location = glGetUniformLocation(shaderProgramId, "u_Color");
    if (location == -1) {
        std::cerr << "Uniform variable location could not be found." << std::endl;
    }
    glUniform4f(location, 0.2f, 0.8f, 0.3f, 1.0f);

    float positions[] = {
        -0.5f, -0.5f, // bottom left
         0.5f, -0.5f, // bottom right
         0.5f,  0.5f, // top right
        -0.5f,  0.5f, // top left
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
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), &positions, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &indices, GL_STATIC_DRAW);

    float r = 0.0f;
    float rIncrement = 0.01f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);
        
        glUniform4f(location, r, 0.8f, 0.3f, 1.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        if (r >= 1.0f) {
            rIncrement = -0.01f;
        }
        else if (r <= 0.0f) {
            rIncrement = 0.01f;
        }
        r += rIncrement;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


GLFWwindow *setUp() {
    // sets up glfw.
    if (!glfwInit()) {
        std::cerr << "GLFW failed to initialise." << std::endl;
        exit(1);
    }
    
    // Sets up glfw window.
    GLFWwindow *window = glfwCreateWindow(960, 720, "Hello World", nullptr, nullptr);
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
    
    std::cout << "Currently using OpenGL version " << glGetString(GL_VERSION) << std::endl;
   

    // Sets the opengl viewport size and sets the framebufferSizeCallback
    // function to be called everytime the window is resized.
    glViewport(0, 0, 960, 720);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Sets up debug message callback function
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debugMessageCallback, nullptr);

    // Sets the background colour of the window.
    glClearColor(0.5f, 0.1f, 0.1f, 1.0f);

    return window;
}


void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    // glViewport resizes everything in the window to be able to fit within
    // The size of the window
    glViewport(0, 0, width, height);
}


void GLAPIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id
    , GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    
    std::string _source;
    std::string _type;
    std::string _severity;

    switch (source) {
        case GL_DEBUG_SOURCE_API:
        _source = "API";
        break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        _source = "WINDOW SYSTEM";
        break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
        _source = "SHADER COMPILER";
        break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
        _source = "THIRD PARTY";
        break;

        case GL_DEBUG_SOURCE_APPLICATION:
        _source = "APPLICATION";
        break;

        case GL_DEBUG_SOURCE_OTHER:
        _source = "UNKNOWN";
        break;

        default:
        _source = "UNKNOWN";
        break;
    }

    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
        _type = "ERROR";
        break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        _type = "DEPRECATED BEHAVIOR";
        break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        _type = "UDEFINED BEHAVIOR";
        break;

        case GL_DEBUG_TYPE_PORTABILITY:
        _type = "PORTABILITY";
        break;

        case GL_DEBUG_TYPE_PERFORMANCE:
        _type = "PERFORMANCE";
        break;

        case GL_DEBUG_TYPE_OTHER:
        _type = "OTHER";
        break;

        case GL_DEBUG_TYPE_MARKER:
        _type = "MARKER";
        break;

        default:
        _type = "UNKNOWN";
        break;
    }

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
        _severity = "HIGH";
        break;

        case GL_DEBUG_SEVERITY_MEDIUM:
        _severity = "MEDIUM";
        break;

        case GL_DEBUG_SEVERITY_LOW:
        _severity = "LOW";
        break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "NOTIFICATION";
        break;

        default:
        _severity = "UNKNOWN";
        break;
    }

   
    std::cerr << "id = " << id << ": type = " << _type << ", severity = " << _severity
        << ", source = " << _source << ", message" << message << std::endl;

    if (severity != GL_DEBUG_SEVERITY_NOTIFICATION) {
        exit(1);
    }
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
