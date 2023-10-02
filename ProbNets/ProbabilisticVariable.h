#ifndef _PROBABILISTICVARIABLE_H_
#define _PROBABILISTICVARIABLE_H_

#include <memory>
#include <vector>
#include <string>

#include "Variable.h"
#include "ProbabilityDistribution.h"

namespace prob_nets{

    class ProbabilisticVariable : public Variable
    {
     protected:
        std::vector< std::shared_ptr<Variable> > parents;
        std::vector<ProbabilityDistribution> conditionalProbabilityTable;
     public:
        ProbabilisticVariable(const std::string& _name, const std::vector<std::string>& _values, const std::vector< std::shared_ptr<Variable> >& _parents, const std::vector<ProbabilityDistribution>& _conditionalProbabilityTable) :
          Variable(_name, _values), parents(_parents), conditionalProbabilityTable(_conditionalProbabilityTable) {};
        
        const std::vector< std::shared_ptr<Variable> >& getParents() const {return parents;};
        void setParents(const std::vector< std::shared_ptr<Variable> >& in_parents){ parents = in_parents; };
        const std::vector<ProbabilityDistribution>& getTable() const {return conditionalProbabilityTable;};
        void setTable(const std::vector<ProbabilityDistribution>& in_table){ conditionalProbabilityTable = in_table; }
        
        int getInstanciation();
        
    
    };

}

#endif