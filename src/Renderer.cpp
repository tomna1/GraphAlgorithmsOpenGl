#include "Renderer.h"

void Renderer::Clear() {
	// Clear what was previously drawn on the window.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, ShaderProgram &shader, Camera &cam) const {
	shader.Use();
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}
