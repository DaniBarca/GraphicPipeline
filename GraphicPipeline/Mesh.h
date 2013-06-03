//
//  Mesh.h
//  GraphicPipeline
//
//  Created by Dani Barca on 30/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#ifndef __GraphicPipeline__Mesh__
#define __GraphicPipeline__Mesh__

#include <iostream>
#include "textParser/text.h"
#include "framework.h"
#include <vector>
#include "Polygon.hpp"

class Mesh{
    int nVertexs;
    int nPolygons;
    
    std::vector<Vector*>*  vertexs;
    std::vector<Polygon*>* polygons;
    
public:
    Mesh(std::string dir);
    bool parseFile(std::string dir);
    
    std::vector<Vector*>* getVertexs(){ return vertexs; }
};

#endif /* defined(__GraphicPipeline__Mesh__) */
