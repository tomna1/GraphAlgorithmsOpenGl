#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <ostream>

// A node with x and y values which represents the position of the node
// on a 2D plane.
class GraphNode {
private:
	int m_x;
	int m_y;
	std::string m_name;
	
public:
	GraphNode();
	// Creates a node with x = 0 and y = 0.
	GraphNode(std::string &name);
	// Creates a node with the respective x and y values.
	GraphNode(std::string &name, int x, int y);

	// Two graphnodes are equal if they have the same coordinates and same name.
	bool operator==(const GraphNode &rhs) const;
	// Graphnodes are not equal if they have different coordinates and different
	// name.
	bool operator!=(const GraphNode &rhs) const;

	// Set the x value of the node to a certain value.
	void SetX(int x);
	// Set the y value of the node to a certain value.
	void SetY(int y);

	// Get the x value of the node.
	int GetX() const;
	// Get the y value of the node.
	int GetY() const;

	void SetName(std::string &name);
	std::string GetName() const;

	// Returns the distance to another node. Calculated using pythagoras'
	// theorem
	int DistanceToNode(const GraphNode&) const;
	// Returns the distance to a point. Calculated using pythagoras' theorem.
	int DistanceToPoint(int x, int y) const;
};

/*
std::ostream &operator<<(std::ostream &os, const GraphNode &rhs) {
	os << "Node(" << rhs.GetX() << ", " << rhs.GetY() << ")" << std::endl;
	return os;
}*/


#endif