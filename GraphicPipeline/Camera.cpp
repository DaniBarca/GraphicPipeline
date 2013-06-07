//
//  Camera.cpp
//  GraphicPipeline
//
//  Created by Dani Barca - Álvaro Ibañez - Lucas Enric de Haan on 31/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#include "Camera.h"

Camera::Camera(Vector position, Vector lookat, int width, int height){
    setCamera(position, lookat);
    
    //Generamos la información del plano
    //Si calculamos ahora la mitad de la altura y el ancho, no tendremos que hacerlo en cada render
    plane.width  = width;
    plane.height = height;
    plane.half_width  = width  * 0.5;
    plane.half_height = height * 0.5;
    
    FOV = 2 * cos(DISTPLANEC / sqrt(DISTPLANEC*DISTPLANEC + (width*width)*0.25));
    distPant = (cos(FOV * 0.5) * (plane.width * 0.5)) / sin (FOV * 0.5);
}

void Camera::setCamera(Vector position, Vector lookat){
    model = new Matrix(); //posicion de la camara
    
    C = position; //vector con coordenadas x,y,z de la posicion de la camara
    
    //Obtenemos N
    N = lookat - position;
    N.norm();
    
    V = N * Vector(0,1,0);
    U = N * Vector(0,0,1);
    
    //Aplicamos U, V, N a la matriz:
    setCUVN();
}

//Actualizar la matriz de vectores de la cámara
void Camera::setCUVN(){
    Matrix r = Matrix();
    Matrix t = Matrix();
    Matrix rt= Matrix();
    
    t.setIdentity();
    r.setIdentity();
    
    //Matriz de traslación de la cámara:
    t.m[3] = -C.x;
    t.m[7] = -C.y;
    t.m[11]= -C.z;
    
    //Matriz de rotación de la cámara:
    r.m[0] = U.x; r.m[1] = U.y; r.m[2] = U.z;
    r.m[4] = V.x; r.m[5] = V.y; r.m[6] = V.z;
    r.m[8] = N.x; r.m[9] = N.y; r.m[10]= N.z;
    
    rt = r*t;
    model->copy(rt);
}

//Generar la imagen en el plano 2D
void Camera::render(Object o){
    std::vector<Vector*>* vertexs = o.getMesh()->getVertexs();

    Image *image = new Image(plane.width, plane.height);
    image->setBlack();
    
    int x,y;
    float fx, fy, w;
    Vector vaux;
    
    std::cout << "--------------" << std::endl;
    
    for(int i = 0; i < vertexs->size(); ++i){
        vaux = *vertexs->at(i);                 //Obtenemos el vertice i
        
        vaux = *o.model * vaux;                 //Lo multiplicamos por la matriz del objeto
        vaux = *model * vaux;                   //Lo multiplicamos por la matriz de la camara
        
        w = vaux.z * IDISTPLANEC;               //Obtenemos la w
        
        fx = (vaux.x/w)*distPant+ plane.half_width;     //Obtenemos x
        fy = (vaux.y/w)*distPant+ plane.half_height;     //Obtenemos y
        
        //Y los redondeamos:
        x  = (int)((fx < 0) ? fx - 0.5 : fx + 0.5);
        y  = (int)((fy < 0) ? fy - 0.5 : fy + 0.5);
        
        std::cout << "x: " << x << " y: " << y << std::endl;
        
        //Por último, si están dentro del viewPlane, los dibujamos
        if(x < 500 && y < 500 && x >= 0 && y >= 0){
            if(i==4)
                image->setPixel(Color(255,0,0), x, y);
            else
                image->setPixel(Color(255,255,255), x, y);
        }
        
        
    }
    
    image->saveTGA("/Users/danibarca/Desktop/result1010.tga");
}
