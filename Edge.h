#pragma once
#include "Vertex.h"
#include <math.h>
#include <exception>
#include <memory>

using std::shared_ptr;
using std::exception;
using std::pair;
class Face;

/*
An edge defined by two endpoints, p and q.
The endpoints are vertices (Vertex)
Can also point to the face which is above it (default to the infinity face). 
p.x <= q.x by default.
*/
class Edge {
public:
	//initiates with default constructors
	Edge();

	//initate edge with vertices, along face (default: infinity face)
	Edge(const Vertex& v1, const Vertex& v2, shared_ptr<const Face> face = nullptr);

	//initate edge with vertices parameters, along face (default: infinity face)
	Edge(double x1, double y1, double x2, double y2, shared_ptr<const Face> face = nullptr);
	
	//return p (default: left endpoint)
	Vertex p() const;

	//return q (default: right endpoint)
	Vertex q() const;

	//swap the vertices p and q
	void swapVertices();

	//return the value of the line of the vertex at x. if the line doesnt exist at x returns Vertex(NAN, NAN)
	Vertex lineAtX(double x) const;

	//return the value of the line of the vertex at y. if the line doesnt exist at y returns Vertex(NAN, NAN)
	Vertex lineAtY(double y) const;

	//return whether the edge is vertical (p.x == q.x)
	bool isVertical() const;

	//return whether the edge is vertical (p.y == q.y)
	bool isHorizontal() const;

	//sets the above face of the edge
	void setAboveFace(shared_ptr<const Face> face);
	
	//returns a pointer to the face above the edge
	shared_ptr<const Face> getFace() const;

	//returns a string of the edge vertices (p --> q)
	string to_string() const;

private:
	//initates the edge, for constructor
	void init();

	Vertex m_p;
	Vertex m_q;
	shared_ptr<const Face> aboveFace;
};

//returns whether u.p.x < v.p.x. if the values are equal returns whether u.q.x < v.q.x
bool comp_x_edge(const Edge& u, const Edge& v);

//returns whether u.p.y < v.p.y. if the values are equal returns whether u.q.y < v.q.y
bool comp_y_edge(const Edge& u, const Edge& v);

//returns whether u.p is between v's endpoints
bool uStartsBetweenV(const Edge& u, const Edge& v);

//returns whether u.q is between v's endpoints
bool uEndsBetweenV(const Edge& u, const Edge& v);

//returns whether two edges are crossing
bool areCrossing(const Edge& u, const Edge& v);

//returns whether two edges are crossing, assuming u.p is between v's endpoints
bool areCrossingUafterV(const Edge& u, const Edge& v);

//returns the common segment of u and v
pair<double, double> getCommonSegment(const Edge& u, const Edge& v);

//returns whether u and v have a common segment
bool haveCommonSegment(const Edge& u, const Edge& v);

//returns whether two edges have the same vertices
bool operator==(const Edge& u, const Edge& v);

//prints the edge to ostream
ostream& operator<<(ostream& os, const Edge& e);

//input into edge from istream
istream& operator>>(istream& is, Edge& e);

//assuming no crossings, if u and v have a shared area (of x axis) returns whether u is below v
bool operator<(const Edge& u, const Edge& v);

//returns whether a point p is below the line of u
bool operator<(const Vertex& p, const Edge& u);

//returns whether a point p is above the line of u
bool operator>(const Vertex& p, const Edge& u);

//returns whether a point p is on the line of u
bool operator==(const Vertex& p, const Edge& u);

//returns whether a point p is on or above the line of u
bool operator>=(const Vertex& p, const Edge& u);

//returns whether a point p is on or below the line of u
bool operator<=(const Vertex& p, const Edge& u);

//calculate the place of p to the line of u
double det3PointAndEdge(const Edge& u, const Vertex& p);

//returns a pair of bools, first indicates whether the edges share a segment, the second is if they share a segment is e1 < e2 (assuming no crossings)
pair<bool, bool> compareEdges(const Edge& e1, const Edge& e2);