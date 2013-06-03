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

float Vector::dist(Vector b){
    return Vector(b.x - this->x, b.y - this->y, b.z - this->z).mod();
}

//-----------Operators

Vector operator +(const Vector& a, const Vector& b){ return Vector(a.x+b.x, a.y+b.y, a.z+b.z); }
Vector operator -(const Vector& a, const Vector& b){ return Vector(a.x-b.x, a.y-b.y, a.z-b.z); }
Vector operator /(const Vector& a, const float&  b){ return Vector(a.x/b,   a.y/b,   a.z/b);   }
Vector operator *(const Vector& a, const float&  b){ return Vector(a.x*b,   a.y*b,   a.z*b);   }

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
    m[3] = x;
    m[7] = y;
    m[11]= z;
}

void Matrix::setPosition(Vector position){
    setPosition(position.x,position.y,position.z);
}

Vector Matrix::rotateVector(Vector v){
    Matrix temp = *this;
	temp.m[3] = 0.0;
	temp.m[7] = 0.0;
	temp.m[11] = 0.0;
	return temp * v;
}

void Matrix::setTraslationMatrix(float x, float y, float z){
    setIdentity();
    m[3] = x;
    m[7] = y;
    m[11] = z;
}

void Matrix::setRotationMatrix( float angle_in_rad, const Vector axis  )
{
	clean();
	Vector axis_n = axis;
	axis_n.norm();
    
	float c = cos( angle_in_rad );
	float s = sin( angle_in_rad );
	float t = 1 - c;
    
	m[0] = t * axis.x * axis.x + c;
	m[4] = t * axis.x * axis.y - s * axis.z;
	m[8] = t * axis.x * axis.z + s * axis.y;
    
	m[1] = t * axis.x * axis.y + s * axis.z;
	m[5] = t * axis.y * axis.y + c;
	m[9] = t * axis.y * axis.z - s * axis.x;
    
	m[2] = t * axis.x * axis.z - s * axis.y;
	m[6] = t * axis.y * axis.z + s * axis.x;
	m[10]= t * axis.z * axis.z + c;
    
	m[15]= 1.0f;
}

//------------Operators

Matrix operator *(const Matrix& a, const Matrix& b){
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

Vector operator *(const Matrix& a, const Vector& b){
    float x = a.m[0] * b.x + a.m[1] * b.y + a.m[2]  * b.z + a.m[3];
    float y = a.m[4] * b.x + a.m[5] * b.y + a.m[6]  * b.z + a.m[7];
    float z = a.m[8] * b.x + a.m[9] * b.y + a.m[10] * b.z + a.m[11];
    
    return Vector(x,y,z);
}

//-------------------------