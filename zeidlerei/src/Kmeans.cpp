#include "Kmeans.h"

#include <algorithm>

std::vector<ClusteringProcess::Cluster> Kmeans::createClusters(Multiset<Word> wordSet)
{
	std::set<Word> words;
	for (auto&& pair : wordSet) {
		words.insert(pair.first);
	}
	std::set<Word> clustroids = sample(words, k_);
	std::vector<Cluster> clusters = clusterWords(wordSet, clustroids, words);

	//calculate new clustroids
	std::set<Word> newClustroids;
	int i = 0;
	while (++i < turns_) {
		for (auto&& c : clusters) {
			Word minWord = c.points[0];
			int minDistance = c.clustroidDistance;
			for (auto&& w : c.points) {
				int dist = 0;
				for (auto&& other : c.points) {
					dist += w.calculateEditDistance(other)*wordSet[other];
					if (dist > minDistance) break;
				}
				if (dist < minDistance) {
					minWord = w;
					minDistance = dist;
				}
			}
			newClustroids.insert(minWord);
		}
		if (newClustroids == clustroids) break;
		clustroids.clear();
		clustroids.insert(newClustroids.begin(), newClustroids.end());
		newClustroids.clear();
		clusters = clusterWords(wordSet, clustroids, words);
	}
	return clusters;
}

std::vector<ClusteringProcess::Cluster> Kmeans::clusterWords(Multiset<Word>& m, std::set<Word>& clustroids, std::set<Word> words) {
	std::vector<Cluster> clusters;
	for (auto&& w : clustroids) {
		clusters.push_back(Cluster{ std::vector<Word>{w} });
	}
	for (auto&& w : words) {
		if (clustroids.find(w) == clustroids.end()) {
			int minDistance = w.calculateEditDistance(clusters[0].points[0]);
			auto closestCluster = std::ref(clusters[0]);
			for (auto c = clusters.begin() + 1; c < clusters.end(); ++c) {
				int distance = w.calculateEditDistance(c->points[0]);
				if (distance < minDistance) {
					minDistance = distance;
					closestCluster = std::ref(*c);
				}
			}
			closestCluster.get().points.push_back(w);
			closestCluster.get().clustroidDistance += m[w] * minDistance;
		}
	}
	return clusters;
}

std::set<Word> Kmeans::sample(std::set<Word> m, const int& n)
{
	std::set<Word> result;
	int numberOfUniques = m.size();
	if (n > numberOfUniques) {
		for (auto w : m) {
			result.insert(w);
		}
	}
	else if (n > numberOfUniques / 2) {
		std::set<Word> except;
		while (except.size() < numberOfUniques - n) {
			except.insert(selectRandomWord(m));
		}
		for (auto w : m) {
			if (except.find(w) == except.end()) {
				result.insert(w);
			}
		}
	}
	else {
		while (result.size() < n) {
			result.insert(selectRandomWord(m));
		}
	}

	return result;
}

Word Kmeans::selectRandomWord(std::set<Word> m)
{
	auto start = m.begin();
	auto end = m.end();
	std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
	std::advance(start, dis(gen));
	return *start;
}