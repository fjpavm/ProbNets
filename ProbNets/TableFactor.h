//
//  TableFactor.h
//  ProbNets
//
//  Created by Francisco Mendonca on 02/12/2016.
//  Copyright © 2016 Francisco Mendonca. All rights reserved.
//

#ifndef TableFactor_h
#define TableFactor_h

#include "Factor.h"

#include <vector>

namespace prob_nets
{
    
    class TableFactor : public Factor
    {
    protected:
        std::vector<double> m_table;
    public:
        TableFactor(const std::vector< Variable* >& in_variables, const std::vector<double>& in_table) : Factor(in_variables), m_table(in_table) {}
        
        double getValueForInstanciation(const std::vector<int>& in_variablesInstanciationIndexes);
        
        Json toJson() const;
    };
    
}

#endif /* TableFactor_h */
