//
//  framework.h
//  GraphicPipeline
//
//  Created by Dani Barca - Álvaro Ibañez - Lucas Enric de Haan on 21/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#ifndef __GraphicPipeline__framework__
#define __GraphicPipeline__framework__

#include <iostream>
#include <math.h>

#define PI      3.1415926536
#define DEG2RAD 0.01745329252
#define RAD2DEG 57.295779513
#define DEGTORAD(d) d*DEG2RAD
#define RADTODEG(r) r*RAD2DEG

int round(float x);

typedef struct{
    int x;
    int y;
}scrPosition;

class Vector{
public:
    struct{
        float x;
        float y;
        float z;
    };
    
    Vector(float x = 0, float y = 0, float z = 0);
    
    float mod();
    void norm();
    float dot(Vector);
    
    void printVector(){
        std::cout << x << " " << y << " " << z << std::endl;
    }
    
    float dist(Vector);
};

Vector operator *(const Vector& a, const Vector& b);
Vector operator +(const Vector& a, const Vector& b);
Vector operator -(const Vector& a, const Vector& b);
Vector operator /(const Vector& a, const float&  b);
Vector operator *(const Vector& a, const float&  b);

/*  0  1  2  3
 *  4  5  6  7
 *  8  9  10 11
 *  12 13 14 15
 */

class Matrix{
public:
    float m[16];
    
    Matrix();
    void setIdentity();
    void clean();
    void printMatrix(){
        for(int i = 0; i < 4; ++i){
            for(int j = 0; j < 4; ++j){
                std::cout << get(i,j) << " ";
            }
            std::cout << std::endl;
        }
    }
    
    void  set(int i, int j, float stuff);
    float get(int i, int j) const;
    
    void copy(Matrix mx){
        for(int i = 0; i < 16; ++i)
            m[i] = mx.m[i];
    }
    
    void setPosition(float x, float y, float z);
    void setPosition(Vector position);
    void setRotation(float angle, Vector axis);
    
    Vector traslateVector(Vector v);
    
    //Adapted from Javier Agenjo's code:
    Vector rotateVector(Vector v);
    void setRotationMatrix(float angle, Vector axis);
    void setTraslationMatrix(float x, float y, float z);
    bool inverse();
};

Matrix operator *(const Matrix& a, const Matrix& b);
Vector operator *(const Matrix& a, const Vector& b);

//Devuelve la posición t de la ecuación de la recta
Vector line(Vector a, Vector b, float t);

//Devuelve el punto de intersección entre una recta y un plano
Vector linePlaneIntersection(Vector linePoint, Vector lineDir, Vector planePoint, Vector planeNormal);

#endif /* defined(__GraphicPipeline__framework__) */
