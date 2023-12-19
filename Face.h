#pragma once
#include <vector>
#include <list>
#include "Edge.h"
#include <algorithm>

using std::vector;

/*
	Geometrical face, by a list of edges.
	Can have a custom name or a generated one.
*/
class Face {
public:
	//initates a face with edges to define it, and an optional custom name (default: face# where # is the number of edges)
	Face(vector<Edge> edges, string name = "");

	//reduces number of faces
	~Face();

	//returns face's edges
	vector<Edge> getEdges() const;

	//returns a string of the edges of the face (sorted) with the name of the face
	string to_string() const;

private:
	string m_name;
	vector<Edge> m_edges;
	static int number_of_faces;
};

//print the face to ostream
ostream& operator<<(ostream& os, const Face& face);