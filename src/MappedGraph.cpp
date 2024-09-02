#include <iostream>

#include "MappedGraph.h"

// Initialises a graph with no nodes and no edges.
MappedGraph::MappedGraph() {
	m_nodes = {};
	m_edges = {};
	m_edges.resize(2);
}
// Initialises a graph with the nodes in the array and no edges.
MappedGraph::MappedGraph(const std::vector<GraphNode> &nodes)
	: m_nodes(nodes)
{
	m_edges.resize(2);
}
// Initialises a graph with nodes and edges.
MappedGraph::MappedGraph(const std::vector<GraphNode> &nodes,
	const std::vector<std::vector<std::pair<int, int>>> &edges)
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
		if (m_edges[index][i].first == index) {
			return i;
		}
	}
	return -1;
}
GraphNode &MappedGraph::getNode(const int index) {
	// if (index > m_nodes.size() - 1) return;
	return m_nodes[index];
}
GraphNode &MappedGraph::getNode(const int nodeIndex, const int edgeIndex) {
	// if (nodeIndex > m_nodes.size() - 1) return;
	// if (edgeIndex > m_edges[nodeIndex].size() - 1) return;
	int index = m_edges[nodeIndex][edgeIndex].first;
	return m_nodes[index];
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
int MappedGraph::getEdgeCount(const GraphNode &node) {
	int index = getNodeIndex(node);
	if (index == -1) return -1;

	return m_edges[index].size();
}
int MappedGraph::getEdgeWeight(const GraphNode &node, const GraphNode &rhs) {
	int index = getNodeIndex(node);
	if (index == -1) return -1;

	int edgeIndex = getEdgeIndex(node, rhs);
	if (edgeIndex == -1) return -1;

	return m_edges[index][edgeIndex].second;
}


bool MappedGraph::hasNode(const GraphNode &node) {
	for (int i = 0; i < m_nodes.size(); i++) {
		if (m_nodes[i] == node) return true;
	}
	return false;
}
bool MappedGraph::hasEdge(const GraphNode &node, const GraphNode &rhs) {
	int index = getNodeIndex(node);
	if (index == -1) return false;
	int index2 = getNodeIndex(rhs);
	if (index2 == -1) return false;

	for (int i = 0; i < m_edges[index].size(); i++) {
		if (m_edges[index][i].first == index2) {
			return true;
		}
	}
	return false;
}
bool MappedGraph::hasEdge(const GraphNode &node, int nodeIndex) {
	int index = getNodeIndex(node);
	if (index == -1) return false;

	for (int i = 0; i < m_edges[index].size(); i++) {
		if (m_edges[index][i].first == nodeIndex) return true;
	}
	return false;
}

bool MappedGraph::addNode(const GraphNode &node) {
	m_nodes.push_back(node);

	if (m_nodes.size() >= m_edges.capacity()) {
		m_edges.resize(m_edges.capacity() * 2);
	}
	return true;
}
bool MappedGraph::addEdge(const GraphNode &node, const GraphNode &to, int weight) {
	int index = getNodeIndex(node);
	if (index == -1) return false;

	int index2 = getNodeIndex(to);
	if (index2 == -1) return false;

	m_edges[index].push_back({ index2, weight });
	m_edges[index2].push_back({ index, weight });
	return true;
}
bool MappedGraph::addNodes(const std::vector<GraphNode> &nodes) {
	for (int i = 0; i < nodes.size(); i++) {
		m_nodes.push_back(nodes[i]);
		m_edges.push_back({});
	}
	
	m_edges.resize(m_edges.capacity() + nodes.size());
	return true;
}
bool MappedGraph::addEdges(const GraphNode &node, const std::vector<std::pair<int, int>> &edges) {
	int index = getNodeIndex(node);
	if (index == -1) return false;

	for (int i = 0; i < edges.size(); i++) {
		if (!hasEdge(node, edges[i].first)) {
			m_edges[index].push_back(edges[i]);
		}
		else return false;
	}
	return true;
}


bool MappedGraph::removeNode(const GraphNode &node) {
	int index = getNodeIndex(node);
	if (index == -1) return false;

	// remove all edges associated with the node
	while (m_edges[index].size() > 0) {
		removeEdge(node, getNode(index, 0));
	}

	// remove the node from m_nodes array
	std::vector<GraphNode>::iterator itNodes = m_nodes.begin();
	m_nodes.erase(itNodes + index);

	// remove the node from m_edges array
	std::vector<std::vector<std::pair<int, int>>>::iterator itEdges = m_edges.begin();
	m_edges.erase(itEdges + index);

	return true;
}
bool MappedGraph::removeEdge(const GraphNode &node, const GraphNode &rhs) {
	int index = getNodeIndex(node);
	if (index == -1) return false;

	int index2 = getNodeIndex(rhs);
	if (index2 == -1) return false;

	if (!hasEdge(node, rhs)) {
		return false;
	}

	int edgeIndex = getEdgeIndex(node, rhs);
	std::vector<std::pair<int, int>>::iterator it = m_edges[index].begin();
	m_edges[index].erase(it + edgeIndex);

	int edgeIndex2 = getEdgeIndex(rhs, node);
	it = m_edges[index2].begin();
	m_edges[index2].erase(it + edgeIndex2);

	return true;
}


bool MappedGraph::changeEdgeWeight(const GraphNode &node, const GraphNode &rhs, const int newWeight) {
	int index = getNodeIndex(node);
	if (index == -1) return false;

	int index2 = getNodeIndex(rhs);
	if (index2 == -1) return false;

	int edgeIndex = getEdgeIndex(node, rhs);
	if (edgeIndex == -1) return false;

	std::pair<int, int> newPair = std::make_pair(index2, newWeight);
	m_edges[index][edgeIndex] = newPair;

	int edgeIndex2 = getEdgeIndex(rhs, node);
	std::pair<int, int> newPair2 = std::make_pair(index, newWeight);
	m_edges[index2][edgeIndex2] = newPair2;

	return true;
}

void MappedGraph::printEdge(const std::pair<int, int> &edge) {
	
	std::cout << "Edge(Node(" << m_nodes[edge.first].getX() << ", " << m_nodes[edge.first].getY()
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
	if (index == -1) return;

	std::cout << "Printing edges of ";
	node.printNode();

	for (int i = 0; i < m_edges[index].size(); i++) {
		printEdge(m_edges[index][i]);
	}
}
void MappedGraph::printAllEdges() {
	std::cout << "Printing all Edges of the graph" << std::endl;
	for (int i = 0; i < m_nodes.size(); i++) {
		std::cout << "Printing Edges of ";
		m_nodes[i].printNode();
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



// Node information used exclusively for Djikstras algorithm. Contains the
// distance from the start, if the node is visted or not and the index of
// the previous node.
struct DNode {
	// The distance this node if from the starting node.
	int distanceFromStart;
	// has the node been visited or not.
	bool isVisited;
	// the index of the previous node in the m_nodes array. -1 if there is
	// no previous node.
	int previousNodeIndex;
};
// Function used to get the index of the shortest from the start, unvisited 
// node. Returns -1 if there are no available options.
int getShortestUnvistedIndex(std::vector<DNode> vec) {
	int output = -1;
	int currentShortest = INT_MAX;
	for (int i = 0; i < vec.size(); i++) {
		if ((vec[i].isVisited == false) && vec[i].distanceFromStart < currentShortest) {
			output = i;
		}
	}
	return output;
}
// Returns a list of nodes which indicates the shortest path between 2 nodes.
// D indicates this uses Djikstra's shortest path algorithm.
std::vector<GraphNode> MappedGraph::findShortestPathD(GraphNode &start, const GraphNode &end) {
	// Djikstra's algorithm works by:
	// 1. Marking the distances from the start for all nodes connected to the
	// current node. 
	// 2. Mark the current node as visited.
	// 3. Go to the next unvisited node with the shortest distance.
	// 4. If the new node is the targeted node then use the information on
	// previous nodes to make a list of the nodes that were visited. Else 
	// go back to step 1.


	// Array used to contains the information of nodes needed for the 
	// algorithm.
	std::vector<DNode> nodesInfo = {};
	nodesInfo.resize(m_nodes.size());
	
	// Each index in nodesInfo relates to the node at the same index in m_nodes
	nodesInfo.push_back({ 0, false, -1 });
	for (int i = 0; i < m_nodes.size() - 1; i++) {
		nodesInfo.push_back({ INT_MAX, false, -1 });
	}

	// A pointer to nodes in m_nodes
	GraphNode *currentNode = &start;
	// index is the index of the current node in m_nodes and index2 is the
	// index of a node connected to the current node.
	int index, index2;

	while ((*currentNode) != end) {
		index = getNodeIndex(*currentNode);
		// Mark the distances from start for all connected nodes.
		for (int i = 0; i < m_edges[index].size(); i++) {
			index2 = m_edges[index][i].first;
			if ((m_edges[index][i].second + nodesInfo[index].distanceFromStart < nodesInfo[index2].distanceFromStart)) {
				// mark the correct distanceFromStart for any connected node.
				nodesInfo[index2].distanceFromStart = m_edges[index][i].second + nodesInfo[index].distanceFromStart;
				// Mark the correct previous node.
				nodesInfo[index2].previousNodeIndex = index;
			}
		}
		// Mark the current node as visited.
		nodesInfo[index].isVisited = true;
		// Make the next unvisited, closest to start node the current one. 
		index = getShortestUnvistedIndex(nodesInfo);
		if (index == -1) return {};
		
		// Make the next unvisited, closest to start node the current one.
		currentNode = &m_nodes[index];
	}

	// Create output starting from the current node and using the previous
	// node in the node info array to go to start.
	std::vector<GraphNode> output;

	while ((*currentNode) != start) {
		output.insert(output.begin(), (*currentNode));
		currentNode = &m_nodes[nodesInfo[getNodeIndex(*currentNode)].previousNodeIndex];
	}
	output.insert(output.begin(), (*currentNode));

	return output;
}
