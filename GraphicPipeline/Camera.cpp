//
//  Camera.cpp
//  GraphicPipeline
//
//  Created by Dani Barca - Álvaro Ibañez - Lucas Enric de Haan on 31/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#include "Camera.h"

Camera::Camera(Vector position, Vector lookat, int width, int height){
    model = new Matrix(); //posicion de la camara
    model->setPosition(-position.x, -position.y, -position.z);
    
    C = position; //vector con coordenadas x,y,z de la posicion de la camara
    
    //Obtenemos N
    N = lookat - position;
    N.norm();
    
    V = N * Vector(0,1,0);
    U = N * Vector(0,0,1);
    
    //U.printVector();
    //V.printVector();
    //N.printVector();
    
    //Aplicamos U, V, N a la matriz:
    setCUVN();
    
    //Generamos la información del plano
    plane.width  = width;
    plane.height = height;
    plane.center = position + N*DISTPLANEC;
    plane.corner = plane.center - U*(width*0.5) + V*(height*0.5);
    
    std::cout << "Matrix: "<<std::endl;
    //model->printMatrix();
    
    FOV = 2 * cos(DISTPLANEC / sqrt(DISTPLANEC*DISTPLANEC + (width*width)*0.25));
    //FOV  = 0.838;
}

//Actualizar la matriz de vectores de la cámara
void Camera::setCUVN(){
    Matrix r = Matrix();
    Matrix t = Matrix();
    Matrix rt= Matrix();
    
    t.setIdentity();
    r.setIdentity();
    
    t.m[3] = -C.x;
    t.m[7] = -C.y;
    t.m[11]= -C.z;
    
    r.m[0] = U.x; r.m[1] = U.y; r.m[2] = U.z;
    r.m[4] = V.x; r.m[5] = V.y; r.m[6] = V.z;
    r.m[8] = N.x; r.m[9] = N.y; r.m[10]= N.z;
    
    std::cout<<"---------"<<std::endl;
    r.printMatrix();
        std::cout<<"---------"<<std::endl;
    t.printMatrix();
        std::cout<<"---------"<<std::endl;
    
    rt = r*t;
    
    rt.printMatrix();
    
    model->copy(rt);
}

//Generar la imagen en el plano 2D
void Camera::render(Object o){
    std::vector<Vector*>* vertexs = o.getMesh()->getVertexs();

    Image *image = new Image(plane.width, plane.height);
    image->setBlack();
    
    float distPant = (cos(FOV * 0.5) * (plane.width * 0.5)) / sin (FOV * 0.5);
    //float distPant = (plane.height*0.5)/tan(DEGTORAD(FOV * 0.5));
    int x,y;
    float fx, fy, w;
    Vector vaux;
    
    std::cout << "--------------" << std::endl;
    
    for(int i = 0; i < vertexs->size(); ++i){
        vaux = *vertexs->at(i);                 //Obtenemos el vertice i
        
        vaux = *o.model * vaux;                 //Lo multiplicamos por la matriz del objeto
        vaux = *model * vaux;                   //Lo multiplicamos por la matriz de la camara
        
        w = vaux.z * IDISTPLANEC;               //Obtenemos la w
        std::cout << "w: " << w << std::endl;
        
        fx = (vaux.x/w)*distPant+ plane.width * 0.5;     //Obtenemos x
        fy = (vaux.y/w)*distPant+ plane.height* 0.5;     //Obtenemos y
        
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
