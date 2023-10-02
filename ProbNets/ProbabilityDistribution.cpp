#include "ProbabilityDistribution.h"

#include <cstdlib>

namespace prob_nets{

    int ProbabilityDistribution::getRandom(){
        double sum = 0;
        double rnd = (((double)rand())/(((unsigned long)RAND_MAX)+1));
        int returnNr;
        for(returnNr = 0; returnNr < probDist.size() ; returnNr++){
            sum += probDist[returnNr];
            if(rnd < sum) break;
        }
        return returnNr;
    }
}