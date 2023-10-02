//
//  GraphVizSingleton.hpp
//  ProbNets
//
//  Created by Francisco Mendonca on 01/12/2016.
//  Copyright © 2016 Francisco Mendonca. All rights reserved.
//

#ifndef GraphVizSingleton_h
#define GraphVizSingleton_h

#include <graphviz/gvc.h>

class GraphVizSingleton
{
    
public:
    static GVC_t* getGraphVizContext()
    {
        static GVC_t *gvc = nullptr;
        if(gvc == nullptr)
        {
            gvc = gvContext();
        }
        return gvc;
    }
    
};

#endif /* GraphVizSingleton_h */
