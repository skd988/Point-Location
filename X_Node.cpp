#include "X_Node.h"

X_Node::X_Node(const Vertex& vertex) :
	m_vertex(vertex)
{
}

bool X_Node::isLeftNextChild(const Vertex& p) const
{
	return p < m_vertex;
}

bool X_Node::isLeftNextChild(const Edge& e) const
{
	return isLeftNextChild(e.p());
}

void X_Node::printDAG(ostream& ost, size_t depth) const
{
	string distance = string(depth, '\t');
	ost << distance << "X Node: " << m_vertex << endl;
	MidNode::printDAG(ost, depth);
}
