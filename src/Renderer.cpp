#include "..\include\Renderer.h"

void Renderer::Draw(const VertexArray &va, ShaderProgram &shader, const Camera &cam) const {
	shader.use();
	va.Bind();
	glDrawArrays(GL_TRIANGLES, 0, );
}
