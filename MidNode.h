#pragma once
#include "Node.h"
#include "Vertex.h"
#include "Edge.h"

using std::endl;

/*
MidNode node, contains pointers to a left and right children.
Inherits from Node.
A virtual class.
*/
class MidNode : public Node, public std::enable_shared_from_this<MidNode>{
public:

	//sets the left child and adds this node as a its parent
	void setLeftChild(shared_ptr<Node> node);

	//sets the right child and adds this node as a its parent
	void setRightChild(shared_ptr<Node> node);

	//gets a child of this node and a new child, replaces the child with a new child. 
	//if the previous child isn't a child of this node, does nothing
	void replaceChild(shared_ptr<Node> previousChild, shared_ptr<Node> newChild);

	//search node tree for point: searches the next child according to the node's type. returns the trapezoid of that point
	virtual shared_ptr<Trapezoid> searchTrapezoid(const Vertex& p) const;

	//search node tree for edge: searches the next child according to the node's type. returns the trapezoid of edge.p
	//used for finding the starting trapezoid when adding a new edge where the edge.p point already exist
	//in that case, the trapezoid will be chosen according to the direction of e
	virtual shared_ptr<Trapezoid> searchTrapezoid(const Edge& e) const;

	//for search function of point, returns the next child that should be search, according to the node's type
	shared_ptr<Node> getNextChildInSearch(const Vertex& p) const;

	//for search function of edge, returns the next child that should be search, according to the node's type
	shared_ptr<Node> getNextChildInSearch(const Edge& e) const;

	//for trapezoid search of point, returns whether the next child in the search is the left one
	virtual bool isLeftNextChild(const Vertex& p) const = 0;

	//for trapezoid search of edge, returns whether the next child in the search is the left one
	virtual bool isLeftNextChild(const Edge& e) const = 0;

	//prints the tree into a stream: prints tree of right and left children
	virtual void printDAG(ostream& ost, size_t depth) const;

	//returns the left child of the node
	shared_ptr<Node> getLeftChild() const;

	//returns the right child of the node
	shared_ptr<Node> getRightChild() const;

private:
	shared_ptr<Node> m_left_child;
	shared_ptr<Node> m_right_child;
};