#include "ProbabilisticVariable.h"
#include "ProbabilityDistribution.h"

namespace prob_nets{

    int ProbabilisticVariable::getInstanciation(){
        if(isInstanciated){
            return instanceNumber;
        }
        int tableIndex = 0;
        for(int p = (int)parents.size()-1; p >= 0; --p){
            int parentInstance = parents[p]->getInstanciation();
            if( parentInstance < 0 ) return -1;
            int mult = (int)parents[p]->getValues().size();
            tableIndex = tableIndex*mult + parentInstance;
        }
        instanceNumber = conditionalProbabilityTable[tableIndex].getRandom();
        isInstanciated = true;
        return instanceNumber;
    };

}