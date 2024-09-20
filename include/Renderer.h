#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "Mesh.h"
#include "Model.h"
#include "Scene.h"

/**
* The renderer is used to draw objects to the screen. Currently can only
* draw a configured vertex array and index buffer to the screen using 
* a specified shader.
*/
class Renderer {
public:
	// Clears the window.
	void Clear() const;

	// Draws a mesh onto the screen.
	void Draw(const Mesh2D &mesh, const ShaderProgram &shader, const int posX, const int posY) const;

	// Draws a scene onto the screen.
	void Draw(Scene &scene, const ShaderProgram &shader) const;

	void DrawLines(const Mesh2D &mesh, const ShaderProgram &shader, const int posX, const int posY) const;
};

#endif
