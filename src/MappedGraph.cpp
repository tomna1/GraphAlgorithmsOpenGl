#include <iostream>

#include "MappedGraph.h"


// Initialises a graph with no nodes and no edges.
MappedGraph::MappedGraph() {
	m_nodes = {};
	m_edges = {};
}
// Initialises a graph with the nodes in the array and no edges.
MappedGraph::MappedGraph(const std::vector<GraphNode> &nodes)
	: m_nodes(nodes)
{ }
// Initialises a graph with nodes and edges.
MappedGraph::MappedGraph(const std::vector<GraphNode> &nodes,
	const std::vector<std::vector<std::pair<GraphNode, int>>> &edges)
	: m_nodes(nodes), m_edges(edges)
{ }
MappedGraph::MappedGraph(const MappedGraph &rhs) {
	m_nodes = rhs.m_nodes;
	m_edges = rhs.m_edges;
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
int MappedGraph::getEdgeIndex(const GraphNode &node, const GraphNode &rhs) {
	int index = getNodeIndex(node);
	if (index == -1) {
		return -1;
	}
	
	for (int i = 0; i < m_edges[index].size(); i++) {
		if (std::get<0>(m_edges[index][i]) == rhs) {
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
	// Push a new empty array to the end of the array.
	m_edges.push_back({});
	return true;
}
bool MappedGraph::addEdge(const GraphNode &node, const GraphNode &to, int weight) {
	int index = getNodeIndex(node);
	if (index == -1) {
		return false;
	}
	m_edges[index].push_back({ to, weight });
	return true;
}

bool MappedGraph::addNodes(const std::vector<GraphNode> &nodes) {
	for (int i = 0; i < nodes.size(); i++) {
		m_nodes.push_back(nodes[i]);
		m_edges.push_back({});
	}
	return true;
}
bool MappedGraph::addEdges(const GraphNode &node, const std::vector<std::pair<GraphNode, int>> &edges) {
	int index = getNodeIndex(node);
	if (index == -1) {
		return false;
	}

	for (int i = 0; i < edges.size(); i++) {
		if (!hasEdge(node, edges[i].first)) {
			m_edges[index].push_back(edges[i]);
		}
		else return false;
	}
	return true;
}

bool MappedGraph::hasNode(const GraphNode& node) {
	for (int i = 0; i < m_nodes.size(); i++) {
		if (m_nodes[i] == node) {
			return true;
		}
	}
	return false;
}
bool MappedGraph::hasEdge(const GraphNode& node, const GraphNode& rhs) {
	int index = getNodeIndex(node);
	if (index == -1) {
		return false;
	}
	for (int i = 0; i < m_edges[index].size(); i++) {
		if (std::get<0>(m_edges[index][i]) == rhs) {
			return true;
		}
	}
	return false;
}

bool MappedGraph::removeNode(const GraphNode& node) {
	int index = getNodeIndex(node);
	if (index == -1) {
		return false;
	}
	std::vector<GraphNode>::iterator it_nodes = m_nodes.begin();
	m_nodes.erase(it_nodes + index);

	std::vector<std::vector<std::pair<GraphNode, int>>>::iterator it_edges = m_edges.begin();
	m_edges.erase(it_edges + index);
	
	return true;
}
bool MappedGraph::removeEdge(const GraphNode& node, const GraphNode& rhs) {
	int index = getNodeIndex(node);
	if (index == -1) {
		return false;
	}
	if (!hasEdge(node, rhs)) {
		return false;
	}

	int edgeIndex = getEdgeIndex(node, rhs);
	std::vector<std::pair<GraphNode, int>>::iterator it = m_edges[index].begin();
	m_edges[index].erase(it + edgeIndex);
	return true;
}

bool MappedGraph::changeEdgeWeight(const GraphNode &node, const GraphNode &rhs, const int newWeight) {
	int index = getNodeIndex(node);
	if (index == -1) {
		return false;
	}
	
	int edgeIndex = getEdgeIndex(node, rhs);
	if (edgeIndex == -1) {
		return false;
	}

	std::pair<GraphNode, int> newPair = std::make_pair(rhs, newWeight);
	m_edges[index][edgeIndex] = newPair;
	return true;
}

int MappedGraph::getEdgeWeight(const GraphNode &node, const GraphNode &rhs) {
	int index = getNodeIndex(node);
	if (index == -1) {
		return -1;
	}

	int edgeIndex = getEdgeIndex(node, rhs);
	if (edgeIndex == -1) {
		return -1;
	}

	return m_edges[index][edgeIndex].second;
}

int MappedGraph::countConnections(const GraphNode &node) {
	int index = getNodeIndex(node);
	if (index == -1) {
		return -1;
	}

	return m_edges[index].size();
}

void MappedGraph::printEdge(const std::pair<GraphNode, int> &edge) {
	std::cout << "Edge(Node(" << edge.first.getX() << ',' << edge.first.getY()
		<< "), " << edge.second << ')' << std::endl;
}
void MappedGraph::printNodes() {
	std::cout << "Printing nodes of graph." << std::endl;
	for (int i = 0; i < m_nodes.size(); i++) {
		m_nodes[i].printNode();
	}
}
void MappedGraph::printEdges(const GraphNode &node) {
	int index = getNodeIndex(node);
	if (index == -1) {
		return;
	}
	
	std::cout << "Printing edges of";
	node.printNode();

	for (int i = 0; i < m_edges[index].size(); i++) {
		printEdge(m_edges[index][i]);
	}
}
void MappedGraph::printAllEdges() {
	std::cout << "Printing all nodes of the graph" << std::endl;
	for (int i = 0; i < m_edges.size(); i++) {
		std::cout << "=============================" << std::endl;
		m_nodes[i].printNode();
		std::cout << "=============================" << std::endl;
		for (int j = 0; j < m_edges[i].size(); j++) {
			printEdge(m_edges[i][j]);
		}
	}
}

// Returns a list of nodes which indicate the shortest path between 2 nodes.
// A indicates this algorithm is the A* algorithm
//std::vector<GraphNode> MappedGraph::findShortestPathA(const GraphNode &start, const GraphNode &end) {
	// TODO: THIS
//}

// Returns a list of nodes which indicates the shortest path between 2 nodes.
// D indicates this uses Djikstra's shortest path algorithm.
//std::vector<GraphNode> MappedGraph::findShortestPathD(const GraphNode &start, const GraphNode &end) {
	// TODO: THIS
//}

