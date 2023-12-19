#pragma once
#include "graphics.h"
#pragma comment(lib,"graphics.lib")
#include "Vertex.h"
#include "Edge.h"
#include <vector>

using std::vector;
using std::pair;

const double DEFAULT_LIMIT = 850;
const double DEFAULT_MULT = 100;
const int POINT_RADIUS = 5;
const int DEFAULT_WID = 1000;
const int DEFAULT_HEI = 1000;

class Window {
public:

	//constructor, defines the window with width, height, limit to start with and mult (number of pixles per point)
	Window(int width = DEFAULT_WID, int height = DEFAULT_HEI, double limit = DEFAULT_LIMIT, double mult = DEFAULT_MULT);

	//destructor, closes window
	~Window();

	//draws all the lines in the list of edges
	void drawLines(vector<Edge> edges);

	//draws an edge
	void drawLine(Edge edge);

	//sets lines' thickness
	void setThickness(int thickness);

	//sets drawing color
	void setColor(int color);

	//clear the window
	void clear();

	//draws a point (a circle)
	void drawPoint(Vertex p, int color = WHITE);

	//returns a vertex of the window coordinates of the click
	Vertex getClick();

private:
	double m_limit;
	double m_mult;
};