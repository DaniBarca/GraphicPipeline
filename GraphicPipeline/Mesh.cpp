//
//  Mesh.cpp
//  GraphicPipeline
//
//  Created by Dani Barca on 30/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#include "Mesh.h"

Mesh::Mesh(std::string dir){
    vertexs = new std::vector<Vector*>();
    polygons= new std::vector<Polygon*>();
    
    if(!parseFile(dir))
        std::cout << "No se ha podido leer el fichero" << std::endl;
}

bool Mesh::parseFile(std::string dir){
    text parser;
    
    if(!parser.create(dir.c_str()))
        return false;
    
    //Miramos cuántos vértices y polígonos hay
    nVertexs = parser.getint();
    nPolygons= parser.getint();
    
    std::cout << "------------------------"   << std::endl;
    std::cout << nVertexs << " " << nPolygons << std::endl;
    
    //Leemos los vértices
    Vector* aux;
    for(int i = 0; i < nVertexs; ++i){
        aux = new Vector(parser.getfloat(), parser.getfloat(), parser.getfloat());
        vertexs->push_back(aux);
        
        std::cout << aux->x << " " << aux->y << " " << aux->z << std::endl;
    }
    
    //Leemos los polígonos
    Polygon* auxb;
    int num;
    for(int i = 0; i < nPolygons; ++i){
        auxb = new Polygon();
        auxb->nSides = parser.getint();
        
        std::cout << auxb->nSides << " ";
        
        for (int j = 0; j < auxb->nSides; ++j){
            //En el archivo los vertices estan numerados a partir de 1
            //pero en el vector son a partir de 0, así que restamos 1
            num = parser.getint() - 1;
            
            auxb->vertexs->push_back(vertexs->at(num));
            
            std::cout << num << " ";
        }
        std::cout << std::endl;
        
        polygons->push_back(auxb);
    }
    

    
    return true;
}