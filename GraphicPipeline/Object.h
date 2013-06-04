//
//  Object.h
//  GraphicPipeline
//
//  Created by Dani Barca - Álvaro Ibañez - Lucas Enric de Haan on 21/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#ifndef __GraphicPipeline__Object__
#define __GraphicPipeline__Object__

#include <iostream>
#include <vector>
#include "framework.h"
#include "Mesh.h"

class Object{
private:
    Mesh* mesh;
    
public:
    Matrix* model;
    Object(std::string dir, Vector position);
    Mesh* getMesh(){ return mesh; }
};

#endif /* defined(__GraphicPipeline__Object__) */
