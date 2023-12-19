#pragma once
#include <string>
#include "Vertex.h"
#include "Edge.h"
#include <vector>
#include <array>
#include <list>
#include <memory>
#include <stack>

using std::stack;
using std::list;
using std::string;
using std::vector;
using std::array;
using std::weak_ptr;
using std::make_shared;
using std::shared_ptr;

constexpr int NUM_OF_ENDS = 4;
enum End { TOP, RIGHT, BOTTOM, LEFT };

//returns a string of a double without trailing zeros, or no decimal point if it is an integer
string no_trailling_zeros(double num);

//returns the vertices of an edge list
vector<Vertex> getVertices(const vector<Edge>& edges);

//computes 3-determinant 
double det3(const array<array<double, 3>, 3>& det);

//finds the vertex that is in the corner
double findEnd(const vector<Vertex>& vertices, End end);

//returns whether a vector contains a value
template<typename T>
bool doesContain(list<T> lst, const T& value)
{
	return std::find(lst.begin(), lst.end(), value) != lst.end();
}

//returns whether a weak ptr is uninitialized and points to nullptr
template<typename T>
bool isNull(weak_ptr<T> const& weak)
{
	return !weak.owner_before(weak_ptr<T>{}) && !weak_ptr<T>().owner_before(weak);
}

//returns whether a weak ptr is uninitialized and points to nullptr
template<typename T>
bool isExpiredNotNull(weak_ptr<T> const& weak)
{
	return weak.expired() && !isNull(weak);
}
