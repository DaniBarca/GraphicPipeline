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

#define WIDTH  500
#define HEIGHT 500

int main(int argc, const char * argv[])
{
    //Image* img = new Image(WIDTH,HEIGHT);
    
    //Leer archivo
    Mesh m = Mesh("/Users/danibarca/Documents/Programas/GraphicPipeline/data/cono.txt");
    
	system("pause");
    return 0;
}

