#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <memory>

using std::shared_ptr;
using std::weak_ptr;

class Leaf;

/*
Trapezoid, defined by top and bottom edges, left and right points,
contains pointers to its neighbors on its sides
Also contains a pointer to the leaf of the DAG that is associated with it.
It is called trapezoid, but actually can be either a trapezoid or a triangle.
*/
class Trapezoid {
public:
	//initates the trapezoid with the top and bottom edges and the left and right points
	//neighbors and leaf are null at this point.
	Trapezoid(Vertex leftp, Vertex rightp, Edge top, Edge bottom);

	//sets the leaf of this trapezoid
	void setLeaf(shared_ptr<Leaf> leaf);

	//returns the leaf
	shared_ptr<Leaf> getLeaf() const;

	//returns the left point
	Vertex getLeftp() const;

	//returns the right point
	Vertex getRightp() const;

	//returns the top edge
	Edge getTop() const;

	//returns the bottom edge
	Edge getBottom() const;

	//returns the bottom right neighbor
	shared_ptr<Trapezoid> getBottomRight() const;

	//returns the top right neighbor
	shared_ptr<Trapezoid> getTopRight() const;

	//returns the bottom left neighbor
	shared_ptr<Trapezoid> getBottomLeft() const;

	//returns the top left neighbor
	shared_ptr<Trapezoid> getTopLeft() const;

	//for each right neighbor which is empty or currently is previousNeighbor, replaces with newNeighbor
	void replaceRightNeighbors(shared_ptr<Trapezoid> previousNeighbor, shared_ptr<Trapezoid> newNeighbor);

	//for each left neighbor which is empty or currently is previousNeighbor, replaces with newNeighbor
	void replaceLeftNeighbors(shared_ptr<Trapezoid> previousNeighbor, shared_ptr<Trapezoid> newNeighbor);

	//sets the bottom right neighbor
	void setBottomRight(shared_ptr<Trapezoid> trapezoid);

	//sets the top right neighbor
	void setTopRight(shared_ptr<Trapezoid> trapezoid);

	//sets the bottom left neighbor
	void setBottomLeft(shared_ptr<Trapezoid> trapezoid);

	//sets the top left neighbor
	void setTopLeft(shared_ptr<Trapezoid> trapezoid);

	//returns whether one of the neighbors of leaf pointers are expired (not null)
	bool isExpired() const;
	
	//returns a string of the trapezoid's pointers and edges  
	string to_string() const;
	

private:
	Vertex m_leftp;
	Vertex m_rightp;
	Edge m_top;
	Edge m_bottom;
	weak_ptr<Trapezoid> m_top_right;
	weak_ptr<Trapezoid> m_bottom_right;
	weak_ptr<Trapezoid> m_top_left;
	weak_ptr<Trapezoid> m_bottom_left;
	weak_ptr<Leaf> m_leaf;
};

//compare two trapezoids points and edges only 
bool compareWithoutNeighbors(const Trapezoid& trap1, const Trapezoid& trap2);

//compare two trapezoids shared_ptr points and edges only 
bool compareWithoutNeighbors(shared_ptr<Trapezoid> trap1, shared_ptr<Trapezoid> trap2);

//compare two trapezoids edges, points and neighbors 
bool operator==(const Trapezoid& trap1, const Trapezoid& trap2);

//print trapezoids details 
ostream& operator<<(ostream& ost, const Trapezoid& trapezoid);