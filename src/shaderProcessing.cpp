#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include <GL/glew.h>

// Tbh im not exactly sure that everything im doing is safe but it is working
// fine for now so i wont touch it anymore.

// Returns the source code of the shader file. Memory must be freed.
static std::string readShaderFromFile(const char* fileName) {
    std::ifstream file;
    file.open(fileName);

    if (file.fail()) {
        std::cerr << "File \"" << fileName << "\" failed to open." << std::endl;
        return "";
    }
    
    std::string output;
    std::string fileLine;
    
    while (std::getline(file, fileLine)) {
        output += fileLine;
        output.push_back('\n');
    }

    output.shrink_to_fit();
    return output;
}


// Will compile a shader and return an ID which references that compiled
// shader. If the shader fails to compile, it will print an error message
// to the standard output but wont really do any error handling.
static GLuint compileShader(GLuint type, const char* source) {
    // TODO : ERROR HANDLING IF type IS NOT A VALID TYPE.
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    GLint result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        // Get the error message
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);

        // Print the error message
        type == GL_VERTEX_SHADER ? (std::cerr << "Vertex") : (std::cerr << "Fragment");
        std::cerr << "Shader could not compile. Error message: " << message
            << std::endl;
        
        glDeleteShader(id);
        free(message);

        exit(1);
    }
    return id;
}

// Given a pointer to the source code of the vertex shader and a pointer to
// the source code of the fragment shader, it will compile these shaders
// and link them to a program and will then return the id of the program.
static GLuint createShaderProgram(const char *vertexShader, const char *fragmentShader) {
    GLuint shaderProgram = glCreateProgram();
    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
    glValidateProgram(shaderProgram);

    GLint programLinkResult;
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &programLinkResult);
    if (programLinkResult == GL_FALSE) {
        std::cerr << "Program failed to validate." << std::endl;
        // TODO: ACTUAL ERROR HANDLING
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return shaderProgram;
}


// Setups up the shader program based on the shader files that are called at
// the start of the function. To read different shader files, this function
// has to be refactored.
GLuint setUpShaderProgram() {
    std::string vertexShader = readShaderFromFile("res\\shaders\\vertexShader.shader");
    std::string fragmentShader = readShaderFromFile("res\\shaders\\fragmentShader.shader");
    GLuint shaderProgram = createShaderProgram(vertexShader.c_str(), fragmentShader.c_str());
    glUseProgram(shaderProgram);
    glDeleteProgram(shaderProgram);
    return shaderProgram;
}
