#pragma once
#include "Processor.h"
#include "ClusteringProcess.h"

class ClusteredProcessor :
	public Processor
{
public:
	struct Configuration : public Processor::Configuration {
		std::vector<ClusteringProcess::Cluster> clusters;
		Configuration(const std::string processorId, const Multiset<Word>& wordSet,
			const std::vector<ClusteringProcess::Cluster> clusters)
			: Processor::Configuration(processorId, wordSet), clusters(clusters) {}
		virtual void accept(ConfigurationVisitor* visitor) override;
	};
	ClusteredProcessor(const std::vector<Word>& initialSet, std::vector<std::shared_ptr<Rule> >& ruleSet,
		const std::shared_ptr<Filter>& inputFilter, const std::shared_ptr<Filter>& outputFilter,
		const std::shared_ptr<ClusteringProcess>& clusterer, const std::string& id);
	virtual void collectOutput() override;
	virtual std::shared_ptr<Processor::Configuration> exportConfiguration() override;
	virtual void evolve() override;
private:
	std::shared_ptr<ClusteringProcess> clusterer_;
	std::vector<ClusteringProcess::Cluster> lastClusters_;
	int countClusterWordsInContent(const ClusteringProcess::Cluster& cluster);
};

