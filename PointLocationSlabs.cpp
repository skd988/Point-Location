#include "PointLocationSlabs.h"
#include <limits>

PointLocationSlabs::PointLocationSlabs(const vector<Edge>& edges) 
{
	vector<Vertex> vertices(getVertices(edges));

	vector<Edge> sortedEdges = topologicalSortBuild(edges, compareEdges);
	for (auto verIt = vertices.begin(); verIt < vertices.end() - 1; ++verIt)
		m_slabs.push_back(Slab(verIt->x(), (verIt + 1)->x(), edges));
}

shared_ptr<const Face> PointLocationSlabs::query(Vertex v)
{
	const Slab* slab = binSearchSlab(v.x());

	if (slab == nullptr)
		return nullptr;

	const Edge* e = slab->binarySearchBelowEdge(v);
	return e == nullptr? nullptr : e->getFace();
}

const Slab* PointLocationSlabs::binSearchSlab(double x)
{
	return binSearchSlabRec(x, 0, m_slabs.size() - 1);
}

const Slab* PointLocationSlabs::binSearchSlabRec(double x, int begin, int end)
{
	if (end < begin)
		return nullptr;

	int half = begin + (end - begin) / 2;

	if (m_slabs[half].leftBound() <= x) {
		if (x <= m_slabs[half].rightBound())
			return &m_slabs[half];
		else
			return binSearchSlabRec(x, half + 1, end);
	}
	else
		return binSearchSlabRec(x, begin, half - 1);
}
