#include <iostream>

#include "MappedGraph.h"


// Initialises a graph with no nodes and no edges.
MappedGraph::MappedGraph() {
	m_nodes = {};
}

MappedGraph::MappedGraph(const MappedGraph &rhs) {
	m_nodes = rhs.m_nodes;
}

MappedGraph::~MappedGraph() {
	// TODO: THIS.
}


GraphNode MappedGraph::GetNode(std::string &name) const {
	// if (index > m_nodes.size() - 1) return;
	return m_nodes.at(name).node;
}


size_t MappedGraph::GetNodeCount() const {
	return m_nodes.size();
}
size_t MappedGraph::GetEdgeCount() const {
	size_t edgeCount = 0;
	auto it = m_nodes.begin();
	while (it != m_nodes.end()) {
		edgeCount += it->second.edges.size();
		it++;
	}
	return edgeCount;
}
size_t MappedGraph::GetEdgeCount(const GraphNode &node) const {
	auto it = m_nodes.find(node.GetName());
	if (it == m_nodes.end()) return 0;

	return it->second.edges.size();
	
}
int MappedGraph::GetEdgeWeight(const GraphNode &node, const GraphNode &rhs) const {
	if (!HasNode(node) || !HasNode(rhs)) return -1;
	for (int i = 0; i < m_nodes.at(node.GetName()).edges.size(); i++) {
		if (m_nodes.at(node.GetName()).node == rhs) return m_nodes.at(node.GetName()).edges[i].weight;
	}
	return -1;
}


bool MappedGraph::HasNode(const GraphNode &node) const {
	auto it = m_nodes.find(node.GetName());
	if (it == m_nodes.end()) return false;
	return true;
}
bool MappedGraph::HasNode(const std::string &name) const {
	auto it = m_nodes.find(name);
	if (it == m_nodes.end()) return false;
	return true;
}
bool MappedGraph::HasEdge(const GraphNode &node, const GraphNode &rhs) const {
	if (!HasNode(node)) return false;
	if (!HasNode(rhs)) return false;

	auto it = m_nodes.at(node.GetName()).edges.begin();
	while (it != m_nodes.at(node.GetName()).edges.end()) {
		if (it->connectedNodeName == rhs.GetName()) return true;
		it++;
	}
	return false;
}
bool MappedGraph::HasNodeAtPoint(int x, int y) const {
	auto it = m_nodes.begin();
	while (it != m_nodes.end()) {
		if (it->second.node.GetX() == x && it->second.node.GetY() == y) return true;
		it++;
	}
	return false;
}

bool MappedGraph::AddNode(const GraphNode &node) {
	if (m_nodes.find(node.GetName()) != m_nodes.end()) return false;
	
	m_nodes.insert({ node.GetName(), {node, {}} });
	return true;
}
bool MappedGraph::AddEdge(const GraphNode &node, const GraphNode &to, int weight) {
	if (!HasNode(node)) return false;
	if (!HasNode(to)) return false;
	if (HasEdge(node, to)) return false;
	m_nodes[node.GetName()].edges.push_back({ to.GetName(), weight });
	m_nodes[to.GetName()].edges.push_back({ node.GetName(), weight });
	return true;
}
/*
bool MappedGraph::AddNodeAtPoint(int x, int y) {
	GraphNode node = GraphNode(x, y);
	return AddNode(node);
}*/


bool MappedGraph::RemoveNode(const GraphNode &node) {
	if (!HasNode(node)) return false;

	// remove all edges associated with the node
	while (m_nodes[node.GetName()].edges.size() > 0) {
		if (RemoveEdge(node, m_nodes[node.GetName()].edges[0].connectedNodeName) == false) {
			return false;
		}
	}

	// remove the node.
	m_nodes.erase(m_nodes.find(node.GetName()));
	return true;
}
bool MappedGraph::RemoveEdge(const GraphNode &node, const GraphNode &rhs) {
	if (!HasNode(node)) return false;
	if (!HasNode(rhs)) return false;

	const std::string nodeName = node.GetName();
	const std::string rhsName = rhs.GetName();

	auto it = m_nodes[nodeName].edges.begin();
	while (it != m_nodes[nodeName].edges.end()) {
		if (it->connectedNodeName == rhsName) {
			m_nodes[nodeName].edges.erase(it);
			break;
		}
		it++;
	}

	it = m_nodes[rhsName].edges.begin();
	while (it != m_nodes[rhsName].edges.end()) {
		if (it->connectedNodeName == nodeName) {
			m_nodes[rhsName].edges.erase(it);
			break;
		}
		it++;
	}
	return true;
}
bool MappedGraph::RemoveEdge(const GraphNode &node, const std::string &rhs) {
	// Checks both nodes are in the graph.
	if (!HasNode(node)) return false;
	if (m_nodes.find(rhs) == m_nodes.end()) return false;

	auto it = m_nodes[node.GetName()].edges.begin();
	while (it != m_nodes[node.GetName()].edges.end()) {
		if (it->connectedNodeName == rhs) {
			m_nodes[node.GetName()].edges.erase(it);
			break;
		}
		it++;
	}

	it = m_nodes[rhs].edges.begin();
	while (it != m_nodes[rhs].edges.end()) {
		if (it->connectedNodeName == node.GetName()) {
			m_nodes[rhs].edges.erase(it);
			break;
		}
		it++;
	}
	return true;
}


bool MappedGraph::ChangeEdgeWeight(const GraphNode &node, const GraphNode &rhs, const int newWeight) {
	if (!HasNode(node)) return false;
	if (!HasNode(rhs)) return false;

	const std::string nodeName = node.GetName();
	const std::string rhsName = rhs.GetName();

	auto it = m_nodes[nodeName].edges.begin();
	while (it != m_nodes[nodeName].edges.end()) {
		if (it->connectedNodeName == rhsName) {
			m_nodes[nodeName].edges.erase(it);
			break;
		}
		it++;
	}

	it = m_nodes[rhsName].edges.begin();
	while (it != m_nodes[rhsName].edges.end()) {
		if (it->connectedNodeName == nodeName) {
			m_nodes[rhsName].edges.erase(it);
			break;
		}
		it++;
	}

	return true;
}

/*
void MappedGraph::PrintEdge(const std::pair<int, int> &edge) const {
	
	std::cout << "Edge(Node(" << m_nodes[edge.first].GetX() << ", " << m_nodes[edge.first].GetY()
		<< "), " << edge.second << ')' << std::endl;
}
void MappedGraph::PrintNodes() const {
	std::cout << "Printing nodes of graph." << std::endl;
	for (int i = 0; i < m_nodes.size(); i++) {
		m_nodes[i].PrintNode();
	}
}
void MappedGraph::PrintEdges(const GraphNode &node) const {
	int index = GetNodeIndex(node);
	if (index == -1) return;

	std::cout << "Printing edges of ";
	node.PrintNode();

	for (int i = 0; i < m_edges[index].size(); i++) {
		PrintEdge(m_edges[index][i]);
	}
}
void MappedGraph::PrintAllEdges() const {
	std::cout << "Printing all Edges of the graph" << std::endl;
	for (int i = 0; i < m_nodes.size(); i++) {
		std::cout << "Printing Edges of ";
		m_nodes[i].PrintNode();
		for (int j = 0; j < m_edges[i].size(); j++) {
			PrintEdge(m_edges[i][j]);
		}
	}
}
*/


std::vector<GraphNode> MappedGraph::GetAllNodes() const {
	std::vector<GraphNode> output;
	output.resize(m_nodes.size());
	
	auto it = m_nodes.begin();
	while (it != m_nodes.end()) {
		output.push_back({ it->second.node });
		it++;
	}
	return output;
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
	std::string name;
	// The distance this node if from the starting node.
	unsigned int distanceFromStart;
	// has the node been visited or not.
	bool isVisited;
	// the index of the previous node in the m_nodes array. -1 if there is
	// no previous node.
	std::string previousNodeName;
};
// Returns the name of the node with the shortest distance from start.
std::string getShortestUnvistedNode(std::map<std::string, DNode> &nodes) {
	std::string output = "";
	unsigned int currentShortest = UINT_MAX;
	auto it = nodes.begin();
	while (it != nodes.end()) {
		if (it->second.distanceFromStart < currentShortest) {
			currentShortest = it->second.distanceFromStart;
			output = it->second.name;
		}
		it++;
	}
	return output;
}
// Returns a list of nodes which indicates the shortest path between 2 nodes.
// D indicates this uses Djikstra's shortest path algorithm.
std::vector<GraphNode> MappedGraph::FindShortestPathD(const std::string &start, const std::string &end) {
	// Djikstra's algorithm works by:
	// 1. Marking the distances from the start for all nodes connected to the
	// current node. 
	// 2. Mark the current node as visited.
	// 3. Go to the next unvisited node with the shortest distance.
	// 4. If the new node is the targeted node then use the information on
	// previous nodes to make a list of the nodes that were visited. Else 
	// go back to step 1.

	if (!HasNode(start)) return {};
	if (!HasNode(end)) return {};

	// Array used to contains the information of nodes needed for the 
	// algorithm.
	std::map<std::string, DNode> nodesInfo;
	
	// Sets up nodesInfo array.
	auto it = m_nodes.begin();
	while (it != m_nodes.end()) {
		nodesInfo.insert({ it->first, { it->first, UINT_MAX, false, "" } });
	}
	nodesInfo[start].distanceFromStart = 0;


	// A pointer to nodes in m_nodes
	GraphNode *currentNode = &(m_nodes.at(start).node);

	unsigned int distanceFromStart;
	while (currentNode->GetName() != end) {
		// Mark the distances from start for all connected nodes.
		auto connectedNodeIt = m_nodes.at(currentNode->GetName()).edges.begin();
		while (connectedNodeIt != m_nodes.at(currentNode->GetName()).edges.end()) {
			// If the connectedNode is visited, continue
			if (nodesInfo[connectedNodeIt->connectedNodeName].isVisited) {
				it++;
				continue;
			}
			
			// Marks the distance from the start of the connected node.
			distanceFromStart = connectedNodeIt->weight;
			if (nodesInfo[currentNode->GetName()].distanceFromStart != UINT_MAX) {
				distanceFromStart += nodesInfo[currentNode->GetName()].distanceFromStart;
			}
			// If the distance from start is less than an already recorded distance from start,
			// change the distance from start.
			if (distanceFromStart < nodesInfo[connectedNodeIt->connectedNodeName].distanceFromStart) {
				nodesInfo[connectedNodeIt->connectedNodeName].distanceFromStart = distanceFromStart;
				nodesInfo[connectedNodeIt->connectedNodeName].previousNodeName = currentNode->GetName();
			}
			it++;
		}
		// Mark the current node as visited.
		nodesInfo[currentNode->GetName()].isVisited = true;
		
		std::string nextNodeName = getShortestUnvistedNode(nodesInfo);
		if (nextNodeName == "") return {};
		
		// Make the next unvisited, closest to start node the current one.
		currentNode = &(m_nodes[nextNodeName].node);
	}

	// Create output starting from the current node and using the previous
	// node in the node info array to go to start.
	std::vector<GraphNode> output;

	while (currentNode->GetName() != start) {
		output.insert(output.begin(), *currentNode);
		currentNode = &(m_nodes[nodesInfo[currentNode->GetName()].previousNodeName].node);
	}
	output.insert(output.begin(), *currentNode);

	return output;
}
