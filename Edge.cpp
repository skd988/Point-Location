#include "Edge.h"
#include <windows.h>
#include "Util.h"

Edge::Edge(double x1, double y1, double x2, double y2, shared_ptr<const Face> face) :
	m_p(x1, y1), m_q(x2, y2), aboveFace(face)
{
	init();
}

Edge::Edge()
{
}

Edge::Edge(const Vertex& v1, const Vertex& v2, shared_ptr<const Face> face) :
	m_p(v1), m_q(v2), aboveFace(face)
{
	init();
}

void Edge::init() 
{
	if (m_p == m_q) 
		throw exception("Edge can not have the same vertex\n");
	
	if (m_p > m_q)
		swapVertices();
}

Vertex Edge::p() const
{
	return m_p;
}

Vertex Edge::q() const
{
	return m_q;
}

void Edge::swapVertices()
{
	Vertex temp(m_p);
	m_p = m_q;
	m_q = temp;
}

Vertex Edge::lineAtX(double x) const
{
	if (m_p.x() == m_q.x())
		return m_p.x() == x? Vertex(x, 0) : Vertex(NAN, NAN);

	double m = (m_p.y() - m_q.y()) / (m_p.x() - m_q.x());
	double y = m * (x - m_p.x()) + m_p.y();
	return Vertex(x, y);
}

Vertex Edge::lineAtY(double y) const
{
	if (m_p.y() == m_q.y())
		return m_p.y() == y ? Vertex(0, y) : Vertex(NAN, NAN);

	double m_inv = (m_p.x() - m_q.x()) / (m_p.y() - m_q.y());
	double x = m_inv * (y - m_p.y()) + m_p.x();
	return Vertex(x, y);
}

bool Edge::isVertical() const
{
	return m_p.x() == m_q.x();
}

bool Edge::isHorizontal() const
{
	return m_p.y() == m_q.y();
}

void Edge::setAboveFace(shared_ptr<const Face> face)
{
	aboveFace = face;
}

shared_ptr<const Face> Edge::getFace() const
{
	return aboveFace;
}

string Edge::to_string() const
{
	return m_p.to_string() + " --> " + m_q.to_string();
}

bool comp_x_edge(const Edge& u, const Edge& v)
{
	return u.p().x() != v.p().x()? comp_x_vertex(u.p(), v.p()) : comp_x_vertex(u.q(), v.q());
}

bool comp_y_edge(const Edge& u, const Edge& v)
{
	return u.p().y() != v.p().y()? comp_y_vertex(u.p(), v.p()) : comp_y_vertex(u.q(), v.q());
}

bool uStartsBetweenV(const Edge& u, const Edge& v)
{
	return v.p() < u.p() && u.p() < v.q();
}

bool uEndsBetweenV(const Edge& u, const Edge& v)
{
	return v.p() < u.q() && u.q() < v.q();
}

bool areCrossing(const Edge& u, const Edge& v)
{
	if (u.p() == v.p()) 
		return u.q() == v;

	if(u.q() == v.q())
		return u.p() == v;

	if (uStartsBetweenV(u, v))
		return areCrossingUafterV(u, v);

	if (uStartsBetweenV(v, u))
		return areCrossingUafterV(v, u);

	return false;
}

bool areCrossingUafterV(const Edge& u, const Edge& v)
{
	if (uEndsBetweenV(u, v) || u.q().x() == v.q().x())
		return (u.p() >= v && u.q() <= v) || (u.p() <= v && u.q() >= v);

	if(uEndsBetweenV(v, u))
		return (u.p() >= v && v.q() >= u) || (u.p() <= v && v.q() <= u);
	
	return false;
}

pair<double, double> getCommonSegment(const Edge& u, const Edge& v)
{	
	if (uStartsBetweenV(u, v) || u.p().x() == v.p().x())
		return { u.p().x(), min(u.q().x(), v.q().x()) };

	if (uStartsBetweenV(v, u))
		return { v.p().x(), min(u.q().x(), v.q().x()) };

	else
		return { NAN, NAN };
}

bool haveCommonSegment(const Edge& u, const Edge& v)
{
	return uStartsBetweenV(u, v) || u.p().x() == v.p().x() || uStartsBetweenV(v, u);
}

bool operator==(const Edge& u, const Edge& v)
{
	return u.p() == v.p() && u.q() == v.q();
}

bool operator<(const Edge &u, const Edge &v)
{
	//if they share a starting point, compare ending points
	if (u.p() == v.p())
		return u.q() < v.q() ? u.q() < v : v.q() > u;

	//if u starts where or after v starts and before v ends (they have a common segment)
	if (uStartsBetweenV(u, v) || u.p().x() == v.p().x())
		return u.p() < v;

	//if v starts after u starts and ends before u ends (they have a common segment)
	if (uStartsBetweenV(v, u))
		return v.p() > u;

	//they have no segment, thus it doesnt matter if u is above or below v
	return false;
}

bool operator<(const Vertex& p, const Edge& u)
{
	//return comp_y_vertex(p, u.lineAtX(p.x()));//old
	return det3PointAndEdge(u, p) < 0;
}

bool operator>(const Vertex& p, const Edge& u)
{
	return det3PointAndEdge(u, p) > 0;
}

bool operator==(const Vertex& p, const Edge& u)
{
	return det3PointAndEdge(u, p) == 0;
}

bool operator>=(const Vertex& p, const Edge& u)
{
	return det3PointAndEdge(u, p) >= 0;
}

bool operator<=(const Vertex& p, const Edge& u)
{
	return det3PointAndEdge(u, p) <= 0;
}

double det3PointAndEdge(const Edge& u, const Vertex& p)
{
	return det3({ { { {u.p().x(), u.p().y(), 1} }, { {u.q().x(), u.q().y(), 1} }, { {p.x(), p.y(), 1} } } });
}

ostream& operator<<(ostream& os, const Edge& e)
{
	return os << e.to_string();
}

istream& operator>>(istream& is, Edge& e)
{
	Vertex p, q;
	is >> p >> q;
	e = Edge(p, q);
	return is;
}

pair<bool, bool> compareEdges(const Edge& e1, const Edge& e2)
{
	return { haveCommonSegment(e1, e2), e1 < e2 };
}
