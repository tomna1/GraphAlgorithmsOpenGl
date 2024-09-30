#ifndef MAPPED_GRAPH_H
#define MAPPED_GRAPH_H

#include <vector>
#include <utility>
#include <map>

#include "GraphNode.h"

/**
* A graph of nodes and edges where the nodes have a mapped position (x and y
* coordinate in a 2D space. 
*/
class MappedGraph {
private:
	typedef struct {
		std::string connectedNodeName;
		int weight;
	} Edge;
	
	// Each struct contains a node and a list of edges associated with that node.
	// The size_t in edges in the index of the node in m_nodes it is connected
	// to and the int is the weight of the edge.
	typedef struct {
		GraphNode node;
		std::vector<Edge> edges;
	} Node;

	// All the nodes associated with the graph.
	std::map<std::string, Node> m_nodes;

public:
	// Initialises a graph with no nodes and no edges.
	MappedGraph();
	// Copy constructor.
	MappedGraph(const MappedGraph &rhs);
	// Destructor.
	~MappedGraph();
private:
	// Returns the node associated with the name.
	GraphNode GetNode(std::string &name) const;
public:
	// Returns the amount of nodes stored in the graph. O(n)
	size_t GetNodeCount() const;
	// Returns the amount of edges stored in the graph. O(n)
	size_t GetEdgeCount() const;
	// Gets the amount of edges a specific node in the graph has. Will return 
	// -1 if the node is not found in the graph. O(n)
	size_t GetEdgeCount(const GraphNode &node) const;
	// Gets the weight between of an edge between 2 nodes. If there is no edge
	// then will return -1. O(n)
	int GetEdgeWeight(const GraphNode &node, const GraphNode &rhs) const;

	// Checks if the graph has a certain node. O(n)
	bool HasNode(const GraphNode &node) const;
	bool HasNode(const std::string &name) const;
	// Checks if the graph has a certain edge between nodes. O(n)
	bool HasEdge(const GraphNode &node, const GraphNode &rhs) const;
	// Checks if the graph has a node at a certain point.
	bool HasNodeAtPoint(int x, int y) const;

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
	// Adds a node to the graph at the specified x,y coordinate.
	// bool AddNodeAtPoint(int x, int y);

	// Removes a nodes and all edges associated with that node.
	bool RemoveNode(const GraphNode &node);
	// Removes an edge between 2 nodes. All edges are bidirectional so will
	// remove the edge from both specified nodes.
	bool RemoveEdge(const GraphNode &node, const GraphNode &rhs);
	bool RemoveEdge(const GraphNode &node, const std::string &rhs);
	// Changes the edge weight of an edge between 2 nodes. Requires there to 
	// already be an edge between 2 nodes.
	bool ChangeEdgeWeight(const GraphNode &node, const GraphNode &rhs, const int newWeight);


	// TODO: CHANGE THESE TO USE THE INSERTION OPERATOR INSTEAD

	// Print out and edge to the standard output. Example: Edge(Node(1, 2), 5)
	// where 1 is the x coordinate of the node, 2 is the y coordinate and 5 is 
	// the edge weight
	void PrintEdge(const std::pair<int, int> &edge) const;
	// Print out a node to the standard output. Example: Node(5, 6) where 5 is
	// the x coordinate of the node and 6 is the y coordinate.
	void PrintNodes() const;
	// Prints out all the edges of a certain node in the graph. Example:
	// Printing Edges of Node(3, 3)
	// Edge(Node(1, 2), 5)
	// Edge(Node(6, 8), 34)
	void PrintEdges(const GraphNode &node) const;
	// Prints out every single edge associated with the graph. Example:
	// Printing all nodes of graph
	// Printing Edges of Node(1, 1)
	// Edge(Node(5, 6), 4)
	// Printing Edges of Node(5, 6)
	// Edge(Node(1, 1), 4)
	void PrintAllEdges() const;

	// Returns the positions of all nodes in the graph.
	std::vector<GraphNode> GetAllNodes() const;

	// Returns a list of nodes which indicate the shortest path between 2 nodes.
	// A indicates this algorithm is the A* algorithm
	std::vector<GraphNode> FindShortestPathA(const GraphNode &start, const GraphNode &end) const;

	// Returns a list of nodes which indicates the shortest path between 2 nodes.
	// D indicates this uses Djikstra's shortest path algorithm.
	std::vector<GraphNode> FindShortestPathD(const std::string &start, const std::string &end);
};

#endif