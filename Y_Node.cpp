#include "Y_Node.h"

Y_Node::Y_Node(const Edge& edge) :
	m_edge(edge)
{
}

bool Y_Node::isLeftNextChild(const Vertex& p) const
{
	return p > m_edge;
}

bool Y_Node::isLeftNextChild(const Edge& e) const
{
	if (e.p() == m_edge.p())
		return m_edge < e;

	return isLeftNextChild(e.p());
}

void Y_Node::printDAG(ostream& ost, size_t depth) const
{
	string distance = string(depth, '\t');
	ost << distance << "Y Node: " << m_edge << endl;
	MidNode::printDAG(ost, depth);
}