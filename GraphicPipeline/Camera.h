//
//  Camera.h
//  GraphicPipeline
//
//  Created by Dani Barca - Álvaro Ibañez - Lucas Enric de Haan on 31/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#ifndef __GraphicPipeline__Camera__
#define __GraphicPipeline__Camera__

#include <iostream>
#include "framework.h"
#include "Object.h"
#include "Mesh.h"
#include "Polygon.hpp"
#include "image.hpp"

#define DISTPLANEC  3
#define IDISTPLANEC 1/DISTPLANEC


class Camera{
    struct plane{
        int width;
        int height;
        int half_width;
        int half_height;
    }plane;
    
    Image* output;
    
    void  setCUVN();
    void  renderVertexs(Object o);
public:
    Matrix* model;
    
    Vector N;
    Vector U;
    Vector V;
    Vector C;
    
    float FOV;
    float distPant;
    
    Camera(Vector position, Vector lookat, int width = 500, int height = 500);
    void setCamera(Vector position, Vector lookat);

    
    void render(Object o);
};

#endif /* defined(__GraphicPipeline__Camera__) */
