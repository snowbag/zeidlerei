#include "ClusteredProcessor.h"
#include "Visitor.h"

ClusteredProcessor::ClusteredProcessor(const std::vector<Word>& initialSet, std::vector<std::shared_ptr<Rule> >& ruleSet,
	const std::shared_ptr<Filter>& inputFilter, const std::shared_ptr<Filter>& outputFilter, const std::shared_ptr<ClusteringProcess>& clusterer, const std::string& id)
	: Processor(initialSet, ruleSet, inputFilter, outputFilter, id), clusterer_(clusterer)
{
}

int ClusteredProcessor::countClusterWordsInContent(const ClusteringProcess::Cluster& cluster)
{
	int cardinality = 0;
	for (auto&& w : cluster.points) {
		cardinality += wordSet_[w];
	}
	return cardinality;
}

void ClusteredProcessor::collectOutput() {
	if (wordSet_.size() == 0) return;

	auto minCluster = std::ref(lastClusters_[0]);
	int minCardinality = countClusterWordsInContent(minCluster);
	for (auto&& c : lastClusters_) {
		int cardinality = countClusterWordsInContent(c);
		if (cardinality < minCardinality) {
			minCluster = std::ref(c);
			minCardinality = cardinality;
		}
	}

	for (auto&& w : minCluster.get().points) {
		if (outputFilter_->apply(w)) {
			output_.add(w, wordSet_[w]);
			wordSet_.remove(w, wordSet_[w]);
		}
	}

}

std::shared_ptr<Processor::Configuration> ClusteredProcessor::exportConfiguration()
{
	return std::make_shared<ClusteredProcessor::Configuration>(id_, wordSet_, lastClusters_);
}

void ClusteredProcessor::Configuration::accept(ConfigurationVisitor* visitor) {
	return visitor->visit(*this);
}

void ClusteredProcessor::evolve() {
	Processor::evolve();
	lastClusters_ = clusterer_->createClusters(wordSet_);
}