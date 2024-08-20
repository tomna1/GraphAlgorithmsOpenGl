#include <cmath>

#include "GraphNode.h"

GraphNode::GraphNode() {
	m_x = 0;
	m_y = 0;
}
GraphNode::GraphNode(int x, int y) {
	m_x = x;
	m_y = y;
}

bool GraphNode::setX(int x) {
	m_x = x;
	return true;
}
bool GraphNode::setY(int y) {
	m_y = y;
	return true;
}

int GraphNode::getX() {
	return m_x;
}
int GraphNode::getY() {
	return m_y;
}


int GraphNode::distanceToNode(const GraphNode& rhs) {
	// Use pythagoras' theorem. a^^2 + b^^2 = c^^2

	int xDistance = abs(m_x - rhs.m_x);
	int yDistance = abs(m_y - rhs.m_y);
	return std::sqrt(pow(xDistance, 2) + pow(yDistance, 2));
}
int GraphNode::distanceToPoint(int x, int y) {
	// Use pythagoras' theorem. a^^2 + b^^2 = c^^2

	int xDistance = abs(m_x - x);
	int yDistance = abs(m_y - y);
	return std::sqrt(pow(xDistance, 2) + pow(yDistance, 2));
}

