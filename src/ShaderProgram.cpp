#include <iostream>
#include <fstream>

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char *vertexPath, const char *fragPath) {
    SetUpShaderProgram(vertexPath, fragPath);
}
ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_id);
}


void ShaderProgram::Use() {
    glUseProgram(m_id);
}


GLuint ShaderProgram::GetID() {
    return m_id;
}


bool ShaderProgram::SetBool(const std::string &name, bool value) const {
    GLint location = glGetUniformLocation(m_id, name.c_str());
    if (location == -1) {
        std::cerr << "Uniform variable \"" << name << "\" could not be found."
            << std::endl;
        return false;
    }
    
    glUniform1i(location, (int)value);
    return true;
}

bool ShaderProgram::SetInt(const std::string &name, int value) const {
    GLint location = glGetUniformLocation(m_id, name.c_str());
    if (location == -1) {
        std::cerr << "Uniform variable \"" << name << "\" could not be found."
            << std::endl;
        return false;
    }

    glUniform1i(location, value);
    return true;
}

bool ShaderProgram::SetFloat(const std::string &name, float value) const {
    GLint location = glGetUniformLocation(m_id, name.c_str());
    if (location == -1) {
        std::cerr << "Uniform variable \"" << name << "\" could not be found."
            << std::endl;
        return false;
    }

    glUniform1i(location, value);
    return true;
}

bool ShaderProgram::SetMatrix4(const std::string &name, glm::mat4 trans) const {
    GLint location = glGetUniformLocation(m_id, name.c_str());
    if (location == -1) {
        std::cerr << "Uniform variable \"" << name << "\" could not be found."
            << std::endl;
        return false;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(trans));
    return true;
}

// Main function to set up the shader program.
GLuint ShaderProgram::SetUpShaderProgram(const char *vertexPath, const char *fragPath) {
    // expected filepath: res\shaders\vertexShader.shader
    // expected filepath: res\shaders\fragmentShader.shader

    std::string vertexShader = ReadShaderFromFile(vertexPath);
    std::string fragmentShader = ReadShaderFromFile(fragPath);
    GLuint shaderProgram = CreateShaderProgram(vertexShader.c_str(), fragmentShader.c_str());
    glUseProgram(shaderProgram);
    return shaderProgram;
}


// Returns the source code of the shader in the specified file
std::string ShaderProgram::ReadShaderFromFile(const char *fileName) {
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

// Creates a shader program given the source code of the vertex and fragment shader
GLuint ShaderProgram::CreateShaderProgram(const char *vertexShader, const char *fragmentShader) {
    GLuint shaderProgram = glCreateProgram();
    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

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

    m_id = shaderProgram;
    return shaderProgram;
}


// Compiles the shader given the source code and type of shader it is
GLuint ShaderProgram::CompileShader(GLuint type, const char *source) {
    // check the type is a valid type.
    if ((type != GL_COMPUTE_SHADER)         &&
        (type != GL_VERTEX_SHADER)          &&
        (type != GL_TESS_CONTROL_SHADER)    &&
        (type != GL_TESS_EVALUATION_SHADER) &&
        (type != GL_GEOMETRY_SHADER)        &&
        (type != GL_FRAGMENT_SHADER)) {
        std::cerr << "Type of shader must be a valid type." << std::endl;
        exit(1);
    }

    GLuint id_ = glCreateShader(type);
    glShaderSource(id_, 1, &source, nullptr);
    glCompileShader(id_);

    GLint result;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        // Get the error message
        int length;
        glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &length);
        char *message = new char[length];
        glGetShaderInfoLog(id_, length, &length, message);

        // Print the error message
        type == GL_VERTEX_SHADER ? (std::cerr << "Vertex") : (std::cerr << "Fragment");
        std::cerr << "Shader could not compile. Error message: " << message
            << std::endl;

        glDeleteShader(id_);
        delete[] message;

        exit(1);
    }
    return id_;
}

