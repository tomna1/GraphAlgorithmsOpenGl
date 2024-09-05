#ifndef RENDERER_H
#define RENDERER_H

#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "IndexBuffer.h"

class Renderer {
public:
	void Clear();
	
	void Draw(const VertexArray &va, const IndexBuffer &ib, ShaderProgram &shader, Camera &cam) const;
};

#endif
