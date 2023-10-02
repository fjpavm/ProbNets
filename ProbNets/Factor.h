//
//  Factor.h
//  ProbNets
//
//  Created by Francisco Mendonca on 02/12/2016.
//  Copyright © 2016 Francisco Mendonca. All rights reserved.
//

#ifndef Factor_h
#define Factor_h

#include "Variable.h"

#include "../Utils/JsonUtils.h"

#include <memory>
#include <vector>

namespace prob_nets
{
    
    class Factor
    {
     protected:
        std::vector< Variable* > variables;
     public:
        Factor(const std::vector< Variable* >& in_variables) : variables(in_variables) {};
        virtual ~Factor(){};
        const std::vector< Variable* >& getVariables() const { return variables; };
        
        virtual double getValueForInstanciation(const std::vector<int>& in_variablesInstanciationIndexes) = 0;
        
        virtual Json toJson() const = 0;
    };

}

#endif /* Factor_h */
