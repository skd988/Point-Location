#pragma once
#include <memory>
#include "Face.h"
#include "Vertex.h"

using std::shared_ptr;

/*
Solution for point location problem, can be implmented in a number of ways.
The implementations receive a vector of non crossing edges, each edge contains a pointer to the face above it.
Builds a data base to search the face of a given point.
Virtual class.
*/
class PointLocation
{
public:
	//find the face that contains the vertex
	virtual shared_ptr<const Face> query(Vertex v) = 0;

private:

};