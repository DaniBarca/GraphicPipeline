//
//  Camera.h
//  GraphicPipeline
//
//  Created by Dani Barca - Álvaro Ibañez - Lucas Enric de Haan on 31/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#ifndef __GraphicPipeline__Camera__
#define __GraphicPipeline__Camera__

#include <iostream>
#include "framework.h"
#include "Object.h"
#include "Mesh.h"
#include "Polygon.hpp"
#include "image.hpp"

#define DISTPLANEC   300
#define DISTFARPLANE 1000


class Camera{
    struct plane{
        int width;
        int height;
        int half_width;
        int half_height;
    }plane;
    
    bool inverseN;                          //Boolean para invertir las normales si es necesario
    std::string outputdir;
    Image*      output;
    
    void  setCUVN();                        //Coloca los vectores u, v y n
    void  setPerspective();                 //Actualiza a matriz tpers * tview
    
    void  renderVertexs(Object o);          //Renderiza los vertices
    void  rasterize(Vector a, Vector b);    //Dibuja una línea entre a y b (son coordenadas 2D, aunque la clase Vector tenga una 3a componente, no la usaremos).
    void  rasterizePolygons(Object o);      //Rasterizamos las líneas entre los vértices
public:
    Matrix* model;
    Matrix* tPers;
    
    Vector N;
    Vector U;
    Vector V;
    Vector C;
    
    float FOV;
    float distPant;
    
    Camera(Vector position, Vector lookat, std::string outputdir, int width = 500, int height = 500, bool inverseN = false); //Constructor
    void setCamera(Vector start, Vector end);                                  //Coloca la cámara

    
    void render(Object o);
};

#endif /* defined(__GraphicPipeline__Camera__) */
