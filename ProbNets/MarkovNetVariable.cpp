#include "MarkovNetVariable.h"
#include "Factor.h"

namespace prob_nets{

    void MarkovNetVariable::setFactors(const std::vector< Factor* >& in_factors)
    {
        // Go through factors and create markov blanket
        markovBlanket.clear();
        for(int f = 0; f < in_factors.size(); ++f)
        {
            const std::vector< Variable* >& variables = in_factors[f]->getVariables();
            markovBlanket.insert(variables.begin(), variables.end());
        }
        factors = in_factors;
    }
    
}