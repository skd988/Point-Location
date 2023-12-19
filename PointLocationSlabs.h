#pragma once
#include "Edge.h"
#include <vector>
#include <algorithm>
#include "Slab.h"
#include "Face.h"
#include "Util.h"
#include "PointLocation.h"
#include "TopologicalNode.h"

using std::vector;

/*
The algorithm of point location by slabs.
Receives a list of non crossing edges, each pointing to the face above, and cutting the subdivision into slabs.
Allows searching of a point location, meaning the face the point is located in the subdivision.
*/
class PointLocationSlabs : public PointLocation {
public:
	//initates the slabs database.
	PointLocationSlabs(const vector<Edge>& edges);

	//returns the face where the vertex is located at.
	virtual shared_ptr<const Face> query(Vertex v);

private:
	//searches the slab that contain x with binary search
	const Slab* binSearchSlab(double x);

	//recursion iteration of binary search of the slabs
	const Slab* binSearchSlabRec(double x, int begin, int end);

	vector<Slab> m_slabs;
};