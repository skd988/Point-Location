#include "Leaf.h"

Leaf::Leaf(shared_ptr<Trapezoid> trapezoid)
{
	//std::cout << "Leaf: " << ++count << std::endl;

	m_trapezoid = trapezoid;
}

shared_ptr<Leaf> Leaf::updateTrapezoid()
{
	getTrapezoid()->setLeaf(shared_from_this());
	return shared_from_this();
}

shared_ptr<Trapezoid> Leaf::getTrapezoid() const
{
	if (shared_ptr<Trapezoid> trapezoid = m_trapezoid.lock())
		return trapezoid;

	throw exception("Leaf's trapezoid is null or expired");
}

shared_ptr<Trapezoid> Leaf::searchTrapezoid(const Vertex& p) const
{
	return getTrapezoid();
}

shared_ptr<Trapezoid> Leaf::searchTrapezoid(const Edge& e) const
{
	return getTrapezoid();
}

void Leaf::printDAG(ostream& ost, size_t depth) const
{
	string distance = string(depth, '\t');
	ost << distance << "Leaf: " << *getTrapezoid() << endl;
}

shared_ptr<Leaf> createLeaf(shared_ptr<Trapezoid> trapezoid)
{
	return make_shared<Leaf>(trapezoid)->updateTrapezoid();
}
