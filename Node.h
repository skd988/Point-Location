#pragma once
#include <memory>
#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include <iostream>

using std::vector;

class MidNode;
class Trapezoid;

using std::shared_ptr;
using std::weak_ptr;

/*
Node class for trapezoid DAG, for searching the trapezoid containing a point.
A virtual class.
*/
class Node {
public:
	//adds a parent for the node 
	void addParent(weak_ptr<MidNode> parent);

	//returns a vector of the  parents of the node
	vector<weak_ptr<MidNode>> getParents();

	//returns whether this node is the root, meaning it has no parents.
	bool isRoot() const;

	//search node tree for point: returns the trapezoid of that point
	virtual shared_ptr<Trapezoid> searchTrapezoid(const Vertex& p) const = 0;

	//search node tree for edge: returns the trapezoid of edge.p
	//used for finding the starting trapezoid when adding a new edge where the edge.p point already exist
	//in that case, the trapezoid will be chosen according to the direction of e
	virtual shared_ptr<Trapezoid> searchTrapezoid(const Edge& e) const = 0;

	//prints the tree into a stream: prints the trapezoid
	virtual void printDAG(ostream& ost, size_t depth) const = 0;

private:
	vector<weak_ptr<MidNode>> m_parents;

};

//gets two node pointers, for each parent of the old child, replaces the old child with a new child (disconnecting the old from the tree) 
void replaceParentsChild(shared_ptr<Node> oldChild, shared_ptr<Node> newChild);
