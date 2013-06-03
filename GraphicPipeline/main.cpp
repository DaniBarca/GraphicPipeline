//
//  main.cpp
//  GraphicPipeline
//
//  Created by Dani Barca on 21/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#include <iostream>
#include "image.hpp"
#include "framework.h"
#include "Mesh.h"
#include "Object.h"
#include "Camera.h"

#define WIDTH  500
#define HEIGHT 500

int main(int argc, const char * argv[])
{
    //Image* img = new Image(WIDTH,HEIGHT);
    
    if(argc != 2)
        std::cout << "ERROR: número de argumentos incorrecto" << std::endl;
    
    //Leer archivo
    std::string dir = argv[1];
    Object o  = Object(dir, Vector(0,0,0));
    Camera *c = new Camera(Vector(0,10,10), Vector(0,0,0));
    
	system("pause");
    return 0;
}

