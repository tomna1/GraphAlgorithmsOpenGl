#ifndef ALL_ERRORS_H
#define ALL_ERRORS_H

#include <GL/glew.h>

#include <string>
#include <iostream>

class Errors {
public:
    // This function prints out a standard error message to the error stream.
    static void GLAPIENTRY debugMessageCallback(GLenum source, GLenum type, GLuint id
        , GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
};

#endif


