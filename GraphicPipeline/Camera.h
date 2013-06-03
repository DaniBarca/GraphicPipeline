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
public:
    Matrix* model;
    
    Vector N;
    Vector U;
    Vector V;
    
    Camera(Vector position, Vector lookat);
    void setUVN();
};

#endif /* defined(__GraphicPipeline__Camera__) */
