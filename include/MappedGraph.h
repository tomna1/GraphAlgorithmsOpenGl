#ifndef MAPPED_GRAPH_H
#define MAPPED_GRAPH_H

#include <vector>
#include <utility>

#include "GraphNode.h"

/**
* A graph of nodes and edges where the nodes have a mapped position (x and y
* coordinate in a 2D space.
* 
*/
class MappedGraph {
private:
	// All the nodes associated with the graph.
	std::vector<GraphNode> m_nodes;
	// Each node has a list which contains what other nodes it is connected to
	// and the weight of each connection. The first list of edges relates to the
	// first node in the nodes dynamic array.
	std::vector<std::vector<std::pair<GraphNode, int>>> m_edges;
public:
	// Initialises a graph with no nodes and no edges.
	MappedGraph();
	// Initialises a graph with the nodes in the list.
	MappedGraph(const std::vector<GraphNode>&);
	// Initialises a graph with nodes and edges.
	MappedGraph(const std::vector<GraphNode>& nodes,
		const std::vector<std::vector<std::pair<GraphNode, int>>>& edges);
	// Copy constructor.
	MappedGraph(const MappedGraph &rhs);
	// Destructor.
	~MappedGraph();
private:
	// Returns the index of the specified node in the m_nodes array. Will
	// return -1 if not found.
	int getNodeIndex(const GraphNode &node);
	// Returns the index of the specified edge in the vector which contains 
	// the pairs of graphnodes and edgeweights. Returns -1 if the edge
	// has not been found.
	int getEdgeIndex(const GraphNode &node, const GraphNode &rhs);
public:
	// Returns the amount of nodes stored in the graph.
	int getNodeCount();
	// Returns the amount of edges stored in the graph.
	int getEdgeCount();

	// Adds Node to the graph. Returns true if nodes has been successfully added
	// and false if the nodes has failed to be added.
	bool addNode(const GraphNode&);
	// Adds an edge between 2 nodes. Returns true if the edge has been successfully
	// added and false if the edge has failed to be added.
	bool addEdge(const GraphNode& node, const GraphNode& rhs, int weight);

	// Adds all the nodes to the graph. Will not add duplicate nodes. Returns
	// true if all nodes not already in the graph have been added and false
	// if all nodes not already in the graph have not all been successfully
	// added.
	bool addNodes(const std::vector<GraphNode> &nodes);
	// Adds all the edges to a node.
	bool addEdges(const GraphNode &node, const std::vector<std::pair<GraphNode, int>>& edges);

	// Checks if the graph has a certain node
	bool hasNode(const GraphNode&);
	// Checks if the graph has a certain edge between nodes.
	bool hasEdge(const GraphNode&, const GraphNode&);

	// Removes a nodes and all edges associated with that node.
	bool removeNode(const GraphNode&);
	// Removes an edge between 2 nodes.
	bool removeEdge(const GraphNode&, const GraphNode&);
	// Changes the edge weight of an edge between 2 nodes. Requires there to 
	// already be an edge between 2 nodes.
	bool changeEdgeWeight(const GraphNode&, const GraphNode&, const int newWeight);
	// Gets the weight between of an edge between 2 nodes. If there is no edge
	// then will return -1.
	int getEdgeWeight(const GraphNode&, const GraphNode&);

	// Returns the amount of edges a Node has.
	int countConnections(const GraphNode&);
	void printEdge(const std::pair<GraphNode, int> &edge);
	void printNodes();
	void printEdges(const GraphNode &node);
	void printAllEdges();
	
	// Returns a list of nodes which indicate the shortest path between 2 nodes.
	// A indicates this algorithm is the A* algorithm
	std::vector<GraphNode> findShortestPathA(const GraphNode& start, const GraphNode& end);

	// Returns a list of nodes which indicates the shortest path between 2 nodes.
	// D indicates this uses Djikstra's shortest path algorithm.
	std::vector<GraphNode> findShortestPathD(const GraphNode &start, const GraphNode &end);
};






#endif
