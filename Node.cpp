#include "Node.h"
#include "MidNode.h"
#include "Trapezoid.h"

void Node::addParent(weak_ptr<MidNode> parent)
{
	m_parents.push_back(parent);
}

vector<weak_ptr<MidNode>> Node::getParents()
{
	return m_parents;
}

bool Node::isRoot() const
{
	return m_parents.empty();
}

void replaceParentsChild(shared_ptr<Node> oldChild, shared_ptr<Node> newChild)
{
	for (weak_ptr<MidNode> parent : oldChild->getParents())
		parent.lock()->replaceChild(oldChild, newChild);
}