#include "Mesh.h"

Mesh2D::Mesh2D() {
	glGenBuffers(1, &m_vbID);
	glGenBuffers(1, &m_ibID);
	glGenVertexArrays(1, &m_vaID);

	m_positionData = {};
	m_indices = {};
}
Mesh2D::Mesh2D(const std::vector<glm::vec2> &positionData) {
	glGenBuffers(1, &m_vbID);
	glGenBuffers(1, &m_ibID);
	glGenVertexArrays(1, &m_vaID);

	m_positionData = positionData;
	m_indices = {};
	
	// Configuring vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbID);
	glBufferData(GL_ARRAY_BUFFER, positionData.size() * 2 * sizeof(float), positionData.data(), GL_STATIC_DRAW);

	// Configuring vertex array.
	glBindVertexArray(m_vaID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}
Mesh2D::Mesh2D(const std::vector<glm::vec2> &positionData, const std::vector<unsigned int> &indices) {
	glGenBuffers(1, &m_vbID);
	glGenBuffers(1, &m_ibID);
	glGenVertexArrays(1, &m_vaID);

	m_positionData = positionData;
	m_indices = indices;
	
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
Mesh2D::~Mesh2D() {
	glDeleteBuffers(1, &m_vbID);
	glDeleteBuffers(1, &m_ibID);
	glDeleteVertexArrays(1, &m_vaID);
}


void Mesh2D::UpdatePositionVertices(const std::vector<glm::vec2> &positionData) {
	m_positionData = positionData;

	// Configuring vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbID);
	glBufferData(GL_ARRAY_BUFFER, positionData.size() * 2 * sizeof(float), positionData.data(), GL_STATIC_DRAW);

	// Configuring vertex array.
	glBindVertexArray(m_vaID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}
void Mesh2D::UpdateIndices(const std::vector<unsigned int> &indices) {
	m_indices = indices;

	// Configuring index buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}


bool Mesh2D::isValidIndices() const {
	// if any of the indices is greater than the amount of vertices then false.
	for (int i = 0; i < m_indices.size(); i++) {
		if (m_indices[i] > (m_positionData.size() - 1)) return false;
	}
	return true;
}


size_t Mesh2D::GetIndicesCount() const {
	return m_indices.size();
}
size_t Mesh2D::GetVertexCount() const {
	return m_positionData.size();
}

void Mesh2D::BindIndexBuffer() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibID);
}
void Mesh2D::BindVAO() const {
	glBindVertexArray(m_vaID);
}


bool Mesh2D::operator==(const Mesh2D &rhs) const {
	return *(this) != rhs;
}
bool Mesh2D::operator!=(const Mesh2D &rhs) const {
	if (m_positionData != rhs.m_positionData || m_indices != rhs.m_indices) return true;
	return false;
}


