#include "Face.h"

int Face::number_of_faces = 0;

Face::Face(vector<Edge> edges, string name) :
	m_name(name)
{
	std::sort(edges.begin(), edges.end(), comp_x_edge);

	if (name.empty())
		m_name = "face" + std::to_string(++number_of_faces);

	if (edges.empty())
		return;

	Vertex beg = edges[0].p();
	Vertex last = edges[0].q();

	m_edges.push_back(edges[0]);
	edges.erase(edges.begin());

	while (last != beg) {
		bool found = false;

		for (auto edge = edges.begin(); edge != edges.end(); ++edge) {
			if (edge->p() == last) 
				last = edge->q();

			else if (edge->q() == last) {
				last = edge->p();
				edge->swapVertices();
			}
			else
				continue;

			found = true;
			m_edges.push_back(*edge);
			edges.erase(edge);
			break;
		}

		if (!found)
			throw std::exception("The list given does not contain a full face.\n");
	}
	if(!edges.empty())
		throw std::exception("The list given does contain more edges than contained in the face.\n");
}

Face::~Face()
{
	--number_of_faces;
}

vector<Edge> Face::getEdges() const
{
	vector<Edge> edges;
	for (Edge edge : m_edges)
		edges.push_back({ edge.p(), edge.q() });

	return edges;
}

string Face::to_string() const
{
	string s = m_name + ":\n";
	if (m_edges.empty())
		s += "infinity edge";

	else {
		s += m_edges[0].p().to_string();
		for (Edge edge : m_edges)
			s += " --> " + edge.q().to_string();
	}

	s += "\n";

	return s;
}

ostream& operator<<(ostream& os, const Face& face)
{
	return os << face.to_string();
}