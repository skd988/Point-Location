#include "Slab.h"
#include "Util.h"

Slab::Slab(double left_bound, double right_bound, const vector<Edge>& edges) :
	m_left_bound(left_bound),
	m_right_bound(right_bound)
{
	for (const Edge& edge : edges)
		if (edge.p().x() <= m_left_bound && edge.q().x() >= m_right_bound)
			m_edges.push_back(edge);

	//std::sort(m_edges.begin(), m_edges.end());
}

string Slab::to_string()
{
	string s = "Left bound: " + no_trailling_zeros(m_left_bound) + ", Right bound: " + no_trailling_zeros(m_right_bound) + ", Edges:\n";
	for (Edge edge : m_edges)
		s += edge.to_string() + "\n";

	return s;
}

double Slab::leftBound()
{
	return m_left_bound;
}

double Slab::rightBound()
{
	return m_right_bound;
}

const Edge* Slab::binarySearchBelowEdge(Vertex v) const
{
	return binarySearchBelowEdgeRec(v, 0, m_edges.size() - 1);
}

const Edge* Slab::binarySearchBelowEdgeRec(Vertex v, unsigned int begin, unsigned int end) const
{
	if (end < begin || begin >= m_edges.size())
		return nullptr;

	if (begin == end)
		return v < m_edges[begin] ? (begin == 0? nullptr : &m_edges[begin-1]) : &m_edges[begin];

	unsigned int half = begin + (end - begin) / 2;

	if (v < m_edges[half])
		return binarySearchBelowEdgeRec(v, begin, half);

	else
		return binarySearchBelowEdgeRec(v, half + 1, end);

}

ostream& operator<<(ostream& os, Slab slab) {
	return os << slab.to_string();
}