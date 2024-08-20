#ifndef GRAPHNODE_H
#define GRAPHNODE_H

// A node with x and y values which represents the position of the node
// on a 2D plane.
class GraphNode {
private:
	int m_x;
	int m_y;

public:
	// Creates a node with x = 0 and y = 0.
	GraphNode();
	// Creates a node with the respective x and y values.
	GraphNode(int x, int y);

	bool operator==(const GraphNode& rhs);
	bool operator!=(const GraphNode &rhs);

	// Set the x value of the node to a certain value.
	bool setX(int x);
	// Set the y value of the node to a certain value.
	bool setY(int y);

	// Get the x value of the node.
	int getX();
	// Get the y value of the node.
	int getY();

	// Returns the distance to another node. Calculated using pythagoras'
	// theorem
	int distanceToNode(const GraphNode&);
	// Returns the distance to a point. Calculated using pythagoras' theorem.
	int distanceToPoint(int x, int y);
};

#endif