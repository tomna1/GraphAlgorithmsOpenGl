#include "Renderer.h"

void Renderer::Clear() {
	// Clear what was previously drawn on the window.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const Mesh2D &mesh, ShaderProgram &shader) const {
	shader.Use();
	glBindVertexArray(mesh.GetVertexArrayID());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndexBufferID());

	glDrawElements(GL_TRIANGLES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
}
