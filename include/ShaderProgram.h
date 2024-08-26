#include <string>

#include <GL/glew.h>

class ShaderProgram {
private:
	GLuint m_id;
public:
	ShaderProgram(const char *vertexPath, const char *fragPath);

	// Activate the shader program.
	void use();

	void destroy();

	GLuint getID();

	// Utility uniform functions.
	
	// Sets a bool uniform variable given the name of the variable and the
	// value to set it to.
	bool setBool(const std::string &name, bool value) const;
	// Sets a int uniform variable given the name of the variable and the
	// value to set it to.
	bool setInt(const std::string &name, int value) const;
	// Sets a float uniform variable given the name of the variable and the
	// value to set it to.
	bool setFloat(const std::string &name, float value) const;

private:
	// Main function to set up the shader program.
	GLuint setUpShaderProgram(const char *vertexShader, const char *fragmentShader);
	// Returns the source code of the shader in the specified file
	std::string readShaderFromFile(const char *fileName);
	// Creates a shader program given the source code of the vertex and fragment shader
	GLuint createShaderProgram(const char *vertexShader, const char *fragmentShader);
	// Compiles the shader given the source code and type of shader it is
	GLuint compileShader(GLuint type, const char *source);
};