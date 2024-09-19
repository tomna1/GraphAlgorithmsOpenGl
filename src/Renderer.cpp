#include "Renderer.h"

void Renderer::Clear() const {
	// Clear what was previously drawn on the window.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const Mesh2D &mesh, const ShaderProgram &shader, const int posX, const int posY) const {
	shader.Use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(posX, posY, 0));
	shader.SetMatrix4("model", model);

	mesh.BindVAO();

	// Draws from the index data if there is index data
	if (mesh.GetIndicesCount() != 0) {
		mesh.BindIndexBuffer();
		glDrawElements(GL_TRIANGLES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}
	// If there is no index data, draws directly from the vertex array.
	else {
		glDrawArrays(GL_TRIANGLES, 0, mesh.GetVertexCount());
	}
}

void Renderer::DrawLines(const Mesh2D &mesh, const ShaderProgram &shader, const int posX, const int posY) const {
	shader.Use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(posX, posY, 0));
	shader.SetMatrix4("model", model);

	mesh.BindVAO();

	if (mesh.GetIndicesCount() != 0) {
		mesh.BindIndexBuffer();
		glDrawElements(GL_LINES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}
	else {
		glDrawArrays(GL_LINES, 0, mesh.GetVertexCount());
	}
}



