#pragma once
#include <vector>
#include <list>
#include <memory>
#include <unordered_map>
#include "PointLocation.h"
#include "Trapezoid.h"
#include "Node.h"
#include "Leaf.h"
#include "MidNode.h"
#include "X_Node.h"
#include "Y_Node.h"
#include "Util.h"

using std::pair;
using std::shared_ptr;
using std::vector;
using std::unordered_map;
using std::make_shared;
using std::list;

//distance of R from the extreme points, can be any positive value
const double R_DISTANCE_FROM_POINT = 1;

/*
The algorithm of point location by trapezoids.
Receives a list of non crossing edges, each pointing to the face above, and cutting the subdivision into trapezoids.
Allows searching of a point location, meaning the face the point is located in the subdivision.
*/
class PointLocationTrapezoids : public PointLocation {
public:
	//initates the trapezoid data structure
	PointLocationTrapezoids(const vector<Edge>& edges, unsigned int seed = 0);

	//returns the face where the vertex is located at
	virtual shared_ptr<const Face> query(Vertex v);

	//return number of trapezoids
	int getSize() const;

	//checks whether one of the trapezoids contains an expired (not null) pointer to a leaf or neighbors
	bool checkExpired();


private:
	//add trapezoid as a new shared_ptr to the database, returns a shared_ptr of the new trapezoid
	shared_ptr<Trapezoid> addTrapezoid(const Trapezoid& trapezoid);

	//returns the trapezoids the edge intersects
	list<shared_ptr<Trapezoid>> getIntersectedTrapezoids(const Edge& e);

	//adds an edge, replacing intersected trapezoids with new ones
	void addEdge(const Edge& e);

	//creates the trapezoids added by the edge and updates the DAG
	void createTrapezoidsAndUpdataDataStructure(const Edge& e, list<shared_ptr<Trapezoid>> intersectedTrapezoids);

	//connects a middle trapezoid to the original trapez right neighbors
	void connectMiddleTrapezoidToRightTrapezoids(shared_ptr<Trapezoid> origTrapez, shared_ptr<Trapezoid> trapez, bool isTop);

	//creates a new middle trapezoid if a new one wasn't already created
	shared_ptr<Leaf> getOrCreateMiddleTrapezoid(const Edge& e, shared_ptr<Trapezoid> origTrapez, shared_ptr<Trapezoid> lastTrapez, list<Vertex>& vertices, bool isTop);
	
	//creates a trapezoid left to an edge
	shared_ptr<Leaf> createLeftTrapezoid(const Edge& e, shared_ptr<Trapezoid> origTrapez);

	//creates a trapezoid right to an edge
	shared_ptr<Leaf> createRightTrapezoid(const Edge& e, shared_ptr<Trapezoid> origTrapez, shared_ptr<Trapezoid> lastTop, shared_ptr<Trapezoid> lastBottom);
	
	//creates a middle trapezoid to connect to the left trapezoid
	shared_ptr<Leaf> createMiddleTrapezoidConnectedToLeftTrapezoid(const Edge& e, shared_ptr<Trapezoid> origTrapez, shared_ptr<Trapezoid> leftTrapez, const Vertex& rightp, bool isTop);
	
	//replaces a leaf in the DAG with a new sub-DAG
	void replaceNode(shared_ptr<Leaf> origNode, shared_ptr<Node> newNode);

	//create new trapezoids where edge is starting before or at the start of the original trapezoid and ends after or at the end of the original trapezoid
	pair<shared_ptr<Trapezoid>, shared_ptr<Trapezoid>> middleSplit(const Edge& e, shared_ptr<Trapezoid> origTrapez, list<Vertex>& topVertices, list<Vertex>& bottomVertices, shared_ptr<Trapezoid> lastTop, shared_ptr<Trapezoid> lastBottom);
	
	//create new trapezoids where edge is starting after the start of the original trapezoid and ends after or at the end of the original trapezoid
	pair<shared_ptr<Trapezoid>, shared_ptr<Trapezoid>> startNotConnected(const Edge& e, shared_ptr<Trapezoid> origTrapez, list<Vertex>& topVertices, list<Vertex>& bottomVertices);
	
	//create new trapezoids where edge is starting before or at the start of original trapezoid and ends before the end of the original trapezoid
	pair<shared_ptr<Trapezoid>, shared_ptr<Trapezoid>> endNotConnected(const Edge& e, shared_ptr<Trapezoid> origTrapez, list<Vertex>& topVertices, list<Vertex>& bottomVertices, shared_ptr<Trapezoid> lastTop, shared_ptr<Trapezoid> lastBottom);
	
	//create new trapezoids where edge is between the start and end of the trapezoid
	pair<shared_ptr<Trapezoid>, shared_ptr<Trapezoid>> notConnectedOneTrapezoid(const Edge& e, shared_ptr<Trapezoid> origTrapez, list<Vertex>& topVertices, list<Vertex>& bottomVertices);
	
	//returns a trapezoid of a vertex
	shared_ptr<Trapezoid> getTrapezoid(const Vertex& v);

	//returns a trapezoid of edge.p. if the edge.p is an existing point in the data structure, returns according to the edge's direction
	shared_ptr<Trapezoid> getTrapezoid(const Edge& e);

	unordered_map<string, shared_ptr<Trapezoid>> m_trapezoids;
	shared_ptr<Node> m_tree;
};

