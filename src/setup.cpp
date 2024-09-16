#define DEFAULT_SCREEN_WIDTH 960
#define DEFAULT_SCREEN_HEIGHT 720

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

#include "setup.h"

// This function prints out a standard error message to the error stream.
void GLAPIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id
    , GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {

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
    glDebugMessageCallback(debugMessageCallback, nullptr);

    // Sets the background colour of the window.
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // GL_DEPTH_TEST is used to make sure that sides that are closes to the 
    // camera are drawn over sides that are further away
    glEnable(GL_DEPTH_TEST);

    return window;
}