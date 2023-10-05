#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include <vector>
#include <string>

namespace prob_nets{

    class Variable{
    protected:
        std::string name;
        std::vector<std::string> values;
        bool isInstanciated;
        int instanceNumber;
    public:
        Variable(const std::string& _name, const std::vector<std::string>& _values) : name(_name), isInstanciated(false), values(_values) {};
        virtual ~Variable(){};
        void clearInstanciation(){isInstanciated = false;};
        void setInstanciation(int number){isInstanciated = true;instanceNumber = number;};
        const std::vector<std::string>& getValues() const {return values;};
        const std::string& getName() const {return name;};
        virtual int getInstanciation();
        bool getIsInstanciated(){return isInstanciated;}
    };

}

#endif