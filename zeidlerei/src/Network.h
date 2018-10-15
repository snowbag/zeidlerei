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
	struct Configuration {
		std::vector<Processor::Configuration> nodes;
		Configuration(const std::vector<Processor*>& processors = std::vector<Processor*>())
		{
			for (auto processor : processors)
			{
				nodes.push_back(processor->exportConfiguration());
			}
		}

		bool operator==(const Configuration& other) const {
			return nodes == other.nodes;
		}
	};
	Network(std::vector<Processor*> processors, std::vector<Edge> edges);
	~Network();
	bool hasEdge(const Edge& edge);
	const std::vector<Processor*>& getProcessors();
	const std::vector<Processor*>& getNeighbours(Processor* processor);
	virtual Configuration exportConfiguration() const;
private:
	std::vector<Processor*> nodes_;
	std::map<Processor*,std::vector<Processor*> > connections_;
};

