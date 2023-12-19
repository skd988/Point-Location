#include "Vertex.h"
#include "Util.h"

Vertex::Vertex() :
	m_x(0),
	m_y(0)
{
}

Vertex::Vertex(double x, double y) :
	m_x(x), m_y(y)
{
}

double Vertex::x() const
{
	return m_x;
}

double Vertex::y() const
{
	return m_y;
}

ostream& operator<<(ostream& os, const Vertex& p) {
	return os << p.to_string();
}

istream& operator>>(istream& is, Vertex& p)
{
	double x, y;
	if(!(is >> x >> y))
		throw exception("Error inputing to vertex");
	p = Vertex(x, y);
	return is;
}

bool operator==(const Vertex& p, const Vertex& q)
{
	return p.x() == q.x() && p.y() == q.y();
}

bool operator!=(const Vertex& p, const Vertex& q)
{
	return !(p == q);
}

bool operator<(const Vertex& p, const Vertex& q)
{
	return p.x() != q.x()? comp_x_vertex(p, q) : comp_y_vertex(p, q);
}

bool operator<=(const Vertex& p, const Vertex& q)
{
	return p < q || p == q;
}

bool operator>=(const Vertex& p, const Vertex& q)
{
	return p > q || p == q;
}

bool operator>(const Vertex& p, const Vertex& q)
{
	return p.x() != q.x() ? !comp_x_vertex(p, q) : !comp_y_vertex(p, q);
}

bool comp_x_vertex(const Vertex& p, const Vertex& q)
{
	return p.x() < q.x();
}

bool comp_y_vertex(const Vertex& p, const Vertex& q)
{
	return p.y() < q.y();
}

bool x_equal_vertex(const Vertex& p, const Vertex& q)
{
	return p.x() == q.x();
}

bool y_equal_vertex(const Vertex& p, const Vertex& q)
{
	return p.y() == q.y();
}

string Vertex::to_string() const
{
	string str = "(" + no_trailling_zeros(m_x);
	str += ", " + no_trailling_zeros(m_y);
	str += ")";
	return str;
}