#include <cmath>

#include "GraphNode.h"

GraphNode::GraphNode() {
	m_name = "";
	m_x = 0;
	m_y = 0;
}
GraphNode::GraphNode(std::string &name) {
	m_name = name;
	m_x = 0;
	m_y = 0;
}
GraphNode::GraphNode(std::string &name, int x, int y) {
	m_name = name;
	m_x = x;
	m_y = y;
}

bool GraphNode::operator==(const GraphNode &rhs) const {
	if ((m_x == rhs.m_x) && (m_y == rhs.m_y) && (m_name == rhs.m_name)) {
		return true;
	}
	return false;
}
bool GraphNode::operator!=(const GraphNode &rhs) const {
	if ((m_x != rhs.m_x) || (m_y != rhs.m_y) || (m_name != rhs.m_name)) {
		return true;
	}
	return false;
}

void GraphNode::SetX(int x) {
	m_x = x;
}
void GraphNode::SetY(int y) {
	m_y = y;
}

int GraphNode::GetX() const {
	return m_x;
}
int GraphNode::GetY() const {
	return m_y;
}

void GraphNode::SetName(std::string &name) {
	m_name = name;
}
std::string GraphNode::GetName() const {
	return m_name;
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



