//
//  Polygon.hpp
//  GraphicPipeline
//
//  Created by Dani Barca on 30/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#ifndef GraphicPipeline_Polygon_hpp
#define GraphicPipeline_Polygon_hpp

#include "framework.h"
#include <vector>

class Polygon{
public:
    int nSides;
    std::vector<Vector*>* vertexs;
    
    Polygon(){
        nSides = 0;
        vertexs = new std::vector<Vector*>();
    }
};

#endif
