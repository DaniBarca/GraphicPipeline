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

//-----------Operators

static Vector operator +(const Vector& a, const Vector& b){ return Vector(a.x+b.x, a.y+b.y, a.z+b.z); }
static Vector operator -(const Vector& a, const Vector& b){ return Vector(a.x-b.x, a.y-b.y, a.z-b.z); }
static Vector operator /(const Vector& a, const float&  b){ return Vector(a.x/b,   a.y/b,   a.z/b);   }

//---------------------------------------------

Matrix::Matrix(){
    clean();
}

void Matrix::setIdentity(){
    clean();
    
    m[0]  = 1;
    m[5]  = 1;
    m[10] = 1;
    m[15] = 1;
}

void Matrix::clean(){
    for(int i = 0; i < 16; ++i)
        m[i] = 0;
}

void Matrix::set(int i, int j, float stuff){
    m[j*4 + i] = stuff;
}

float Matrix::get(int i, int j) const{
    return m[j*4 + i];
}

void Matrix::setPosition(float x, float y, float z){
    m[3] = -x;
    m[7] = -y;
    m[11]= -z;
}

void Matrix::setPosition(Vector position){
    setPosition(position.x,position.y,position.z);
}

//------------Operators

static Matrix operator *(const Matrix& a, const Matrix& b){
    Matrix c; c.clean();
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            for(int t = 0; t < 4; ++t){
                c.set(i,j, c.get(i,j) + a.get(i,t) * b.get(t,i));
            }
        }
    }
    return c;
}

static Vector operator *(const Matrix& a, const Vector& b){
    float x = a.m[0] * b.x + a.m[4] * b.y + a.m[8]  * b.z + a.m[12];
    float y = a.m[1] * b.x + a.m[5] * b.y + a.m[9]  * b.z + a.m[13];
    float z = a.m[2] * b.x + a.m[6] * b.y + a.m[10] * b.z + a.m[14];
    
    return Vector(x,y,z);
}

//-------------------------