#include "Trapezoid.h"
#include "Leaf.h"
#include "Util.h"

Trapezoid::Trapezoid(Vertex leftp, Vertex rightp, Edge top, Edge bottom) :
	m_leftp(leftp),
	m_rightp(rightp),
	m_top(top),
	m_bottom(bottom)
{
}

void Trapezoid::setLeaf(shared_ptr<Leaf> leaf)
{
	m_leaf = leaf;
}

shared_ptr<Leaf> Trapezoid::getLeaf() const
{
	if (shared_ptr<Leaf> leaf = m_leaf.lock())
		return leaf;

	throw exception("Trapezoid's leaf is null or expired");
}

Vertex Trapezoid::getLeftp() const
{
	return m_leftp;
}

Vertex Trapezoid::getRightp() const
{
	return m_rightp;
}

Edge Trapezoid::getTop() const
{
	return m_top;
}

Edge Trapezoid::getBottom() const
{
	return m_bottom;
}

shared_ptr<Trapezoid> Trapezoid::getBottomRight() const
{
	return m_bottom_right.lock();
}

shared_ptr<Trapezoid> Trapezoid::getTopRight() const
{
	return m_top_right.lock();
}

shared_ptr<Trapezoid> Trapezoid::getBottomLeft() const
{
	return m_bottom_left.lock();
}

shared_ptr<Trapezoid> Trapezoid::getTopLeft() const
{
	return m_top_left.lock();
}

void Trapezoid::replaceRightNeighbors(shared_ptr<Trapezoid> previousNeighbor, shared_ptr<Trapezoid> newNeighbor)
{
	if (!getBottomRight() || getBottomRight() == previousNeighbor)
		m_bottom_right = newNeighbor;
	if (!getTopRight() || getTopRight() == previousNeighbor)
		m_top_right = newNeighbor;
}

void Trapezoid::replaceLeftNeighbors(shared_ptr<Trapezoid> previousNeighbor, shared_ptr<Trapezoid> newNeighbor)
{
	if (!getBottomLeft() || getBottomLeft() == previousNeighbor)
		m_bottom_left = newNeighbor;
	if (!getTopLeft() || getTopLeft() == previousNeighbor)
		m_top_left = newNeighbor;
}

void Trapezoid::setBottomRight(shared_ptr<Trapezoid> trapezoid)
{
	m_bottom_right = trapezoid;
}

void Trapezoid::setTopRight(shared_ptr<Trapezoid> trapezoid)
{
	m_top_right = trapezoid;
}

void Trapezoid::setBottomLeft(shared_ptr<Trapezoid> trapezoid)
{
	m_bottom_left = trapezoid;
}

void Trapezoid::setTopLeft(shared_ptr<Trapezoid> trapezoid)
{
	m_top_left = trapezoid;
}

bool Trapezoid::isExpired() const
{
	return isExpiredNotNull(m_leaf) || 
		isExpiredNotNull(m_bottom_left) || isExpiredNotNull(m_bottom_right) || 
		isExpiredNotNull(m_top_left) || isExpiredNotNull(m_top_right);
}

string Trapezoid::to_string() const
{
	return m_leftp.to_string() + " " + m_rightp.to_string() + " " + m_top.to_string() + " " + m_bottom.to_string();
}

bool compareWithoutNeighbors(const Trapezoid& trap1, const Trapezoid& trap2)
{
	return trap1.getLeftp() == trap2.getLeftp() && trap1.getRightp() == trap2.getRightp() &&
		trap1.getTop() == trap2.getTop() && trap1.getBottom() == trap1.getBottom();
}

bool compareWithoutNeighbors(shared_ptr<Trapezoid> trap1, shared_ptr<Trapezoid> trap2)
{
	return (!trap1 && !trap2) || compareWithoutNeighbors(*trap1, *trap2);
}

bool operator==(const Trapezoid& trap1, const Trapezoid& trap2)
{
	return compareWithoutNeighbors(trap1, trap2)
		&& compareWithoutNeighbors(trap1.getBottomLeft(), trap2.getBottomLeft())
		&& compareWithoutNeighbors(trap1.getTopLeft(), trap2.getTopLeft())
		&& compareWithoutNeighbors(trap1.getBottomRight(), trap2.getBottomRight()) 
		&& compareWithoutNeighbors(trap1.getTopRight(), trap2.getTopRight());
}

ostream& operator<<(ostream& ost, const Trapezoid& trapezoid)
{
	return ost << "Leftp: " << trapezoid.getLeftp() << " Rightp: " << trapezoid.getRightp() << " Top: " 
		<< trapezoid.getTop() << " Bottom: " << trapezoid.getBottom();
}