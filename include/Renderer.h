#ifndef RENDERER_H
#define RENDERER_H

#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "IndexBuffer.h"

/**
* The renderer is used to draw objects to the screen. Currently can only
* draw a configured vertex array and index buffer to the screen using 
* a specified shader.
*/
class Renderer {
public:
	void Clear();
	
	void Draw(const VertexArray &va, const IndexBuffer &ib, ShaderProgram &shader, Camera &cam) const;
};

#endif
