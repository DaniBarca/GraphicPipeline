//
//  Polygon.hpp
//  GraphicPipeline
//
//  Created by Dani Barca - Álvaro Ibañez - Lucas Enric de Haan on 30/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#ifndef GraphicPipeline_Polygon_hpp
#define GraphicPipeline_Polygon_hpp

#include "framework.h"
#include <vector>

class Polygon{    
public:
    int nSides;
    std::vector<int>* vertexs;
    Vector normal;
    
    Polygon(){
        nSides = 0;
        vertexs = new std::vector<int>();
    }
    
    void getNormal(){
        Vector v1 = vertexs->at(1) - vertexs->at(0);
        Vector v2 = vertexs->at(2) - vertexs->at(1);
        
        normal = v1 * v2;
    }
};

#endif
