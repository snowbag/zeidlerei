#pragma once
#include "ClusteringProcess.h"

#include <random>
#include <vector>
#include <set>

#include "Multiset.h"
#include "Word.h"

class Kmeans : public ClusteringProcess
{
public:
	Kmeans(const int& k, const int& turns = INT_MAX) : k_(k), turns_(turns) {}
	std::vector<Cluster> createClusters(Multiset<Word> wordSet) override;

private:
	std::default_random_engine gen = std::default_random_engine(std::random_device()());
	int k_;
	int turns_;

	std::vector<Cluster> clusterWords(Multiset<Word>& m, std::set<Word>& clustroids, std::set<Word> words);
	std::set<Word> sample(std::set<Word> m, const int& n);
	Word selectRandomWord(std::set<Word> m);
};