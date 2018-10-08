#include "stdafx.h"
#include "Network.h"

#include <algorithm>


Network::Network(std::vector<Processor> processors, std::vector<Edge> edges)
{
	nodes_ = processors;
	for (auto e : edges) {
		connections_[e.left].push_back(e.right);
		connections_[e.right].push_back(e.left);
	}
}

Network::~Network()
{
}

bool Network::hasEdge(const Edge& edge)
{
	auto v = connections_[edge.left];
	return std::find(v.begin(),v.end(), edge.right) != v.end();
}