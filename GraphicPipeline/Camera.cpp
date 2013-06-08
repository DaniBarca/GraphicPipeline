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
    
    output = new Image(width, height);
    output->setBlack();
    
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
    renderVertexs(o);
    rasterizePolygons(o);
    
    output->saveTGA("/Users/danibarca/Desktop/result1010.tga");
}

void Camera::renderVertexs(Object o){
    std::vector<Vector*>* vertexs = o.getMesh()->getVertexs();
    
    int x,y;
    float fx, fy, w;
    Vector vaux;
    
    scrPosition auxPosition;
    
    for(int i = 0; i < vertexs->size(); ++i){
        vaux = *vertexs->at(i);                 //Obtenemos el vertice i
        
        vaux = *o.model * vaux;                 //Lo multiplicamos por la matriz del objeto
        vaux = *model * vaux;                   //Lo multiplicamos por la matriz de la camara
        
        w = vaux.z * IDISTPLANEC;               //Obtenemos la w
        
        fx = (vaux.x/w)*distPant + plane.half_width;      //Obtenemos x
        fy = (vaux.y/w)*distPant + plane.half_height;     //Obtenemos y
        
        //Y los redondeamos:
        x  = round(fx);
        y  = round(fy);
        
        auxPosition.x = x;
        auxPosition.y = y;
        
        o.mesh->positions->at(i) = auxPosition;
        
        //Por último, si están dentro del viewPlane, los dibujamos
        if(x < 500 && y < 500 && x >= 0 && y >= 0){
            if(i==4)
                output->setPixel(Color(255,0,0), x, y);
            else
                output->setPixel(Color(255,255,255), x, y);
        }
    }
}

void Camera::rasterizePolygons(Object o){
    std::vector<Polygon*>* polygons = o.getMesh()->getPolygons();
    std::vector<scrPosition>* positions = o.getMesh()->positions;
    std::vector<int>* vaux;
    
    Polygon paux;
    int j;
    for(int i = 0; i < polygons->size(); ++i){
        for(j = 0; j < polygons->at(i)->vertexs->size()-1 ; ++j){
            vaux = polygons->at(i)->vertexs;
            rasterize(Vector(positions->at(vaux->at(j)).x, positions->at(vaux->at(j)).y), Vector(positions->at(vaux->at(j+1)).x, positions->at(vaux->at(j+1)).y));
            output->saveTGA("/Users/danibarca/Desktop/output.tga");

        }
        rasterize(Vector(positions->at(vaux->at(j)).x, positions->at(vaux->at(j)).y), Vector(positions->at(vaux->at(0)).x, positions->at(vaux->at(0)).y));
        output->saveTGA("/Users/danibarca/Desktop/output.tga");
    }
}

void Camera::rasterize(Vector start, Vector end){
    /*Explicación:
     *El método para rasterizar varía según el ángulo de la línea que tenemos que dibujar
     *1) Miramos si es horizontal o vertical para usar el algoritmo básico si es así
     *2) Nos aseguramos de que los algoritmos restantes recorran y de arriba a abajo cambiando start por end si hace falta (if(start.y > end.y)...)
     *3) Miramos si el ángulo de la línea es inferior a +-45º para usar el algoritmo middle point si es así
     *4) En el resto de casos, usamos el algoritmo de Swanson and Thayer del libro
     */
    
    //Si la línea es completamente horizontal
    if(start.x == end.x){
        int st = start.y, en = end.y;
        
        if(start.y > end.y){
            st = end.y;
            en = start.y;
        }
        
        for(;st < en; ++st){
            output->setPixel(Color(255,255,255), start.x, st);
            //output->saveTGA("Users/danibarca/output.tga");
        }
        return;
    }
    
    //Si la línea es completamente vertical
    if(start.y == end.y){
        int st = start.x, en = end.x;
        
        if(start.x > end.x){
            st = end.x;
            en = start.x;
        }
        
        for(;st < en; ++st){
            output->setPixel(Color(255,255,255), st, start.y);
        }
        return;
    }
    
    //Si start está por debajo de end, los intercambiamos
    if(start.y > end.y){
        Vector aux = end;
        end = start;
        start = aux;
    }
    
    
    //Calculamos el ángulo respecto a la línea horizontal
    float pendiente = (start.y - end.y)/(start.x-end.x);
    float angulo    = atan(pendiente);
    angulo = RADTODEG(angulo);
    
    if((angulo < 45 && angulo > 0)||(angulo > -45 && angulo < 0)){          //Si el ángulo es menor a 45º
        std::cout  << std::endl;
        //Algoritmo midpoint, sólo funciona cuando el ángulo es < 45º
        
        if(angulo < 0){
            start.x = (plane.half_width + (plane.half_width - start.x));
            end.x   = (plane.half_width + (plane.half_width - end.x));
        }
        
        int dx = end.x - start.x;
        int dy = end.y - start.y;
        int d  = 2*dy - dx;
        
        int incrE = 2*dy;
        int incrNE= 2*(dy-dx);
        
        int x = start.x;
        int y = start.y;
        
        while(x<end.x){
            if(d <= 0){
                d += incrE;
                x++;
            }
            else{
                d += incrNE;
                x++;
                y++;
            }
            
            if(angulo < 0)
                output->setPixel(Color(255,255,255), (plane.half_width - (x-plane.half_width)), y);
            else
                output->setPixel(Color(255,255,255), x, y);
        }
        return;
    }
    
    //Algoritmo 2
     
    float xi = start.x;
    float xf = -0.5;
    
    int   mi = floor((end.x- start.x) / (end.y - start.y));
    float mf = (end.x - start.x) / (end.y - start.y) - mi;
    
    for(int y = start.y; y < end.y; ++y){
        output->setPixel(Color(255,255,255), xi, y);
        
        xi += mi;
        xf += mf;
        
        if(xf > 0.0){
            xi += 1;
            xf -= 1;
        }
    }
}
