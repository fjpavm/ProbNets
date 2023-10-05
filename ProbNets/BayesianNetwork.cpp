#include "BayesianNetwork.h"

#include "../Utils/GraphVizSingleton.hpp"
#include "../Utils/JsonUtils.h"

#include <map>
#include <string>
#include <vector>

namespace prob_nets{

    std::map<std::string, std::string> BayesianNetwork::createSample()
    {
        // Register not instanciated variables so only they get cleared.
        // This alows keeping pre-instanciated variables across several samples as evidence
        std::vector<size_t> not_instanciated;
        for(int i = 0; i < m_nodes.size(); i++)
        {
            if(m_nodes[i]->getIsInstanciated() == false){
                not_instanciated.push_back(i);
            }
        }

        std::map<std::string, std::string> sample;
        for(int i = 0; i < m_nodes.size(); i++)
        {
            sample[m_nodes[i]->getName()] = m_nodes[i]->getValues()[m_nodes[i]->getInstanciation()];
        }

        // clear previously non instanciated
        for(int i = 0; i < not_instanciated.size(); i++)
        {
            m_nodes[not_instanciated[i]]->clearInstanciation();
        }
        return sample;
    }
    
    void BayesianNetwork::exportPNG(const std::string& in_filename)
    {
        auto g = agopen((char *)"Bayesian Network", Agdirected, 0);
        
        for(int i = 0; i < m_nodes.size(); i++)
        {
            Agnode_t* thisNode = agnode(g, (char *)m_nodes[i]->getName().c_str() , TRUE);
            for(int p = 0; p < m_nodes[i]->getParents().size(); ++p)
            {
                Agnode_t* parentNode = agnode(g, (char *)m_nodes[i]->getParents()[p]->getName().c_str() , TRUE);
                agedge(g, parentNode, thisNode, NULL, TRUE);
            }
        }
        
        /* Use the directed graph layout engine */
        gvLayout(GraphVizSingleton::getGraphVizContext(), g, "dot");
        
        /* Output in png format */
        gvRenderFilename(GraphVizSingleton::getGraphVizContext(), g, "png", in_filename.c_str());
        gvFreeLayout(GraphVizSingleton::getGraphVizContext(), g);
        agclose(g);
    }
    
    bool BayesianNetwork::loadFromJsonFile(const std::string& in_filename)
    {
        m_nodes.clear();
        Json json = JsonUtils::fromFile(in_filename);
        if(json.is_null() || json.find("type") == json.end() || json["type"] != "BayesianNetwork"){ return false; }
        
        if(json.find("variables") == json.end() || json["variables"].is_array() == false){ return false; }
        Json& variables = json["variables"];
        std::vector<prob_nets::ProbabilityDistribution> probabilityTable;
        std::vector< std::shared_ptr< prob_nets::Variable> > parents;
        std::map<std::string, std::shared_ptr<ProbabilisticVariable> > nodes;
        for(int v = 0; v < variables.size(); ++v)
        {
            Json& var = variables[v];
            if(var.is_object() == false ||
               var.find("name") == var.end() ||
               var.find("values") == var.end() ||
               var["values"].is_array() == false)
            {
                return false;
            }
            std::vector<std::string> values = var["values"];
            std::string name = var["name"];
            std::shared_ptr< prob_nets::ProbabilisticVariable > variable_ptr(new prob_nets::ProbabilisticVariable(name, values, parents, probabilityTable));
            nodes[name] = variable_ptr;
            m_nodes.push_back(variable_ptr);
        }
        
        if(json.find("probabilities") == json.end() || json["probabilities"].is_array() == false){ return false; }
        Json& probabilities = json["probabilities"];
        for(int p = 0; p < probabilities.size(); ++p)
        {
            Json& cdt = probabilities[p];
            if(cdt.is_object() == false ||
               cdt.find("type") == cdt.end() ||
               (cdt["type"] != std::string("cdt") && cdt["type"] != std::string("CDT")) ||
               cdt.find("table") == cdt.end() ||
               cdt["table"].is_array() == false ||
               cdt.find("variable") == cdt.end() ||
               cdt["variable"].is_string() == false)
            {
                return false;
            }
            Json& table = cdt["table"];
            parents.clear(); probabilityTable.clear();
            for(int t = 0; t < table.size(); ++t)
            {
                std::vector<double> probDist = table[t];
                probabilityTable.push_back( ProbabilityDistribution(probDist) );
            }
            if(cdt.find("parents") != cdt.end() && cdt["parents"].is_array())
            {
                Json& parentsJson = cdt["parents"];
                for(int parentIndex = 0; parentIndex < parentsJson.size(); ++parentIndex)
                {
                    if(nodes.find(parentsJson[parentIndex]) == nodes.end()){ return false; }
                    parents.push_back(nodes[parentsJson[parentIndex]]);
                }
            }
            if(nodes.find(cdt["variable"]) == nodes.end()){ return false; }
            const std::shared_ptr<ProbabilisticVariable>& node = nodes[cdt["variable"]];
            node->setParents(parents);
            node->setTable(probabilityTable);
        }
        
        return true;
    }
    bool BayesianNetwork::saveToJsonFile(const std::string& in_filename)
    {
        Json json = Json::object();
        json["type"] = "BayesianNetwork";
        Json variablesJson = Json::array();
        Json probabilitiesJson = Json::array();
        
        for(int n = 0; n < m_nodes.size(); ++n)
        {
            Json variable = Json::object();
            variable["name"] = m_nodes[n]->getName();
            variable["values"] = m_nodes[n]->getValues();
            variablesJson.push_back(variable);
            
            Json cdt = Json::object();
            cdt["type"] = "CDT";
            cdt["variable"] = m_nodes[n]->getName();
            Json cdtTable = Json::array();
            if(m_nodes[n]->getParents().size() == 0)
            {
                Json probDist = m_nodes[n]->getTable()[0].getProbabilityDistributionTable();
                cdtTable.push_back(probDist);
            }
            else
            {
                Json parents = Json::array();
                for(int p = 0; p < m_nodes[n]->getParents().size(); ++p)
                {
                    parents.push_back(m_nodes[n]->getParents()[p]->getName());
                }
                cdt["parents"] = parents;
                for(int t = 0; t < m_nodes[n]->getTable().size(); ++t)
                {
                    Json probDist = m_nodes[n]->getTable()[t].getProbabilityDistributionTable();
                    cdtTable.push_back(probDist);
                }
            }
            cdt["table"] = cdtTable;
            probabilitiesJson.push_back(cdt);
        }
        
        json["variables"] = variablesJson;
        json["probabilities"] = probabilitiesJson;
        
        return JsonUtils::toPrettyFile(json, in_filename);
    }

}