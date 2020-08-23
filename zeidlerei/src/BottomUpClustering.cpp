#include "BottomUpClustering.h"

#include <algorithm>
#include <set>

std::vector<ClusteringProcess::Cluster> BottomUpClustering::createClusters(Multiset<Word> wordSet) {
	std::set<Word> words;
	for (auto&& pair : wordSet) {
		words.insert(pair.first);
	}
	std::vector<Cluster> clusters;
	for (auto&& w : words) {
		clusters.push_back(Cluster{ std::vector<Word>{w} });
	}
	int i = 0;
	while (++i < turns_) {
		if (clusters.size() <= k_) {
			return clusters;
		}
		mergeClosestClusters(clusters, wordSet);
	}
	return clusters;
}

void BottomUpClustering::mergeClosestClusters(std::vector<Cluster>& clusters, Multiset<Word> m) {
	if (clusters.size() <= 1) return;

	//find closest
	int minDist = clusters[0].points[0].calculateEditDistance(clusters[1].points[0]);
	auto oneClosest = std::ref(clusters[0]), otherClosest = std::ref(clusters[1]);
	for (auto&& c1 : clusters) {
		for (auto&& c2 : clusters) {
			if (&c1 != &c2) {
				int dist = c1.points[0].calculateEditDistance(c2.points[0]);
				if (dist < minDist) {
					minDist = dist;
					oneClosest = std::ref(c1);
					otherClosest = std::ref(c2);
				}
			}
		}
	}

	for (auto&& w : otherClosest.get().points) {
		oneClosest.get().points.push_back(w);
		oneClosest.get().clustroidDistance += m[w] * oneClosest.get().points[0].calculateEditDistance(w);
	}

	//remove other
	clusters.erase(std::remove(clusters.begin(), clusters.end(), otherClosest.get()), clusters.end());
	//calculate new clustroid
	Word minWord = oneClosest.get().points[0];
	int minDistance = oneClosest.get().clustroidDistance;
	for (auto&& w : oneClosest.get().points) {
		int dist = 0;
		for (auto&& other : oneClosest.get().points) {
			dist += w.calculateEditDistance(other)*m[other];
			if (dist > minDistance) break;
		}
		if (dist < minDistance) {
			minWord = w;
			minDistance = dist;
		}
	}

	// swap old clustroid with new
	if (minWord != oneClosest.get().points[0]) {
		oneClosest.get().points.erase(std::remove(oneClosest.get().points.begin(), oneClosest.get().points.end(), minWord), oneClosest.get().points.end());
		oneClosest.get().points.push_back(oneClosest.get().points[0]);
		oneClosest.get().points[0] = minWord;
		oneClosest.get().clustroidDistance = minDistance;
	}
}