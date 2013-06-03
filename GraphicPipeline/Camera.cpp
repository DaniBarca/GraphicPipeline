//
//  Camera.cpp
//  GraphicPipeline
//
//  Created by Dani Barca on 31/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#include "Camera.h"

Camera::Camera(Vector position, Vector lookat){
    Matrix r = Matrix();
    model = new Matrix();
    model->setPosition(position);
    
    //Obtenemos N
    N = lookat - position;
    N.norm();
    
    V = N;
    U = N;
    
    //Rotamos V
    r.setRotationMatrix(DEGTORAD(90), Vector(1,0,0));
    r.rotateVector(V);
    
    //Rotamos U
    r.clean();
    r.setRotationMatrix(DEGTORAD(90), Vector(0,0,1));
    r.rotateVector(U);
}
