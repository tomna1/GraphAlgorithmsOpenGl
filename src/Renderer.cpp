#include "Renderer.h"

void Renderer::Clear() {
	// Clear what was previously drawn on the window.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, ShaderProgram &shader, Camera &cam) const {
	// shader.use();
	va.Bind();
	ib.Bind();
	shader.setMatrix4("view", cam.getViewMatrix());
	glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}
