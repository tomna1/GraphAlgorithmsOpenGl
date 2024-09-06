#include <cmath>
#include <iostream>

#include "GraphNode.h"

VertexArray *GraphNode::va = nullptr;
IndexBuffer *GraphNode::ib = nullptr;

GraphNode::GraphNode() {
	m_x = 0;
	m_y = 0;

	if (va == nullptr) {
		va = new VertexArray();
		// TODO: SET VERTEX ARRAYT AND INDEX BUFFER TO CORRECT VALUES.
	}
}
GraphNode::GraphNode(int x, int y) {
	m_x = x;
	m_y = y;
}

bool GraphNode::operator==(const GraphNode &rhs) {
	if ((m_x == rhs.m_x) && (m_y == rhs.m_y)) {
		return true;
	}
	return false;
}
bool GraphNode::operator!=(const GraphNode &rhs) {
	if ((m_x != rhs.m_x) || (m_y != rhs.m_y)) {
		return true;
	}
	return false;
}

bool GraphNode::SetX(int x) {
	m_x = x;
	return true;
}
bool GraphNode::SetY(int y) {
	m_y = y;
	return true;
}

int GraphNode::GetX() const {
	return m_x;
}
int GraphNode::GetY() const {
	return m_y;
}

int GraphNode::DistanceToNode(const GraphNode& rhs) const {
	// Use pythagoras' theorem. a^^2 + b^^2 = c^^2

	int xDistance = abs(m_x - rhs.m_x);
	int yDistance = abs(m_y - rhs.m_y);
	return std::sqrt(pow(xDistance, 2) + pow(yDistance, 2));
}
int GraphNode::DistanceToPoint(int x, int y) const {
	// Use pythagoras' theorem. a^^2 + b^^2 = c^^2

	int xDistance = abs(m_x - x);
	int yDistance = abs(m_y - y);
	return std::sqrt(pow(xDistance, 2) + pow(yDistance, 2));
}

void GraphNode::PrintNode() const {
	std::cout << "Node(" << m_x << ", " << m_y << ')' << std::endl;
}

glm::mat4 GraphNode::GenerateModelMatrix() const {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(m_x, m_y, 0));
	return model;
}

