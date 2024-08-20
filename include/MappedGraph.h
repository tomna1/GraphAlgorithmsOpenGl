#ifndef MAPPED_GRAPH_H
#define MAPPED_GRAPH_H

#include <list>

#include "GraphNode.h"

/**
* A graph of nodes and edges where the nodes have a mapped position (x and y
* coordinate in a 2D space.
* 
*/
class MappedGraph {
private:
	std::list<GraphNode> m_nodes;
	std::list<std::pair<std::pair<GraphNode, GraphNode>, int>> m_edges;
public:
	// Initialises a graph with no nodes and no edges.
	MappedGraph();
	// Initialises a graph with the nodes in the list.
	MappedGraph(std::list<GraphNode>);
	// Initialises a graph with nodes and edges.
	MappedGraph(std::list<GraphNode> &nodes,
		std::list<std::pair<std::pair<GraphNode, GraphNode>, int>> edges);
	~MappedGraph();

	// Returns the amount of nodes stored in the graph.
	int getNodeCount();
	// Returns the amount of edges stored in the graph.
	int getEdgeCount();

	// Adds Node to the graph. Returns true if nodes has been successfully added
	// and false if the nodes has failed to be added.
	bool addNode(GraphNode&);
	// Adds an edge between 2 nodes. Returns true if the edge has been successfully
	// added and false if the edge has failed to be added.
	bool addEdge(GraphNode&, GraphNode&, int weight);

	// Checks if the graph has a certain node
	bool hasNode(GraphNode &);
	// Checks if the graph has a certain edge between nodes.
	bool hasEdge(GraphNode &, GraphNode &);

	// Removes a nodes and all edges associated with that node.
	bool removeNode();
	// Removes an edge between 2 nodes.
	bool removeEdge();
	// Changes the edge weight of an edge between 2 nodes. Requires there to 
	// already be an edge between 2 nodes.
	bool changeEdgeWeight(GraphNode&, GraphNode&, int weight);
	// Gets the weight between of an edge between 2 nodes. If there is no edge
	// then will return -1.
	int getEdgeWeight(GraphNode&, GraphNode&);

	// Returns the amount of edges a Node has.
	int countConnections(GraphNode&);
	
	// Returns a list of nodes which indicate the shortest path between 2 nodes.
	// A indicates this algorithm is the A* algorithm
	std::list<GraphNode> findShortestPathA(GraphNode, GraphNode);
};






#endif
