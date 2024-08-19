#ifndef GRAPH___H
#define GRAPH___H

#include <list>

#include "GraphNode.h"

class Graph {
private:
	std::list<GraphNode> nodes_;
	std::list<std::pair<GraphNode, GraphNode>> edges_;
public:
	Graph(std::list<GraphNode> &nodes,
		std::list<std::pair<std::pair<GraphNode, GraphNode>, int>> edges);
	~Graph();

	int getNodeCount();
	int getEdgeCount();

	bool addNode();
	bool addEdge();

	bool removeNode();
	bool removeEdge();

	std::list<GraphNode> findShortestPath(GraphNode, GraphNode);

	bool hasNode();
	bool hasConnection(GraphNode, GraphNode);
};






#endif
