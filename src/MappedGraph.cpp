#include "MappedGraph.h"


// Initialises a graph with no nodes and no edges.
MappedGraph::MappedGraph() {
	m_nodes = {};
	m_edges = {};
}
// Initialises a graph with the nodes in the list.
MappedGraph::MappedGraph(const std::vector<GraphNode>& nodes)
	: m_nodes(nodes)
{}
// Initialises a graph with nodes and edges.
MappedGraph::MappedGraph(const std::vector<GraphNode> &nodes,
	const std::vector<std::list<std::pair<GraphNode, int>>> &edges)
	: m_nodes(nodes), m_edges(edges)
{
}

MappedGraph::~MappedGraph() {
	// TODO: THIS.
}

int MappedGraph::getNodeIndex(const GraphNode &node) {
	for (int i = 0; i < m_nodes.size(); i++) {
		if (m_nodes[i] == node) {
			return i;
		}
	}
	return -1;
}

int MappedGraph::getNodeCount() {
	return m_nodes.size();
}
int MappedGraph::getEdgeCount() {
	int edgeCount = 0;
	for (int i = 0; i < m_edges.size(); i++) {
		edgeCount += m_edges[i].size();
	}
	return edgeCount;
}

bool MappedGraph::addNode(const GraphNode &node) {
	m_nodes.push_back(node);
	m_edges.push_back({});
	return true;
}
bool MappedGraph::addEdge(const GraphNode &node, const GraphNode &rhs, int weight) {

}

bool addNodes(const std::vector<GraphNode> &nodes);
bool addEdges(const std::vector<std::list<std::pair<GraphNode, int>>> &edges);

bool hasNode(const GraphNode &);
bool hasEdge(const GraphNode &, const GraphNode &);

// Removes a nodes and all edges associated with that node.
bool removeNode(const GraphNode &);
// Removes an edge between 2 nodes.
bool removeEdge(const GraphNode &, const GraphNode &);
// Changes the edge weight of an edge between 2 nodes. Requires there to 
// already be an edge between 2 nodes.
bool changeEdgeWeight(const GraphNode &, const GraphNode &, int weight);
// Gets the weight between of an edge between 2 nodes. If there is no edge
// then will return -1.
int getEdgeWeight(const GraphNode &, const GraphNode &);

// Returns the amount of edges a Node has.
int countConnections(const GraphNode &);

// Returns a list of nodes which indicate the shortest path between 2 nodes.
// A indicates this algorithm is the A* algorithm
std::list<GraphNode> findShortestPathA(const GraphNode &start, const GraphNode &end);

// Returns a list of nodes which indicates the shortest path between 2 nodes.
// D indicates this uses Djikstra's shortest path algorithm.
std::list<GraphNode> findShortestPathD(const GraphNode &start, const GraphNode &end);

