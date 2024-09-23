#include "Model.h"


Model2D::Model2D() {
	m_meshName = "";
	m_position = { 0,  0 };
	m_isSelected = false;
	m_scale = 1;
}

Model2D::Model2D(std::string &meshName, float posX, float posY) {
	m_meshName = meshName;
	m_position = { posX, posY };
	m_isSelected = false;
	m_scale = 1;
}


void Model2D::Select() {
	m_isSelected = true;
}
void Model2D::DeSelect() {
	m_isSelected = false;
}
bool Model2D::isSelected() const {
	return m_isSelected;
}


void Model2D::SetPos(float x, float y) {
	m_position = { x, y };
}
float Model2D::GetX() const {
	return m_position.x;
}
float Model2D::GetY() const {
	return m_position.y;
}
glm::mat4 Model2D::GetModelMatrix() const {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(m_position.x, m_position.y, 0));
	return model;
}

void Model2D::SetMeshName(const std::string &name) {
	m_meshName = name;
}

std::string Model2D::GetMeshName() const {
	return m_meshName;
}


bool Model2D::operator==(const Model2D &rhs) const {
	return !(*(this) != rhs);
}
bool Model2D::operator!=(const Model2D &rhs) const {
	if (m_position != rhs.m_position || m_meshName != rhs.m_meshName) return true;
	return false;
}



