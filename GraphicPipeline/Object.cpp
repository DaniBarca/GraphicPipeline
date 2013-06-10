//
//  Object.cpp
//  GraphicPipeline
//
//  Created by Dani Barca - Álvaro Ibañez - Lucas Enric de Haan on 21/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#include "Object.h"

Object::Object(std::string dir, Vector position){
    mesh = new Mesh(dir.c_str());
    model         = new Matrix();
    rotationModel = new Matrix();
    
    model        ->setIdentity();
    rotationModel->setIdentity();
    
    model->setPosition(position);
    
    //model        ->setRotation(DEGTORAD(70 % 360), Vector(0,0,1));
    //rotationModel->setRotationMatrix(DEGTORAD(70%360), Vector(0,0,1));
}
