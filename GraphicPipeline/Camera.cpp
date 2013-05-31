//
//  Camera.cpp
//  GraphicPipeline
//
//  Created by Dani Barca on 31/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#include "Camera.h"

Camera::Camera(Vector position, Vector lookat){
    model = new Matrix();
    model->setPosition(position);
    
    N = lookat - position;
    N.norm();
    
    
}