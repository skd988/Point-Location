#pragma once
#include "Node.h"
#include "Trapezoid.h"

using std::make_shared;
using std::endl;

/*
Leaf node, contains a pointer to a trapezoid associated with this leaf.
Inherits from Node.
*/
class Leaf : public Node, public std::enable_shared_from_this<Leaf> {
public:
	//initiates a leaf node, with a pointer to the trapezoid associated with it
	Leaf(shared_ptr<Trapezoid> trapezoid);

	//updates the trapezoid leaf pointer to point to this object (must be seperate as shared from this doesnt work from a constructor
	shared_ptr<Leaf> updateTrapezoid();

	//returns the trapezoid of the leaf
	shared_ptr<Trapezoid> getTrapezoid() const;
	
	//search node tree for point: returns the trapezoid of the leaf
	virtual shared_ptr<Trapezoid> searchTrapezoid(const Vertex& p) const;

	//search node tree for edge: returns the trapezoid of the leaf
	//used for finding the starting trapezoid when adding a new edge where the edge.p point already exists
	//in that case, the trapezoid will be chosen according to the direction of e
	virtual shared_ptr<Trapezoid> searchTrapezoid(const Edge& e) const;

	//prints the tree into a stream: prints the trapezoid
	virtual void printDAG(ostream& ost, size_t depth) const;

private:
	weak_ptr<Trapezoid> m_trapezoid;

};

//create a new leaf connected to a trapezoid, with the trapezoid connected to the leaf
shared_ptr<Leaf> createLeaf(shared_ptr<Trapezoid> trapezoid);