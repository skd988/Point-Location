#include "PlanarSubdivision.h"

bool PlanarSubdivision::addEdge(Edge edge)
{
	if (checkIfCrosses(edge))
		return false;

	m_edges_by_p.insert(findClosestRightEdgeByP(edge.p().x()), edge);
	m_edges_by_q.insert(findClosestRightEdgeByQ(edge.q().x()), edge);
	return true;
}

const vector<Edge>& PlanarSubdivision::getEdges() const
{
	return m_edges_by_p;
}

bool PlanarSubdivision::checkIfCrosses(Edge edge) const
{
	for (auto toCheck = m_edges_by_p.begin(); toCheck < m_edges_by_p.end() && toCheck->p().x() <= edge.q().x(); ++toCheck)
		if (areCrossing(*toCheck, edge))
			return true;

	return false;
}

vector<Edge>::const_iterator PlanarSubdivision::findClosestRightEdgeByP(double x)
{
	return findClosestRightEdgeRec(m_edges_by_p, x, 0, m_edges_by_p.size());
}

vector<Edge>::const_iterator PlanarSubdivision::findClosestRightEdgeByQ(double x)
{
	return findClosestRightEdgeRec(m_edges_by_q, x, 0, m_edges_by_q.size());
}

vector<Edge>::const_iterator PlanarSubdivision::findClosestRightEdgeRec(const vector<Edge>& edges, double x, unsigned int begin, unsigned int end)
{
	if (end < begin || begin >= edges.size())
		return edges.end();

	if (end == begin)
		return edges.begin() + begin;

	unsigned int half = begin + (end - begin) / 2;

	if (x <= edges[half].q().x())
		return findClosestRightEdgeRec(edges, x, begin, half);

	else
		return findClosestRightEdgeRec(edges, x, half + 1, end);

}