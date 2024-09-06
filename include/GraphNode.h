#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexArray.h"
#include "IndexBuffer.h"


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

	bool operator==(const GraphNode &rhs);
	bool operator!=(const GraphNode &rhs);

	// Set the x value of the node to a certain value.
	bool SetX(int x);
	// Set the y value of the node to a certain value.
	bool SetY(int y);

	// Get the x value of the node.
	int GetX() const;
	// Get the y value of the node.
	int GetY() const;

	// Sets the vertex array of the graphnode.
	void SetVertexArray(const VertexArray &va);
	// Sets the index buffer of the graphnode.
	void SetIndexBuffer(const IndexBuffer &ib);

	// Gets the Vertex Array currently being used by the graphnode. Returns 
	// nullptr if a vertex array is not being used.
	VertexArray &GetVertexArray();
	// Gets the IndexBuffer stored by the graphnode. Returns nullptr if a
	// index buffer is not being used.
	IndexBuffer &GetIndexBuffer();

	// Returns the distance to another node. Calculated using pythagoras'
	// theorem
	int DistanceToNode(const GraphNode&) const;
	// Returns the distance to a point. Calculated using pythagoras' theorem.
	int DistanceToPoint(int x, int y) const;
	// Prints out a Node to the standard output. Example: Node(1, 2) where 1
	// is the x coordinate of the node and 2 is the y coordinate.
	void PrintNode() const;

	// Uses the position coordinate of the graphnode to generate a model 
	// matrix.
	glm::mat4 GenerateModelMatrix() const;
};

#endif