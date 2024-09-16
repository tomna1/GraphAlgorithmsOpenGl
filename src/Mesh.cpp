#include "Mesh.h"

Mesh2D::Mesh2D() {
	glGenBuffers(1, &m_vbID);
	glGenBuffers(1, &m_ibID);
	glGenVertexArrays(1, &m_vaID);

	m_positionData = {};
	m_indices = {};
	m_colour = {0, 0, 0};
}
Mesh2D::Mesh2D(std::vector<glm::vec2> &positionData) {
	glGenBuffers(1, &m_vbID);
	glGenBuffers(1, &m_ibID);
	glGenVertexArrays(1, &m_vaID);

	m_positionData = positionData;
	m_indices = {};
	m_colour = { 0, 0, 0 };
	
	// Configuring vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbID);
	glBufferData(GL_ARRAY_BUFFER, positionData.size() * 2 * sizeof(float), positionData.data(), GL_STATIC_DRAW);

	// Configuring vertex array.
	glBindVertexArray(m_vaID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}
Mesh2D::Mesh2D(std::vector<glm::vec2> &positionData, std::vector<unsigned int> &indices) {
	glGenBuffers(1, &m_vbID);
	glGenBuffers(1, &m_ibID);
	glGenVertexArrays(1, &m_vaID);

	m_positionData = positionData;
	m_indices = indices;
	m_colour = { 0, 0, 0 };
	
	// Configuring vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbID);
	glBufferData(GL_ARRAY_BUFFER, positionData.size() * 2 * sizeof(float), positionData.data(), GL_STATIC_DRAW);

	// Configuring index buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// Since there is only position data atm, only the position attribute needs to be
	// configured. This will need to be change when more vertex attributes are added.
	
	// Configuring vertex array.
	glBindVertexArray(m_vaID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}
Mesh2D::Mesh2D(std::vector<glm::vec2> &positionData, std::vector<unsigned int> &indices, glm::vec3 colour)
	: Mesh2D(positionData, indices)
{
	m_colour = colour;
}
Mesh2D::~Mesh2D() {
	glDeleteBuffers(1, &m_vbID);
	glDeleteBuffers(1, &m_ibID);
	glDeleteVertexArrays(1, &m_vaID);
}


void Mesh2D::UpdatePositionVertices(std::vector<glm::vec2> &positionData) {
	m_positionData = positionData;

	// Configuring vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbID);
	glBufferData(GL_ARRAY_BUFFER, positionData.size() * 2 * sizeof(float), positionData.data(), GL_STATIC_DRAW);

	// Configuring vertex array.
	glBindVertexArray(m_vaID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}
void Mesh2D::UpdateIndices(std::vector<unsigned int> &indices) {
	m_indices = indices;

	// Configuring index buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}
void Mesh2D::UpdateColour(glm::vec3 colour) {
	m_colour = colour;
}


bool Mesh2D::isValidIndices() const {
	// if any of the indices is greater than the amount of vertices then false.
	for (int i = 0; i < m_indices.size(); i++) {
		if (m_indices[i] > (m_positionData.size() - 1)) return false;
	}
	return true;
}


unsigned int Mesh2D::GetIndicesCount() const {
	return m_indices.size();
}
unsigned int Mesh2D::GetVertexCount() const {
	return m_positionData.size();
}

GLuint Mesh2D::GetVertexArrayID() const {
	return m_vaID;
}
GLuint Mesh2D::GetIndexBufferID() const {
	return m_ibID;
}

glm::vec3 Mesh2D::GetColour() const {
	return m_colour;
}

