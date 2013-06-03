//
//  framework.h
//  GraphicPipeline
//
//  Created by Dani Barca on 21/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#ifndef __GraphicPipeline__framework__
#define __GraphicPipeline__framework__

#include <iostream>
#include <math.h>

#define DEG2RAD 0.01745329252
#define RAD2DEG 57.295779513
#define DEGTORAD(d) d*DEG2RAD
#define RADTODEG(r) r*RAD2DEG

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
    
    float dist(Vector);
};

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
    
    void  set(int i, int j, float stuff);
    float get(int i, int j) const;
    
    void setPosition(float x, float y, float z);
    void setPosition(Vector position);
    
    //Adapted from Javier Agenjo's code:
    Vector rotateVector(Vector v);
    void setRotationMatrix(float angle, Vector axis);
    void setTraslationMatrix(float x, float y, float z);
    bool inverse();
};

Matrix operator *(const Matrix& a, const Matrix& b);
Vector operator *(const Matrix& a, const Vector& b);

Vector line(Vector, Vector, float);

#endif /* defined(__GraphicPipeline__framework__) */
