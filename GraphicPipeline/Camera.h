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
    
    Camera(Vector position, Vector lookat, int width = 500, int height = 500);
    void setUVN();
};

#endif /* defined(__GraphicPipeline__Camera__) */
