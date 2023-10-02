#ifndef _MARKOV_NETWORK_H_
#define _MARKOV_NETWORK_H_

#include "MarkovNetVariable.h"
#include "Factor.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace prob_nets{
    
    class MarkovNetwork{
    protected:
        std::vector< std::shared_ptr<MarkovNetVariable> > m_variables;
        std::vector< std::shared_ptr<Factor> > m_factors;
    public:
        MarkovNetwork(const std::vector< std::shared_ptr<MarkovNetVariable> >& in_variables = std::vector< std::shared_ptr<MarkovNetVariable> >(),
                      const std::vector< std::shared_ptr<Factor> >& in_factors = std::vector< std::shared_ptr<Factor> >() )
        : m_variables(in_variables)
        , m_factors(in_factors) {};
        
        std::map<std::string, std::string> createSample();
        void exportPNG(const std::string& in_filename);
        bool loadFromJsonFile(const std::string& in_filename);
        bool saveToJsonFile(const std::string& in_filename);
    };
    
}

#endif