//
//  Object.cpp
//  GraphicPipeline
//
//  Created by Dani Barca - Álvaro Ibañez - Lucas Enric de Haan on 21/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#include "Object.h"

Object::Object(std::string dir, Vector position){
    mesh  = new Mesh(dir.c_str());
    model = new Matrix();
    
    model->setIdentity();
    
    model->setPosition(position);
    
    //Asigna una rotación. Tengase en cuenta el objeto no necesariamente está centrado en 0,0,0
    //así que podría desplazarse también al rotarlo
    //son un ejemplo cono.txt o la tetera
    //model->setRotation(DEGTORAD(-90), Vector(0,1,0));
}
