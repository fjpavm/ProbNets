//
//  JsonUtils.hpp
//  ProbNets
//
//  Created by Francisco Mendonca on 01/12/2016.
//  Copyright © 2016 Francisco Mendonca. All rights reserved.
//

#ifndef JsonUtils_h
#define JsonUtils_h

#include "../json/single_include/nlohmann/json.hpp"

#include <iostream>
#include <fstream>
#include <string>

using Json = nlohmann::json;

class JsonUtils
{
 public:
    static Json fromFile(const std::string& in_filename)
    {
        Json json;
        std::ifstream jsonFile (in_filename);
        if (jsonFile.is_open())
        {
            jsonFile >> json;
            jsonFile.close();
        }
        return json;
    }
    
    static bool toFile(const Json& in_json, const std::string& in_filename)
    {
        std::ofstream jsonFile (in_filename);
        if (jsonFile.is_open())
        {
            jsonFile << in_json;
            jsonFile.close();
            return true;
        }
        return false;
    }
    
    static bool toPrettyFile(const Json& in_json, const std::string& in_filename)
    {
        std::ofstream jsonFile (in_filename);
        if (jsonFile.is_open())
        {
            jsonFile << std::setw(4) << in_json << std::endl;
            jsonFile.close();
            return true;
        }
        return false;
    }
    
    static Json fromString(const std::string& in_string)
    {
        return Json::parse(in_string);
    }
    
    static std::string toString(const Json& in_json)
    {
        return in_json.dump();
    }
    
    static std::string toPrettyString(const Json& in_json)
    {
        return in_json.dump(4);
    }
};

#endif /* JsonUtils_h */
