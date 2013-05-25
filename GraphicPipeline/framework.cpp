//
//  framework.cpp
//  GraphicPipeline
//
//  Created by Dani Barca on 21/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#include "framework.h"

Vector::Vector(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vector::mod(){ return sqrt(x*x + y*y + z*z); }

void Vector::norm(){
    Vector a;
    a = (*this)/mod();
    
    this->x = a.x;
    this->y = a.y;
    this->z = a.z;
}

static Vector operator +(const Vector& a, const Vector& b){ return Vector(a.x+b.x, a.y+b.y, a.z+b.z); }
static Vector operator -(const Vector& a, const Vector& b){ return Vector(a.x-b.x, a.y-b.y, a.z-b.z); }
static Vector operator /(const Vector& a, const float&  b){ return Vector(a.x/b,   a.y/b,   a.z/b);   }

void Matrix::setIdentity(){
    for(int i = 0; i < 16; ++i)
        m[i] = 0;
    
    m[0]  = 1;
    m[5]  = 1;
    m[10] = 1;
    m[14] = 1;
}