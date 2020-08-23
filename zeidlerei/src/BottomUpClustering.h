#pragma once
#include "ClusteringProcess.h"

#include <vector>

#include "Multiset.h"
#include "Word.h"

class BottomUpClustering : public ClusteringProcess
{
public:
	BottomUpClustering(const int& k, const int& turns = INT_MAX ) : k_(k), turns_(turns) {
		if (k <= 1) {
			k_ = 1;
		}
	}
	std::vector<Cluster> createClusters(Multiset<Word> wordSet) override;
private:
	int k_;
	int turns_;

	void mergeClosestClusters(std::vector<Cluster>& clusters, Multiset<Word> m);
};

