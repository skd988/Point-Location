#pragma once
#include "Edge.h"
#include <vector>
#include <algorithm>

using std::vector;

/*
A slab of the subdivision, defined by left and right bounds and the edges that cross the slab.
*/
class Slab {
public:
	//initates the slab with the bounds, keeps the edges that cross the slab. assumes edges are sorted
	Slab(double left_bound, double right_bound, const vector<Edge>& edges);

	//returns a string of the slab's edges
	string to_string();

	//returns the left bound
	double leftBound();

	//returns the right bound
	double rightBound();

	//binary searchs the edge that is right below the vertex
	const Edge* binarySearchBelowEdge(Vertex v) const;

private:
	//iteration of the recursion of the binary search
	const Edge* binarySearchBelowEdgeRec(Vertex v, unsigned int begin, unsigned int end) const;

	double m_left_bound;
	double m_right_bound;
	vector<Edge> m_edges;
};

//prints the slab to an ostream
ostream& operator<<(ostream& os, Slab slab);