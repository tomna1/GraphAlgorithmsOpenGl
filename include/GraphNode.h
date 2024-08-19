#ifndef GRAPHNODE_H
#define GRAPHNODE_H

class GraphNode {
private:
	int x;
	int y;

public:
	GraphNode();
	~GraphNode();

	int setX(int);
	int setY(int);

	int distanceToNode(GraphNode);
	int distanceToPoint(int x, int y);
};

#endif