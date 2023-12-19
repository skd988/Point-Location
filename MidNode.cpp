#include "MidNode.h"

void MidNode::setLeftChild(shared_ptr<Node> node)
{
	m_left_child = node;
	node->addParent(shared_from_this());
}

void MidNode::setRightChild(shared_ptr<Node> node)
{
	m_right_child = node;
	node->addParent(shared_from_this());
}

void MidNode::replaceChild(shared_ptr<Node> previousChild, shared_ptr<Node> newChild)
{
	if (previousChild == m_right_child)
		setRightChild(newChild);
	else if (previousChild == m_left_child)
		setLeftChild(newChild);
}

shared_ptr<Node> MidNode::getLeftChild() const
{
	return m_left_child;
}

shared_ptr<Node> MidNode::getRightChild() const
{
	return m_right_child;
}

shared_ptr<Trapezoid> MidNode::searchTrapezoid(const Vertex& p) const
{
	return getNextChildInSearch(p)->searchTrapezoid(p);
}

shared_ptr<Trapezoid> MidNode::searchTrapezoid(const Edge& e) const
{
	return getNextChildInSearch(e)->searchTrapezoid(e);
}

shared_ptr<Node> MidNode::getNextChildInSearch(const Vertex& p) const
{
	return isLeftNextChild(p)? getLeftChild() : getRightChild();
}

shared_ptr<Node> MidNode::getNextChildInSearch(const Edge& e) const
{
	return isLeftNextChild(e) ? getLeftChild() : getRightChild();
}

void MidNode::printDAG(ostream& ost, size_t depth) const
{	
	string distance = string(depth, '\t');
	ost << distance << "Left child: " << endl;
	m_left_child->printDAG(ost, depth + 1);
	ost << distance << "Right child: " << endl;
	m_right_child->printDAG(ost, depth + 1);
}
