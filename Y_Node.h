#pragma once
#include "MidNode.h"
#include "Edge.h"
#include "Y_Node.h"
#include "Leaf.h"

/*
Y_Node, directes the search of a point p by comparing if p is below or above an edge.
Inherits from MidNode.
*/
class Y_Node : public MidNode {
public:
	//initates the node with an edge
	Y_Node(const Edge& edge);

	//returns whether p < m_edge, meaning the left child is the next one in the search
	virtual bool isLeftNextChild(const Vertex& p) const;

	//returns whether e.p < m_edge, meaning the left child is the next one in the search. if e.p == m_edge.p, compares m_edge < e
	virtual bool isLeftNextChild(const Edge& e) const;

	//prints the edge and children of the node
	virtual void printDAG(ostream& ost, size_t depth) const;

private:
	Edge m_edge;
};