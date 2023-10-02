//
//  TableFactor.cpp
//  ProbNets
//
//  Created by Francisco Mendonca on 02/12/2016.
//  Copyright © 2016 Francisco Mendonca. All rights reserved.
//

#include "TableFactor.h"

namespace prob_nets
{

    double TableFactor::getValueForInstanciation(const std::vector<int>& in_variablesInstanciationIndexes)
    {
        unsigned long tableIndex = 0;
        for(int v = (int)variables.size()-1; v >= 0; --v)
        {
            int mult = (int)variables[v]->getValues().size();
            tableIndex = tableIndex*mult + in_variablesInstanciationIndexes[v];
        }
        return m_table[tableIndex];
    }
    
    Json TableFactor::toJson() const
    {
        Json tableFactorJson = Json::object();
        
        tableFactorJson["type"] = "TableFactor";
        
        Json variablesJson = Json::array();
        for(int v = 0; v < variables.size(); ++v)
        {
            variablesJson.push_back(variables[v]->getName());
        }
        tableFactorJson["variables"] = variablesJson;
        tableFactorJson["table"] = m_table;
        
        return tableFactorJson;
    }
    
}