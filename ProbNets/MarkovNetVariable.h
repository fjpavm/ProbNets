#ifndef _MARKOVNETVARIABLE_H_
#define _MARKOVNETVARIABLE_H_

#include <memory>
#include <vector>
#include <string>
#include <set>

#include "Factor.h"
#include "Variable.h"

namespace prob_nets{

    
    class MarkovNetVariable : public Variable
    {
     protected:
        std::vector< Factor* > factors;
        std::set< Variable* > markovBlanket;
     public:
        MarkovNetVariable(const std::string& _name, const std::vector<std::string>& _values) :
          Variable(_name, _values) {};
        
        const std::vector< Factor* >& getFactors() const {return factors;};
        void setFactors(const std::vector< Factor* >& in_factors);
        const std::set< Variable* >& getMarkovBlanket() const {return markovBlanket;};
    
    };

}

#endif