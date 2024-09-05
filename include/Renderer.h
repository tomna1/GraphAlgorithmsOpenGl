#ifndef RENDERER_H
#define RENDERER_H

#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Camera.h"

class Renderer {
public:
	void Draw(const VertexArray &va, ShaderProgram &shader, const Camera &cam) const;
};

#endif
