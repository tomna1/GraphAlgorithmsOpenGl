#ifndef RENDERER_H
#define RENDERER_H

#include "ShaderProgram.h"
#include "Mesh.h"

/**
* The renderer is used to draw objects to the screen. Currently can only
* draw a configured vertex array and index buffer to the screen using 
* a specified shader.
*/
class Renderer {
public:
	void Clear();

	void Draw(const Mesh2D &mesh, ShaderProgram &shader) const;
};

#endif
