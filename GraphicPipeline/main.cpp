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

#define WIDTH  500
#define HEIGHT 500

int main(int argc, const char * argv[])
{
    //Image* img = new Image(WIDTH,HEIGHT);
    
    //Leer archivo
    Vector a = Vector(2,2,2);
    a.norm();
    
    std::cout << "x " << a.x << " y " << a.y << " z " << a.z;
    
    return 0;
}

