#pragma once
#include <vector>
#include <map>


#include <iostream>
#include "Processor.h"

class Network
{
public:
	struct Edge {
		Processor* left;
		Processor* right;
		Edge(Processor* l, Processor* r) : left(l), right(r) {}
	};
	Network(std::vector<Processor*> processors, std::vector<Edge> edges);
	~Network();
	bool hasEdge(const Edge& edge);
	const std::vector<Processor*>& getProcessors();
private:
	std::vector<Processor*> nodes_;
	std::map<Processor*,std::vector<Processor*> > connections_;
};

