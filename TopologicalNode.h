#pragma once
#include <vector>
#include <memory>
#include "Edge.h"
#include <stack>

using std::stack;
using std::vector;
using std::shared_ptr;
using std::make_shared;

template<typename T>
class TopologicalNode
{
public:
	TopologicalNode(T type) :
		m_content(type),
		dependencies(0)
	{
	}

	int increaseDependant()
	{
		return ++dependencies;
	}

	int decreaseDependant()
	{
		return --dependencies;
	}

	bool isDependant() const
	{
		return dependencies > 0;
	}

	T getContent() const
	{
		return m_content;
	}

	void addConnection(shared_ptr<TopologicalNode> node)
	{
		m_connectedNodes.push_back(node);
		node->increaseDependant();
	}

	vector<shared_ptr<TopologicalNode<T>>> getConnections() const
	{
		return m_connectedNodes;
	}

private:
	T m_content;
	int dependencies;
	vector<shared_ptr<TopologicalNode<T>>> m_connectedNodes;
};

template<typename T>
vector<T> topologicalSortBuild(const vector<T>& contents, pair<bool, bool>(*checkConnection)(const T& t1, const T& t2))
{
	vector<shared_ptr<TopologicalNode<const T&>>> nodes;

	//create nodes
	for (const T& content : contents)
		nodes.push_back(make_shared<TopologicalNode<const T&>>(content));

	for (auto it = nodes.begin(); it < nodes.end(); ++it) {
		for (auto to_check = it + 1; to_check < nodes.end(); ++to_check)
		{
			pair<bool, bool> answer = checkConnection((*it)->getContent(), (*to_check)->getContent());
			if (answer.first)
				answer.second ? (*it)->addConnection(*to_check) : (*to_check)->addConnection(*it);
		}
	}
	
	return topologicalSort(nodes);
}

template<typename T>
vector<T> topologicalSort(vector<shared_ptr<TopologicalNode<const T&>>> nodes)
{
	vector<T> sorted_content;
	stack<shared_ptr<TopologicalNode<const T&>>> stack;

	for (shared_ptr<TopologicalNode<const T&>> node : nodes)
	{
		if (!node->isDependant())
			stack.push(node);
	}

	while (!stack.empty())
	{
		shared_ptr<TopologicalNode<const T&>> node = stack.top();
		stack.pop();

		sorted_content.push_back(node->getContent());

		for (shared_ptr<TopologicalNode<const T&>> toDecNode : node->getConnections())
		{
			if(toDecNode->decreaseDependant() == 0)
				stack.push(toDecNode);
		}
	}
	return sorted_content;
}
