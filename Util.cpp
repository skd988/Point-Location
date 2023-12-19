#include "Util.h"
#include <algorithm>
#include "TopologicalNode.h"

string no_trailling_zeros(double num)
{
	string str = std::to_string(num);
	str = str.erase(str.find_last_not_of('0') + 1, std::string::npos);
	if (str[str.size() - 1] == '.')
		str = str.substr(0, str.size() - 1);

	return str;
}

vector<Vertex> getVertices(const vector<Edge>& edges)
{
	vector<Vertex> vertices;

	for (Edge edge : edges) {
		vertices.push_back(edge.p());
		vertices.push_back(edge.q());
	}

	std::sort(vertices.begin(), vertices.end(), comp_x_vertex);
	auto duplicateBeg = std::unique(vertices.begin(), vertices.end(), x_equal_vertex);
	vertices.erase(duplicateBeg, vertices.end());
	return vertices;
}

double det3(const array<array<double, 3>, 3>& det)
{
	return det[0][0] * (det[1][1] * det[2][2] - det[1][2] * det[2][1]) -
		det[0][1] * (det[1][0] * det[2][2] - det[1][2] * det[2][0]) +
		det[0][2] * (det[1][0] * det[2][1] - det[1][1] * det[2][0]);
}

double findEnd(const vector<Vertex>& vertices, End end)
{
	if (vertices.empty())
		throw exception("Vertices vector is empty");


	double end_value = end == RIGHT || end == LEFT? vertices.begin()->x() : vertices.begin()->y();
	
	for (const Vertex& v : vertices)
		if ((end == TOP && v.y() > end_value) || (end == BOTTOM && v.y() < end_value) ||
			(end == RIGHT && v.x() > end_value || (end == LEFT && v.x() < end_value)))
			end_value = end == RIGHT || end == LEFT ? v.x() : v.y();

	return end_value;

}
