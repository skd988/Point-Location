#pragma once
#include <iostream>
#include <vector>
#include "Window.h"
#include "Edge.h"
#include "PlanarSubdivision.h"

using std::vector;
using std::endl;
using std::cout;
using std::cin;

//input 2 edges and check if they cross
void checkCrossings(Window win);

//input 2 non-crossing edges and check if one is above the other in the common segment
void checkEdgeComp(Window win);

//input edges into planar subdivision, crossing edges will disappear
void checkPlanarSubdivision(Window win);

//input edge and point and check whether the point is above, below or on the edge
void checkEdgeToVertex(Window win);

//check if the mouse clicking on the window is in the right place
void checkMouseClick(Window win);

//input two edges and check what is their common segment
void checkEdgeSegment(Window win);

//check edges topological sort from bottom to top
void checkTopologicalSort(Window& win, vector<Edge> edges);

//run point location trapezoids on many different seeds and check if there is a problem
void checkTrapezoidPointLocation(vector<Edge> edges);
