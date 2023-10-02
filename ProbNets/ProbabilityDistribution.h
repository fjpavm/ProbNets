#ifndef _PROBABILITYDISTRIBUTION_H_
#define _PROBABILITYDISTRIBUTION_H_

#include <vector>


namespace prob_nets{

    class ProbabilityDistribution{
    protected:
        std::vector<double> probDist;
    public:
        ProbabilityDistribution(std::vector<double> _probDist) : probDist(_probDist) {};
        const std::vector<double>& getProbabilityDistributionTable() const { return probDist; };
        
        int getRandom();
        
    };

}

#endif