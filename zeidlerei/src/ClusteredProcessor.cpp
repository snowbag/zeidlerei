#include "ClusteredProcessor.h"

ClusteredProcessor::ClusteredProcessor(const std::vector<Word>& initialSet, std::vector<std::shared_ptr<Rule> >& ruleSet,
	const std::shared_ptr<Filter>& inputFilter, const std::shared_ptr<Filter>& outputFilter, const std::shared_ptr<ClusteringProcess>& clusterer, const std::string& id)
	: Processor(initialSet, ruleSet, inputFilter, outputFilter, id), clusterer_(clusterer)
{
}

void ClusteredProcessor::collectOutput() {
	if (wordSet_.size() == 0) return;
	std::vector<ClusteringProcess::Cluster> clusters = clusterer_->createClusters(wordSet_);
	auto minCluster = std::ref(clusters[0]);
	for (auto&& c : clusters) {
		if (c.points.size() < minCluster.get().points.size()) {
			minCluster = std::ref(c);
		}
	}

	for (auto&& w : minCluster.get().points) {
		if (outputFilter_->apply(w)) {
			output_.add(w, wordSet_[w]);
			wordSet_.remove(w, wordSet_[w]);
		}
	}
}