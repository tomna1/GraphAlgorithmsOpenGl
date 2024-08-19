#ifndef MAPPED_GRAPH_H
#define MAPPED_GRAPH_H

#include <list>

#include "GraphNode.h"

class MappedGraph {
private:
	std::list<GraphNode> m_nodes;
	std::list<std::pair<std::pair<GraphNode, GraphNode>, int>> m_edges;
public:
	MappedGraph();
	MappedGraph(std::list<GraphNode>);
	MappedGraph(std::list<GraphNode> &nodes,
		std::list<std::pair<std::pair<GraphNode, GraphNode>, int>> edges);
	~MappedGraph();

	int getNodeCount();
	int getEdgeCount();

	bool addNode();
	bool addEdge();

	bool removeNode();
	bool removeEdge();

	bool hasNode();
	bool hasEdge(GraphNode, GraphNode);

	int getEdgeWeight(GraphNode, GraphNode);

	std::list<GraphNode> findShortestPath(GraphNode, GraphNode);
};






#endif
