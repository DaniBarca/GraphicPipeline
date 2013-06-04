//
//  Camera.cpp
//  GraphicPipeline
//
//  Created by Dani Barca - Álvaro Ibañez - Lucas Enric de Haan on 31/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#include "Camera.h"

Camera::Camera(Vector position, Vector lookat, int width, int height){
    Matrix r = Matrix(); 
    model = new Matrix(); //posicion de la camara
    model->setPosition(-position.x, -position.y, -position.z);
    
    C = position; //vector con coordenadas x,y,z de la posicion de la camara
    
    //Obtenemos N
    N = lookat - position;
    N.norm();
    
    V = N;
    U = N;
    
    //Rotamos V 90 grados hacia arriba
    r.setRotationMatrix(DEGTORAD(90), Vector(1,0,0));
    r.rotateVector(V);
    
    //Rotamos U 90 grados hacia la derecha
    r.clean();
    r.setRotationMatrix(DEGTORAD(90), Vector(0,0,1));
    r.rotateVector(U);
    
    //Aplicamos U, V, N a la matriz:
    setUVN();
    
    //Generamos la información del plano
    plane.width  = width;
    plane.height = height;
    plane.center = position + N*DISTPLANEC;
    plane.corner = plane.center - U*(width*0.5) + V*(height*0.5);
    
    FOV = 2 * cos(DISTPLANEC / sqrt(DISTPLANEC*DISTPLANEC + (width*width)*0.25));
}

//Actualizar la matriz de vectores de la cámara
void Camera::setUVN(){    
    model->m[0] = U.x; model->m[1] = U.y; model->m[2] = U.z;
    model->m[4] = V.x; model->m[5] = V.y; model->m[6] = V.z;
    model->m[8] = N.x; model->m[9] = N.y; model->m[10]= N.z;
}

//Generar la imagen en el plano 2D
void Camera::render(Object o){
    std::vector<Vector*>* vertexs = o.getMesh()->getVertexs();

    Image *image = new Image(plane.width, plane.height);
    double dstPant;
    int x,y;
    for(int i = 0; i < vertexs->size(); ++i){
        dstPant =  (cos(FOV * 0.5) * (plane.width * 0.5)) / sin (FOV * 0.5);
        x = (vertexs->at(i)->x / vertexs->at(i)->z) * dstPant;
        y = (vertexs->at(i)->y / vertexs->at(i)->z) * dstPant;
    }
}
