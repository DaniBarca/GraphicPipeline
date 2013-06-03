//
//  Camera.h
//  GraphicPipeline
//
//  Created by Dani Barca on 31/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#ifndef __GraphicPipeline__Camera__
#define __GraphicPipeline__Camera__

#include <iostream>
#include "framework.h"
#include "image.hpp"
#include "Object.h"
#include "Mesh.h"
#include "Polygon.hpp"


class Camera{
    struct plane{
        int width;
        int height;
        Vector center;
        Vector corner;
    }plane;
    
public:
    Matrix* model;
    
    Vector N;
    Vector U;
    Vector V;
    Vector C;
    
    Camera(Vector position, Vector lookat, int width = 500, int height = 500);
    void setUVN();
    
    void render(Object o);
};

#endif /* defined(__GraphicPipeline__Camera__) */
