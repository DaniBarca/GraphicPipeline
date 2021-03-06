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

#define WIDTH  600
#define HEIGHT 600

int main(int argc, const char * argv[])
{    
    if(argc != 3)
        std::cout << "ERROR: número de argumentos incorrecto" << std::endl;
    
    //Leer archivo
    std::string dir    = argv[1];
    std::string outdir = argv[2];
    //Delante -0.5, -0.5, -0.5   /// 20,0,0
    //Arriba
    
    Object o = Object(dir, Vector(-0.5,-0.5,-0.5));
    Camera *c = new Camera(Vector(20,5,5), Vector(0,0,0), outdir, WIDTH, HEIGHT,true);
    
    //El último parametro del constructor invierte las normales, por defecto false
    //Camera *c = new Camera(Vector(20,1,10), Vector(0,0,0), outdir, WIDTH, HEIGHT, true);
    
    c->render(o);
    
	system("pause");
    return 0;
}

