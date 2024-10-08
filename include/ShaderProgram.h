#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
* A Shader program currently consists of a vertex shader and a fragment shader.
* Uniform variables can be set during runtime using the setter methods.
*/
class ShaderProgram {
private:
	GLuint m_id;
public:
	ShaderProgram(const char *vertexPath, const char *fragPath);
	~ShaderProgram();

	// Activate the shader program.
	void Use() const;

	// Gets the id of the shader program. Shader Program must first have been
	// setup using the setUpShaderProgram method.
	GLuint GetID() const;

	// Utility uniform functions.
	
	// Sets a bool uniform variable given the name of the variable and the
	// value to set it to.
	bool SetBool(const std::string &name, bool value) const;
	// Sets a int uniform variable given the name of the variable and the
	// value to set it to.
	bool SetInt(const std::string &name, int value) const;
	// Sets a float uniform variable given the name of the variable and the
	// value to set it to.
	bool SetFloat(const std::string &name, float value) const;
	// Sets a 4x4 matrix uniform variable given the name of the variable in the shader
	// and the value to set it to.
	bool SetMatrix4(const std::string &name, glm::mat4 trans) const;
	// Sets a 3d vector of floats uniform variable given the name of the variable
	// in the shader and the value to set it to.
	bool SetVec3f(const std::string &name, glm::vec3 vector) const;

private:
	// Main function to set up the shader program.
	GLuint SetUpShaderProgram(const char *vertexShader, const char *fragmentShader);
	// Returns the source code of the shader in the specified file
	std::string ReadShaderFromFile(const char *fileName);
	// Creates a shader program given the source code of the vertex and fragment shader
	GLuint CreateShaderProgram(const char *vertexShader, const char *fragmentShader);
	// Compiles the shader given the source code and type of shader it is
	GLuint CompileShader(GLuint type, const char *source);
};

#endif