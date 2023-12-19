#pragma once
#include "MidNode.h"
#include "Node.h"

/*
X_Node, directes the search of a point p by comparing if p is before or after a vertex.
Inherits from MidNode.
*/
class X_Node : public MidNode {
public:
	//initates the node with a vertex
	X_Node(const Vertex& vertex);

	//returns whether p < m_vertex, meaning the left child is the next one in the search
	virtual bool isLeftNextChild(const Vertex& p) const;

	//returns whether e.p < m_vertex, meaning the left child is the next one in the search
	virtual bool isLeftNextChild(const Edge& e) const;

	//prints the vertex and children of the node
	virtual void printDAG(ostream& ost, size_t depth) const;

private:
	Vertex m_vertex;
};
