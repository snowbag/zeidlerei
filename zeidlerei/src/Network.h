#pragma once
#include <vector>
#include <map>
#include <iostream>

#include "Processor.h"
#include "ClusteredProcessor.h"
class Network
{
public:
	struct Edge {
		std::shared_ptr<Processor> left;
		std::shared_ptr<Processor> right;
		Edge(std::shared_ptr<Processor> l, std::shared_ptr<Processor> r) : left(l), right(r) {}
	};
	struct Configuration {
		std::vector<std::shared_ptr<Processor::Configuration> > nodes;
		Configuration(const std::vector<std::shared_ptr<Processor>>& processors = std::vector<std::shared_ptr<Processor>>())
		{
			for (auto&& processor : processors)
			{
				nodes.push_back(processor->exportConfiguration());
			}
		}

		friend std::ostream& operator<< (std::ostream& stream, const Configuration& config) {
			for (auto&& node : config.nodes)
			{
				stream << *node << "\n";
			}
			return stream;
		}

		bool operator==(const Configuration& other) const {
			if (nodes.size() != other.nodes.size()) return false;
			for (size_t i = 0; i < nodes.size(); ++i) {
				if (*nodes[i] != *other.nodes[i])
					return false;
			}
			return true;
		}
	};
	Network(std::vector<std::shared_ptr<Processor>> processors, std::vector<Edge> edges);
	~Network();
	bool hasEdge(const Edge& edge);
	const std::vector<std::shared_ptr<Processor>>& getProcessors();
	const std::vector<std::shared_ptr<Processor>>& getNeighbours(std::shared_ptr<Processor> processor);
	virtual Configuration exportConfiguration() const;
private:
	std::vector<std::shared_ptr<Processor>> nodes_;
	std::map<std::shared_ptr<Processor>,std::vector<std::shared_ptr<Processor>> > connections_;
};

