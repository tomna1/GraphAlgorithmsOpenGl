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
	// first node in the nodes dynamic array. The first int in the pair is the 
	// index of the node in the m_nodes array it is connected to and the second int
	// is the edge weight
	std::vector<std::vector<std::pair<int, int>>> m_edges;
public:
	// Initialises a graph with no nodes and no edges.
	MappedGraph();
	// Initialises a graph with the nodes in the list.
	MappedGraph(const std::vector<GraphNode> &nodes);
	// Initialises a graph with nodes and edges.
	MappedGraph(const std::vector<GraphNode> &nodes,
		const std::vector<std::vector<std::pair<int, int>>> &edges);
	// Copy constructor.
	MappedGraph(const MappedGraph &rhs);
	// Destructor.
	~MappedGraph();
private:
	// Returns the index of the specified node in the m_nodes array. Will
	// return -1 if not found. O(n)
	int GetNodeIndex(const GraphNode &node);
	// Returns the index of the specified edge in the m_edges array. Returns 
	// -1 if the edge has not been found. O(n)
	int GetEdgeIndex(const GraphNode &node, const GraphNode &rhs);
	// Returns the node at m_nodes[index]. NO ERROR
	// CHECKING SO MAKE SURE TO INPUT CORRECT INDEX.
	GraphNode &GetNode(const int index);
	// Returns the node at m_edges[nodeIndex][edgeIndex]. NO ERROR CHECKING SO MAKE SURE TO INPUT CORRECT
	// INDEX.
	GraphNode &GetNode(const int nodeIndex, const int edgeIndex);
public:
	// Returns the amount of nodes stored in the graph. O(n)
	int GetNodeCount();
	// Returns the amount of edges stored in the graph. O(n)
	int GetEdgeCount();
	// Gets the amount of edges a specific node in the graph has. Will return 
	// -1 if the node is not found in the graph. O(n)
	int GetEdgeCount(const GraphNode &node);
	// Gets the weight between of an edge between 2 nodes. If there is no edge
	// then will return -1. O(n)
	int GetEdgeWeight(const GraphNode &node, const GraphNode &rhs);

	// Checks if the graph has a certain node. O(n)
	bool HasNode(const GraphNode &node);
	// Checks if the graph has a certain edge between nodes. O(n)
	bool HasEdge(const GraphNode &node, const GraphNode &rhs);
private:
	// Checks if the graph has a certain edge between a node and
	// m_nodes[nodeIndex].
	bool HasEdge(const GraphNode &node, int nodeIndex);

public:
	// Adds Node to the graph. Returns true if nodes has been successfully added
	// and false if the nodes has failed to be added. O(n) (checks if the node 
	// has already been added)
	bool AddNode(const GraphNode &node);
	// Adds a bidirectional edge between 2 nodes. Returns true if the edge has 
	// been successfully added and false if the edge has failed to be added.
	// Both specified nodes have to be in the graph for the edge to be added.
	// O(n) (checks if nodes are already in graph)
	bool AddEdge(const GraphNode &node, const GraphNode &rhs, int weight);
	// Adds all the nodes to the graph. Will not add duplicate nodes. Returns
	// true if all nodes not already in the graph have been added and false
	// if all nodes not already in the graph have not all been successfully
	// added. 
	bool AddNodes(const std::vector<GraphNode> &nodes);
	// Adds all the edges to a node.
	bool AddEdges(const GraphNode &node, const std::vector<std::pair<int, int>> &edges);

	// Removes a nodes and all edges associated with that node.
	bool RemoveNode(const GraphNode &node);
	// Removes an edge between 2 nodes. All edges are bidirectional so will
	// remove the edge from both specified nodes.
	bool RemoveEdge(const GraphNode &node, const GraphNode &rhs);
	// Changes the edge weight of an edge between 2 nodes. Requires there to 
	// already be an edge between 2 nodes.
	bool ChangeEdgeWeight(const GraphNode &node, const GraphNode &rhs, const int newWeight);


	// Print out and edge to the standard output. Example: Edge(Node(1, 2), 5)
	// where 1 is the x coordinate of the node, 2 is the y coordinate and 5 is 
	// the edge weight
	void PrintEdge(const std::pair<int, int> &edge);
	// Print out a node to the standard output. Example: Node(5, 6) where 5 is
	// the x coordinate of the node and 6 is the y coordinate.
	void PrintNodes();
	// Prints out all the edges of a certain node in the graph. Example:
	// Printing Edges of Node(3, 3)
	// Edge(Node(1, 2), 5)
	// Edge(Node(6, 8), 34)
	void PrintEdges(const GraphNode &node);
	// Prints out every single edge associated with the graph. Example:
	// Printing all nodes of graph
	// Printing Edges of Node(1, 1)
	// Edge(Node(5, 6), 4)
	// Printing Edges of Node(5, 6)
	// Edge(Node(1, 1), 4)
	void PrintAllEdges();

	// Returns a list of nodes which indicate the shortest path between 2 nodes.
	// A indicates this algorithm is the A* algorithm
	std::vector<GraphNode> FindShortestPathA(const GraphNode &start, const GraphNode &end);

	// Returns a list of nodes which indicates the shortest path between 2 nodes.
	// D indicates this uses Djikstra's shortest path algorithm.
	std::vector<GraphNode> FindShortestPathD(GraphNode &start, const GraphNode &end);
};

#endif