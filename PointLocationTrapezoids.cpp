#include "PointLocationTrapezoids.h"

bool PointLocationTrapezoids::checkExpired()
{
	bool answer = false;
	for (auto& trapez : m_trapezoids)
	{
		if (trapez.second->isExpired())
		{
			std::cout << "alas! one or more of this trapezoid neighbors is expired: " << *trapez.second << std::endl;
			answer = true;
		}

	}
	return answer;
}

PointLocationTrapezoids::PointLocationTrapezoids(const vector<Edge>& edges, unsigned int seed) :
	m_tree(nullptr)
{
	if (seed == 0)
		seed = time(nullptr);

	srand(seed);

	vector<Edge> randomized_edges(edges);
	std::random_shuffle(randomized_edges.begin(), randomized_edges.end());

	array<double, NUM_OF_ENDS> r_ends;
	vector<Vertex> vertices = getVertices(edges);

	for (int end = TOP; end <= LEFT; ++end)
		r_ends[end] = findEnd(vertices, End(end)) + ((end == RIGHT || end == TOP)? R_DISTANCE_FROM_POINT : -R_DISTANCE_FROM_POINT);

	Edge r_top = { { r_ends[LEFT], r_ends[TOP] }, { r_ends[RIGHT], r_ends[TOP] } };
	Edge r_bottom = { { r_ends[LEFT], r_ends[BOTTOM] }, { r_ends[RIGHT], r_ends[BOTTOM] } };

	m_tree = createLeaf(addTrapezoid(Trapezoid(r_bottom.p(), r_top.q(), r_top, r_bottom)));

	int index = 0;
	for (const Edge& edge : randomized_edges)
		addEdge(edge);

}

shared_ptr<Trapezoid> PointLocationTrapezoids::addTrapezoid(const Trapezoid& trapezoid)
{
	//add trapezoid if exists
	auto insertResult = m_trapezoids.insert({ trapezoid.to_string(), make_shared<Trapezoid>(trapezoid) });
	return insertResult.first->second;
}

void PointLocationTrapezoids::addEdge(const Edge& e)
{
	auto trapezoids_size = m_trapezoids.size();

	list<shared_ptr<Trapezoid>> intersectedTrapezoids(getIntersectedTrapezoids(e));

	createTrapezoidsAndUpdataDataStructure(e, intersectedTrapezoids);

	for (shared_ptr<Trapezoid> trapez : intersectedTrapezoids)
		m_trapezoids.erase(trapez->to_string());
}

list<shared_ptr<Trapezoid>> PointLocationTrapezoids::getIntersectedTrapezoids(const Edge& e)
{
	list<shared_ptr<Trapezoid>> intersectedTrapezoids;

	//run on the intersected trapezoids until you reach the last trapezoid the edge intersects
	for (shared_ptr<Trapezoid> trapezoid = getTrapezoid(e); trapezoid && trapezoid->getLeftp() < e.q();
		trapezoid = trapezoid->getRightp() < e ? trapezoid->getTopRight() : trapezoid->getBottomRight())
		intersectedTrapezoids.push_back(trapezoid);

	return intersectedTrapezoids;
}

void PointLocationTrapezoids::createTrapezoidsAndUpdataDataStructure(const Edge& e, list<shared_ptr<Trapezoid>> intersectedTrapezoids)
{
	list<Vertex> topVertices;
	list<Vertex> bottomVertices;

	//calculate top and bottom vertices
	auto trap_it = intersectedTrapezoids.begin();
	for (++trap_it; trap_it != intersectedTrapezoids.end(); ++trap_it)
	{
		if ((*trap_it)->getLeftp() > e)
			topVertices.push_back((*trap_it)->getLeftp());
		else
			bottomVertices.push_back((*trap_it)->getLeftp());
	}

	topVertices.push_back(e.q());
	bottomVertices.push_back(e.q());

	shared_ptr<Trapezoid> firstTrapez = intersectedTrapezoids.front();
	shared_ptr<Trapezoid> lastTrapez = intersectedTrapezoids.back();

	bool isOneTrapezoid = intersectedTrapezoids.size() == 1;
	bool ispNew = e.p() != firstTrapez->getLeftp();
	bool isqNew = e.q() != lastTrapez->getRightp();

	pair<shared_ptr<Trapezoid>, shared_ptr<Trapezoid>> lastTopAndBottomTrapezoids;

	//deal with first trapezoid
	if (isOneTrapezoid)
	{
		if (!ispNew && !isqNew)
			lastTopAndBottomTrapezoids = middleSplit(e, firstTrapez, topVertices, bottomVertices, firstTrapez->getTopLeft(), firstTrapez->getBottomLeft());
		else if (!ispNew)
			lastTopAndBottomTrapezoids = endNotConnected(e, firstTrapez, topVertices, bottomVertices, firstTrapez->getTopLeft(), firstTrapez->getBottomLeft());
		else if (!isqNew)
			lastTopAndBottomTrapezoids = startNotConnected(e, firstTrapez, topVertices, bottomVertices);
		else
			lastTopAndBottomTrapezoids = notConnectedOneTrapezoid(e, firstTrapez, topVertices, bottomVertices);
	}
	else
	{
		//deal with first trapezoid
		if (!ispNew)
			lastTopAndBottomTrapezoids = middleSplit(e, firstTrapez, topVertices, bottomVertices, firstTrapez->getTopLeft(), firstTrapez->getBottomLeft());
		else
			lastTopAndBottomTrapezoids = startNotConnected(e, firstTrapez, topVertices, bottomVertices);

		//problem: last top and bottom aren't necessarily accurate, intersected trapezoid left neighbors should be prioritized if those neighbors aren't intersected themselves.
		
		//refers to us removing the front and back and dealing with them seperatley
		intersectedTrapezoids.pop_front();
		intersectedTrapezoids.pop_back();

		//deal with middle trapezoids
		for (shared_ptr<Trapezoid> trapez : intersectedTrapezoids)
			lastTopAndBottomTrapezoids = middleSplit(e, trapez, topVertices, bottomVertices, lastTopAndBottomTrapezoids.first, lastTopAndBottomTrapezoids.second);


		//deal with last trapezoid
		if (!isqNew)//need to connect to right
			lastTopAndBottomTrapezoids = middleSplit(e, lastTrapez, topVertices, bottomVertices, lastTopAndBottomTrapezoids.first, lastTopAndBottomTrapezoids.second);
		else
			lastTopAndBottomTrapezoids = endNotConnected(e, lastTrapez, topVertices, bottomVertices, lastTopAndBottomTrapezoids.first, lastTopAndBottomTrapezoids.second);
		
	}
	//connect right neighbors to the last trapezoids
	if (lastTrapez->getTopRight() && lastTopAndBottomTrapezoids.first->getTop().q() != lastTopAndBottomTrapezoids.first->getBottom().q())
	{
		lastTrapez->getTopRight()->replaceLeftNeighbors(lastTrapez, lastTopAndBottomTrapezoids.first);
		lastTopAndBottomTrapezoids.first->setTopRight(lastTrapez->getTopRight());
		lastTopAndBottomTrapezoids.first->setBottomRight(isqNew? lastTrapez->getBottomRight() : lastTrapez->getTopRight());
	}
	if (lastTrapez->getBottomRight() && lastTopAndBottomTrapezoids.second->getTop().q() != lastTopAndBottomTrapezoids.second->getBottom().q())
	{
		lastTrapez->getBottomRight()->replaceLeftNeighbors(lastTrapez, lastTopAndBottomTrapezoids.second);
		lastTopAndBottomTrapezoids.second->setTopRight(isqNew ? lastTrapez->getTopRight() : lastTrapez->getBottomRight());
		lastTopAndBottomTrapezoids.second->setBottomRight(lastTrapez->getBottomRight());
	}
}

void PointLocationTrapezoids::connectMiddleTrapezoidToRightTrapezoids(shared_ptr<Trapezoid> origTrapez, shared_ptr<Trapezoid> trapez, bool isTop)
{
	//if the trapez isn't closed on the right (creating a triangle)
	if (trapez->getBottom().q() != trapez->getTop().q())
	{
		//if the right neighbors are also different, the new trapez might inherit one of them 
		if (origTrapez->getBottomRight() != origTrapez->getTopRight())
		{
			//if the trapezs share rightp, it means that the new trapez should inherit one of the right neighbors of the orig
			if (origTrapez->getRightp() == trapez->getRightp())
			{
				Vertex rightp = origTrapez->getRightp();
				if (isTop)
				{
					trapez->setTopRight(origTrapez->getTopRight());
					origTrapez->getTopRight()->replaceLeftNeighbors(origTrapez, trapez);
				}
				else
				{
					trapez->setBottomRight(origTrapez->getBottomRight());
					origTrapez->getBottomRight()->replaceLeftNeighbors(origTrapez, trapez);
				}
			}
		}
	}
}

shared_ptr<Leaf> PointLocationTrapezoids::getOrCreateMiddleTrapezoid(const Edge& e, shared_ptr<Trapezoid> origTrapez, shared_ptr<Trapezoid> lastTrapez, list<Vertex>& vertices, bool isTop)
{
	const Vertex& minRightp = origTrapez->getRightp() < e.q() ? origTrapez->getRightp() : e.q();
	if (lastTrapez && minRightp <= lastTrapez->getRightp())
	{
		connectMiddleTrapezoidToRightTrapezoids(origTrapez, lastTrapez, isTop);
		return lastTrapez->getLeaf();
	}

	shared_ptr<Trapezoid> trapez = addTrapezoid(Trapezoid(origTrapez->getLeftp(), vertices.front(), isTop ? origTrapez->getTop() : e, isTop ? e : origTrapez->getBottom()));
	vertices.pop_front();

	//if the trapez isn't closed on the left (creating a triangle)
	if (trapez->getBottom().p() != trapez->getTop().p())
	{
		shared_ptr<Trapezoid> topLeft = lastTrapez, bottomLeft = lastTrapez;
		//if the orig trapez left neighbors are different, the new trapez might inherit one of them
		if (origTrapez->getBottomLeft() != origTrapez->getTopLeft())
			if (isTop)
				topLeft = origTrapez->getTopLeft();
			else
				bottomLeft = origTrapez->getBottomLeft();
		
		trapez->setTopLeft(topLeft);
		trapez->setBottomLeft(bottomLeft);
		if (topLeft)
			topLeft->replaceRightNeighbors(origTrapez, trapez);
		if (bottomLeft)
			bottomLeft->replaceRightNeighbors(origTrapez, trapez);
	}

	connectMiddleTrapezoidToRightTrapezoids(origTrapez, trapez, isTop);
	return createLeaf(trapez);
}

shared_ptr<Leaf> PointLocationTrapezoids::createMiddleTrapezoidConnectedToLeftTrapezoid(const Edge& e, shared_ptr<Trapezoid> origTrapez, shared_ptr<Trapezoid> leftTrapez, const Vertex& rightp, bool isTop)
{
	shared_ptr<Trapezoid> trapez = addTrapezoid(Trapezoid(e.p(), rightp, isTop ? origTrapez->getTop() : e, isTop ? e : origTrapez->getBottom()));

	trapez->setBottomLeft(leftTrapez);
	trapez->setTopLeft(leftTrapez);

	if (isTop)
		leftTrapez->setTopRight(trapez);
	else
		leftTrapez->setBottomRight(trapez);

	connectMiddleTrapezoidToRightTrapezoids(origTrapez, trapez, isTop);

	return createLeaf(trapez);

}

void PointLocationTrapezoids::replaceNode(shared_ptr<Leaf> origNode, shared_ptr<Node> newNode)
{
	if (origNode->isRoot())
		m_tree = newNode;
	else
		replaceParentsChild(origNode, newNode);
}

shared_ptr<Leaf> PointLocationTrapezoids::createLeftTrapezoid(const Edge& e, shared_ptr<Trapezoid> origTrapez)
{
	shared_ptr<Trapezoid> trapez = addTrapezoid(Trapezoid(origTrapez->getLeftp(), e.p(), origTrapez->getTop(), origTrapez->getBottom()));

	trapez->setTopLeft(origTrapez->getTopLeft());
	trapez->setBottomLeft(origTrapez->getBottomLeft());

	if (origTrapez->getTopLeft())
		origTrapez->getTopLeft()->replaceRightNeighbors(origTrapez, trapez);

	if (origTrapez->getBottomLeft())
		origTrapez->getBottomLeft()->replaceRightNeighbors(origTrapez, trapez);

	return createLeaf(trapez);
}

shared_ptr<Leaf> PointLocationTrapezoids::createRightTrapezoid(const Edge& e, shared_ptr<Trapezoid> origTrapez, shared_ptr<Trapezoid> lastTop, shared_ptr<Trapezoid> lastBottom)
{
	shared_ptr<Trapezoid> trapez = addTrapezoid(Trapezoid(e.q(), origTrapez->getRightp(), origTrapez->getTop(), origTrapez->getBottom()));

	trapez->setTopLeft(lastTop);
	trapez->setBottomLeft(lastBottom);
	trapez->setTopRight(origTrapez->getTopRight());
	trapez->setBottomRight(origTrapez->getBottomRight());

	if (lastTop)
	{
		lastTop->setTopRight(trapez);
		lastTop->setBottomRight(trapez);

	}
	if (lastBottom)
	{
		lastBottom->setTopRight(trapez);
		lastBottom->setBottomRight(trapez);
	}


	return createLeaf(trapez);
}

pair<shared_ptr<Trapezoid>, shared_ptr<Trapezoid>> PointLocationTrapezoids::middleSplit(const Edge& e, shared_ptr<Trapezoid> origTrapez, list<Vertex>& topVertices, list<Vertex>& bottomVertices, shared_ptr<Trapezoid> lastTop, shared_ptr<Trapezoid> lastBottom)
{
	shared_ptr<Y_Node> eNode = make_shared<Y_Node>(e);

	shared_ptr<Leaf> topLeaf = getOrCreateMiddleTrapezoid(e, origTrapez, lastTop, topVertices, true);
	eNode->setLeftChild(topLeaf);

	shared_ptr<Leaf> bottomLeaf = getOrCreateMiddleTrapezoid(e, origTrapez, lastBottom, bottomVertices, false);
	eNode->setRightChild(bottomLeaf);

	replaceNode(origTrapez->getLeaf(), eNode);

	return { topLeaf->getTrapezoid(), bottomLeaf->getTrapezoid() };
}

pair<shared_ptr<Trapezoid>, shared_ptr<Trapezoid>> PointLocationTrapezoids::startNotConnected(const Edge& e, shared_ptr<Trapezoid> origTrapez, list<Vertex>& topVertices, list<Vertex>& bottomVertices)
{
	shared_ptr<X_Node> pNode = make_shared<X_Node>(e.p());

	shared_ptr<Leaf> leftLeaf = createLeftTrapezoid(e, origTrapez);
	pNode->setLeftChild(leftLeaf);

	shared_ptr<Y_Node> eNode = make_shared<Y_Node>(e);
	pNode->setRightChild(eNode);

	shared_ptr<Leaf> topLeaf = createMiddleTrapezoidConnectedToLeftTrapezoid(e, origTrapez, leftLeaf->getTrapezoid(), topVertices.front(), true);
	topVertices.pop_front();
	eNode->setLeftChild(topLeaf);

	shared_ptr<Leaf> bottomLeaf = createMiddleTrapezoidConnectedToLeftTrapezoid(e, origTrapez, leftLeaf->getTrapezoid(), bottomVertices.front(), false);
	bottomVertices.pop_front();
	eNode->setRightChild(bottomLeaf);

	replaceNode(origTrapez->getLeaf(), pNode);

	return { topLeaf->getTrapezoid(), bottomLeaf->getTrapezoid() };
}

pair<shared_ptr<Trapezoid>, shared_ptr<Trapezoid>> PointLocationTrapezoids::endNotConnected(const Edge& e, shared_ptr<Trapezoid> origTrapez, list<Vertex>& topVertices, list<Vertex>& bottomVertices, shared_ptr<Trapezoid> lastTop, shared_ptr<Trapezoid> lastBottom)
{
	shared_ptr<X_Node> qNode = make_shared<X_Node>(e.q());

	shared_ptr<Y_Node> eNode = make_shared<Y_Node>(e);
	qNode->setLeftChild(eNode);

	shared_ptr<Leaf> topLeaf = getOrCreateMiddleTrapezoid(e, origTrapez, lastTop, topVertices, true);
	eNode->setLeftChild(topLeaf);

	shared_ptr<Leaf> bottomLeaf = getOrCreateMiddleTrapezoid(e, origTrapez, lastBottom, bottomVertices, false);
	eNode->setRightChild(bottomLeaf);

	shared_ptr<Leaf> rightLeaf = createRightTrapezoid(e, origTrapez, topLeaf->getTrapezoid(), bottomLeaf->getTrapezoid());
	qNode->setRightChild(rightLeaf);

	replaceNode(origTrapez->getLeaf(), qNode);

	return { rightLeaf->getTrapezoid(), rightLeaf->getTrapezoid() };
}

pair<shared_ptr<Trapezoid>, shared_ptr<Trapezoid>> PointLocationTrapezoids::notConnectedOneTrapezoid(const Edge& e, shared_ptr<Trapezoid> origTrapez, list<Vertex>& topVertices, list<Vertex>& bottomVertices)
{
	shared_ptr<X_Node> pNode = make_shared<X_Node>(e.p());

	shared_ptr<Leaf> leftLeaf = createLeftTrapezoid(e, origTrapez);
	pNode->setLeftChild(leftLeaf);

	shared_ptr<Y_Node> eNode = make_shared<Y_Node>(e);
	pNode->setRightChild(eNode);
	
	shared_ptr<Leaf> topLeaf = createMiddleTrapezoidConnectedToLeftTrapezoid(e, origTrapez, leftLeaf->getTrapezoid(), e.q(), true);
	eNode->setLeftChild(topLeaf);

	shared_ptr<Leaf> bottomLeaf = createMiddleTrapezoidConnectedToLeftTrapezoid(e, origTrapez, leftLeaf->getTrapezoid(), e.q(), false);
	eNode->setRightChild(bottomLeaf);

	shared_ptr<X_Node> qNode = make_shared<X_Node>(e.q());
	pNode->setRightChild(qNode);
	qNode->setLeftChild(eNode);

	shared_ptr<Leaf> rightLeaf = createRightTrapezoid(e, origTrapez, topLeaf->getTrapezoid(), bottomLeaf->getTrapezoid());
	qNode->setRightChild(rightLeaf);

	replaceNode(origTrapez->getLeaf(), pNode);

	return { rightLeaf->getTrapezoid(), rightLeaf->getTrapezoid() };
}

shared_ptr<Trapezoid> PointLocationTrapezoids::getTrapezoid(const Vertex& v)
{
	return m_tree->searchTrapezoid(v);
}

shared_ptr<Trapezoid> PointLocationTrapezoids::getTrapezoid(const Edge& e)
{
	return m_tree->searchTrapezoid(e);
}

shared_ptr<const Face> PointLocationTrapezoids::query(Vertex v)
{
	shared_ptr<Trapezoid> trapez = getTrapezoid(v);

	std::cout << trapez->getBottom() << std::endl;
	return trapez->getBottom().getFace();
}

int PointLocationTrapezoids::getSize() const
{
	return m_trapezoids.size();
}