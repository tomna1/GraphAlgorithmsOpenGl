#ifndef GRAPHNODE_H
#define GRAPHNODE_H

class GraphNode {
private:
	int m_x;
	int m_y;

public:
	GraphNode();
	GraphNode(int x, int y);

	bool setX(int x);
	bool setY(int y);

	int getX();
	int getY();

	int distanceToNode(const GraphNode&);
	int distanceToPoint(int x, int y);
};

#endif