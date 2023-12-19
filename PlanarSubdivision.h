#pragma once
#include <vector>
#include "Edge.h"

using std::vector;

/*
Planar subdivision, containing non crossing edges.
*/
class PlanarSubdivision {
public:
	//adds an edge, if it doesn't crosses any other edges. returns whether the adding was successfull
	bool addEdge(Edge edge);

	//returns vector of the edges
	const vector<Edge>& getEdges() const;

	//binary search the edges, finds the edge which is the closest to x that ends after x 
	vector<Edge>::const_iterator findClosestRightEdgeRec(const vector<Edge>& edges, double x, unsigned int begin, unsigned int end);

private:
	//binary search the edges by p, to find the location for the edge with the value x
	vector<Edge>::const_iterator findClosestRightEdgeByP(double x);

	//binary search the edges by q, to find the location for the edge with the value x
	vector<Edge>::const_iterator findClosestRightEdgeByQ(double x);

	//check if the edge crosses one of the other edges
	bool checkIfCrosses(Edge edge) const;

	vector<Edge> m_edges_by_p;
	vector<Edge> m_edges_by_q;
};