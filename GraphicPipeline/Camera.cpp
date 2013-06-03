//
//  Camera.cpp
//  GraphicPipeline
//
//  Created by Dani Barca on 31/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#include "Camera.h"

Camera::Camera(Vector position, Vector lookat, int width, int height){
    Matrix r = Matrix();
    model = new Matrix();
    model->setPosition(-position.x, -position.y, -position.z);
    
    C = position;
    
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
    
    //Aplicamos U, V, N a la matriz:
    setUVN();
    
    //Generamos la información del plano
    plane.width  = width;
    plane.height = height;
    plane.center = position + N*5;
    plane.corner = plane.center + U*(width*0.5) + V*(height*0.5);
}

void Camera::setUVN(){    
    model->m[0] = U.x; model->m[1] = U.y; model->m[2] = U.z;
    model->m[4] = V.x; model->m[5] = V.y; model->m[6] = V.z;
    model->m[8] = N.x; model->m[9] = N.y; model->m[10]= N.z;
}

void Camera::render(Object o){
    std::vector<Vector*>* vertexs = o.getMesh()->getVertexs();
    
    for(int i = 0; i < vertexs->size(); ++i){
        linePlaneIntersection(C, N, plane.center, N);
    }
}
