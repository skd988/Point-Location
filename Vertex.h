#pragma once
#include <string>
#include <ostream>
#include <istream>

using std::ostream;
using std::istream;
using std::string;

/*
A vertex, with x and y double parameters
*/
class Vertex {
public:
	//initiates the vertex with (0,0)
	Vertex();

	//initates the vertex with x and y
	Vertex(double x, double y);

	//returns the x value
	double x() const;

	//returns the y value
	double y() const;

	//returns the string of the vertex's parameters
	string to_string() const;

private:
	double m_x;
	double m_y;
};

//prints the vertex to ostream
ostream& operator<<(ostream& os, const Vertex& p);

//input values into p from istream
istream& operator>>(istream& is, Vertex& p);

//returns whether p's and q's parameters are equal
bool operator==(const Vertex& p, const Vertex& q);

//returns whether p's and q's parameters are different
bool operator!=(const Vertex& p, const Vertex& q);

//returns whether p.x < q.x. if they're equal returns whether p.y < q.y
bool operator<(const Vertex& p, const Vertex& q);

//returns whether p.x > q.x. if they're equal returns whether p.y > q.y
bool operator>(const Vertex& p, const Vertex& q);

//returns whether p equals or lesser than q (see operator < and ==)
bool operator<=(const Vertex& p, const Vertex& q);

//returns whether p equals or greater than q (see operator > and ==)
bool operator>=(const Vertex& p, const Vertex& q);

//returns whether p.x < q.x
bool comp_x_vertex(const Vertex& p, const Vertex& q);

//returns whether p.y < q.y
bool comp_y_vertex(const Vertex& p, const Vertex& q);

//returns whether p.x == q.x
bool x_equal_vertex(const Vertex& p, const Vertex& q);

//returns whether p.y == q.y
bool y_equal_vertex(const Vertex& p, const Vertex& q);
