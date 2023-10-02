#include "Variable.h"

namespace prob_nets{

    int Variable::getInstanciation(){
        if(isInstanciated){
            return instanceNumber;
        }
        return -1;
    }

}