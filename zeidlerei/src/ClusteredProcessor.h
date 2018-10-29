#pragma once
#include "Processor.h"
#include "ClusteringProcess.h"

class ClusteredProcessor :
	public Processor
{
public:
	ClusteredProcessor(const std::vector<Word>& initialSet, std::vector<std::shared_ptr<Rule> >& ruleSet,
		const std::shared_ptr<Filter>& inputFilter, const std::shared_ptr<Filter>& outputFilter, const std::shared_ptr<ClusteringProcess>& clusterer, const std::string& id);
	virtual void collectOutput() override;
private:
	std::shared_ptr<ClusteringProcess> clusterer_;
};

