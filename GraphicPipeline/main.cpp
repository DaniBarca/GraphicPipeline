//
//  main.cpp
//  GraphicPipeline
//
//  Created by Dani Barca - Álvaro Ibañez - Lucas Enric de Haan on 21/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#include <iostream>
#include "framework.h"
#include "Mesh.h"
#include "Object.h"
#include "Camera.h"

#define WIDTH  500
#define HEIGHT 500

int main(int argc, const char * argv[])
{
    //Image* img = new Image(WIDTH,HEIGHT);
    
    if(argc != 3)
        std::cout << "ERROR: número de argumentos incorrecto" << std::endl;
    
    //Leer archivo
    std::string dir = argv[1];
    std::string outdir = argv[2];
    Object o = Object(dir, Vector(0,0,0));
    Camera *c = new Camera(Vector(10,4,1), Vector(0,0,0), outdir, WIDTH, HEIGHT);
    c->render(o);
    
	system("pause");
    return 0;
}

