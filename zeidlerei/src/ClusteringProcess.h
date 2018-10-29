#pragma once
#include <vector>
#include "Multiset.h"
#include "Word.h"

class ClusteringProcess
{
public:
	struct Cluster {
		std::vector<Word> points;
		int clustroidDistance; //TODO modify: when point added, add distance
		bool operator==(const Cluster& other) {
			return this->points == other.points;
		}
	};
	virtual std::vector<Cluster> createClusters(Multiset<Word> wordSet) = 0;
};

