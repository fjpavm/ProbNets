#include "MarkovNetwork.h"

#include "TableFactor.h"

#include "../Utils/GraphVizSingleton.hpp"
#include "../Utils/JsonUtils.h"

#include <map>
#include <string>
#include <vector>

namespace prob_nets{
    
    std::map<std::string, std::string> MarkovNetwork::createSample()
    {
        std::map<std::string, std::string> sample;
        //TODO: Use MarkovBlanket and factors to calculate an instanciation
        return sample;
        
        for(int i = 0; i < m_variables.size(); i++)
        {
            sample[m_variables[i]->getName()] = m_variables[i]->getValues()[m_variables[i]->getInstanciation()];
        }
        for(int i = 0; i < m_variables.size(); i++)
        {
            m_variables[i]->clearInstanciation();
        }
        return sample;
    }
    
    void MarkovNetwork::exportPNG(const std::string& in_filename)
    {
        auto g = agopen((char *)"Markov Network", Agstrictundirected, 0);
        
        for(int i = 0; i < m_variables.size(); i++)
        {
            Agnode_t* thisNode = agnode(g, (char *)m_variables[i]->getName().c_str() , TRUE);
            for(auto variable = m_variables[i]->getMarkovBlanket().begin() ; variable != m_variables[i]->getMarkovBlanket().end(); ++variable)
            {
                if((*variable)->getName() == m_variables[i]->getName())
                {
                    continue;
                }
                Agnode_t* parentNode = agnode(g, (char *)(*variable)->getName().c_str() , TRUE);
                agedge(g, parentNode, thisNode, NULL, TRUE);
            }
        }
        
        /* Use the graph layout engine */
        gvLayout(GraphVizSingleton::getGraphVizContext(), g, "fdp");
        
        /* Output in png format */
        gvRenderFilename(GraphVizSingleton::getGraphVizContext(), g, "png", in_filename.c_str());
        gvFreeLayout(GraphVizSingleton::getGraphVizContext(), g);
        agclose(g);
    }
    
    Factor* createTableFactorFromJson(const Json& in_tableFactor, std::map<std::string, std::shared_ptr<MarkovNetVariable> > in_variableMap)
    {
        if(in_tableFactor.find("table") == in_tableFactor.end() ||
           in_tableFactor["table"].is_array() == false ||
           in_tableFactor.find("variables") == in_tableFactor.end() ||
           in_tableFactor["variables"].is_array() == false)
        {
            return nullptr;
        }
        const Json& tableJson = in_tableFactor["table"];
        
        std::vector<double> table = tableJson;
        
        const Json& variablesJson = in_tableFactor["variables"];
        std::vector< Variable* > variables;
        for(int variableIndex = 0; variableIndex < variablesJson.size(); ++variableIndex)
        {
            if(in_variableMap.find(variablesJson[variableIndex]) == in_variableMap.end()){ return nullptr; }
            variables.push_back(in_variableMap[variablesJson[variableIndex]].get());
        }
        
        return new TableFactor(variables, table);
    }
    
    bool MarkovNetwork::loadFromJsonFile(const std::string& in_filename)
    {
        m_variables.clear();
        m_factors.clear();
        Json json = JsonUtils::fromFile(in_filename);
        // TODO: extend functionality to read bayesian networks as markov networks
        if(json.is_null() || json.find("type") == json.end() || json["type"] != "MarkovNetwork"){ return false; }
        
        if(json.find("variables") == json.end() || json["variables"].is_array() == false){ return false; }
        Json& variablesJson = json["variables"];
        std::map<std::string, std::shared_ptr<MarkovNetVariable> > variableMap;
        for(int v = 0; v < variablesJson.size(); ++v)
        {
            Json& var = variablesJson[v];
            if(var.is_object() == false ||
               var.find("name") == var.end() ||
               var.find("values") == var.end() ||
               var["values"].is_array() == false)
            {
                return false;
            }
            std::vector<std::string> values = var["values"];
            std::string name = var["name"];
            std::shared_ptr< MarkovNetVariable > variable_ptr(new MarkovNetVariable(name, values));
            variableMap[name] = variable_ptr;
            m_variables.push_back(variable_ptr);
        }
        
        if(json.find("probabilities") == json.end() || json["probabilities"].is_array() == false){ return false; }
        Json& probabilities = json["probabilities"];
        std::map<Variable*, std::vector<Factor*> > variableFactorsMap;
        for(int p = 0; p < probabilities.size(); ++p)
        {
            Json& factorJson = probabilities[p];
            Factor* factor = nullptr;
            
            if(factorJson.is_object() == false ||
               factorJson.find("type") == factorJson.end())
            {
                return false;
            }
            
            if(factorJson["type"] == std::string("TableFactor"))
            {
                factor = createTableFactorFromJson(factorJson, variableMap);
                if(factor == nullptr){ return false; }
                
            }
            else // add else if to extend types of factors handled
            {
                return false;
            }
            
            const std::vector< Variable* >& vars = factor->getVariables();
            for(int v = 0; v < vars.size(); ++v)
            {
                variableFactorsMap[vars[v]].push_back(factor);
            }
            std::shared_ptr<Factor> factor_shared(factor);
            m_factors.push_back(factor_shared);
        }
        
        for(int v = 0; v < m_variables.size(); ++v)
        {
            m_variables[v]->setFactors(variableFactorsMap[m_variables[v].get()]);
        }
        
        return true;
    }
    
    bool MarkovNetwork::saveToJsonFile(const std::string& in_filename)
    {
        Json json = Json::object();
        json["type"] = "MarkovNetwork";
        Json variablesJson = Json::array();
        Json probabilitiesJson = Json::array();
        
        for(int n = 0; n < m_variables.size(); ++n)
        {
            Json variable = Json::object();
            variable["name"] = m_variables[n]->getName();
            variable["values"] = m_variables[n]->getValues();
            variablesJson.push_back(variable);
        }
        
        for(int f = 0; f < m_factors.size(); ++f)
        {
            Json factor = m_factors[f]->toJson();
            probabilitiesJson.push_back(factor);
        }
        
        json["variables"] = variablesJson;
        json["probabilities"] = probabilitiesJson;
        
        return JsonUtils::toPrettyFile(json, in_filename);
    }

}