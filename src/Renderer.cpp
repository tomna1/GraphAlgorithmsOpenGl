#include "Renderer.h"

void Renderer::Clear() const {
	// Clear what was previously drawn on the window.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const Mesh2D &mesh, ShaderProgram &shader, int posX, int posY) const {
	shader.Use();
	glBindVertexArray(mesh.GetVertexArrayID());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndexBufferID());

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(posX, posY, 0));
	shader.SetMatrix4("model", model);

	glDrawElements(GL_TRIANGLES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
}
