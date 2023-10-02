#ifndef _BAYESIAN_NETWORK_H_
#define _BAYESIAN_NETWORK_H_

#include "ProbabilisticVariable.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace prob_nets{
    
    class BayesianNetwork{
    protected:
        std::vector< std::shared_ptr<ProbabilisticVariable> > m_nodes;
    public:
        BayesianNetwork(const std::vector< std::shared_ptr<ProbabilisticVariable> >& in_nodes = std::vector< std::shared_ptr<ProbabilisticVariable> >()) : m_nodes(in_nodes) {};
        std::map<std::string, std::string> createSample();
        void exportPNG(const std::string& in_filename);
        bool loadFromJsonFile(const std::string& in_filename);
        bool saveToJsonFile(const std::string& in_filename);
    };
    
}

#endif