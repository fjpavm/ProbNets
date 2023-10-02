//
//  main.cpp
//  ProbNets
//
//  Created by Francisco Mendonca on 30/11/2016.
//  Copyright © 2016 Francisco Mendonca. All rights reserved.
//

#include "Utils/JsonUtils.h"
#include "ProbNets/BayesianNetwork.h"
#include "ProbNets/MarkovNetwork.h"

#include <cstdio>
#include <map>
#include <memory>
#include <vector>

int main(int argc, const char * argv[]) {

    prob_nets::BayesianNetwork bayesNet;
    bayesNet.loadFromJsonFile("ExampleNetworks/BayesianNetworks/bayes1.json");
    //bayesNet.saveToJsonFile("bayes1.json");
    bayesNet.exportPNG("bayes1.png");
    
    for(int n = 0; n < 4; n++)
    {
        std::map<std::string, std::string> sample = bayesNet.createSample();
        for(auto it =sample.begin(); it != sample.end(); ++it)
        {
            printf("%s = %s, ", it->first.c_str(), it->second.c_str());
        }
        printf("\n");
    }
    
    prob_nets::MarkovNetwork markovNet1;
    markovNet1.loadFromJsonFile("ExampleNetworks/MarkovNetworks/Title.json");
    //markovNet1.saveToJsonFile("Title.json");
    markovNet1.exportPNG("Title.png");
    /**
    Json j = JsonUtils::fromFile("Title.json");
    std::string jsonString = JsonUtils::toPrettyString(j);
    printf("%s\n", jsonString.c_str());
    /**/
    return 0;
}
