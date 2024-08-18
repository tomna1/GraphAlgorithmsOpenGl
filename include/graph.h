#ifndef GRAPH___H
#define GRAPH___H

#include "grid.h"

// Each node may have a theoretically unlimited amount of edges. Each edge
// tells the other node that a node is connected to and the weighting between
// each nodes.
typedef struct Edge {
	Node *connectedNode;
	unsigned int weight;

} Edge;

// Each node represents a specific tile
typedef struct Node {
	Tile tile;
	
	
} Node;





#endif
