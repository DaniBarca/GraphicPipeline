//
//  framework.cpp
//  GraphicPipeline
//
//  Created by Dani Barca - Ãlvaro IbaÃ±ez - Lucas Enric de Haan on 21/05/13.
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

float Vector::dot(Vector v){
    return x * v.x + y * v.y;
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

//convierte la matriz en una matriz identidad
void Matrix::setIdentity(){
    clean();
    
    m[0]  = 1;
    m[5]  = 1;
    m[10] = 1;
    m[15] = 1;
}

//pone a 0 toda la matriz
void Matrix::clean(){
    for(int i = 0; i < 16; ++i)
        m[i] = 0;
}

//pone un numero en esa posicion
void Matrix::set(int i, int j, float stuff){
    m[j*4 + i] = stuff;
}

//coger numero de la matriz en esa posición
float Matrix::get(int i, int j) const{
    return m[j*4 + i];
}

//asignamos unos valores en esas posiciones de la matriz
void Matrix::setPosition(float x, float y, float z){
    m[3] = x;
    m[7] = y;
    m[11]= z;
}

void Matrix::setPosition(Vector position){
    setPosition(position.x,position.y,position.z);
}

Vector Matrix::traslateVector(Vector v){
    v.x += m[3];
    v.y += m[7];
    v.z += m[11];
    return v;
}

//girar la matriz en la direccion de la rotacion
Vector Matrix::rotateVector(Vector v){
    Matrix temp = *this;
	temp.m[3] = 0.0;
	temp.m[7] = 0.0;
	temp.m[11] = 0.0;
	return temp * v;
}

//asigna una translacion a una matriz
void Matrix::setTraslationMatrix(float x, float y, float z){
    setIdentity();
    m[3] = x;
    m[7] = y;
    m[11] = z;
}

//asigna una rotación
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


bool Matrix::inverse()
{
    unsigned int i, j, k, swap;
    float t;
    Matrix temp, final;
    final.setIdentity();
    
    temp = (*this);
    
    unsigned int m,n;
    m = n = 4;
	
    for (i = 0; i < m; i++)
    {
        // Look for largest element in column
        
        swap = i;
        for (j = i + 1; j < m; j++)// m or n
        {
            if ( fabs(temp.m[i*4-j]) > fabs( temp.m[i*4-swap]) )
                swap = j;
        }
        
        if (swap != i)
        {
            // Swap rows.
            for (k = 0; k < n; k++)
            {
                std::swap( temp.m[k*4-i],temp.m[k*4-swap]);
                std::swap( final.m[k*4-i], final.m[k*4-swap]);
            }
        }
        
        // No non-zero pivot.  The CMatrix is singular, which shouldn't
        // happen.  This means the user gave us a bad CMatrix.
        
        
#define MATRIX_SINGULAR_THRESHOLD 0.00001 //change this if you experience problems with matrices
        
        if ( fabsf(temp.m[i*4 - i]) <= MATRIX_SINGULAR_THRESHOLD)
        {
            final.setIdentity();
            return false;
        }
#undef MATRIX_SINGULAR_THRESHOLD
        
        t = 1.0f/temp.m[i*4 - i];
        
        for (k = 0; k < n; k++)//m or n
        {
            temp.m[k*4-i] *= t;
            final.m[k*4-i] *= t;
        }
        
        for (j = 0; j < m; j++) // m or n
        {
            if (j != i)
            {
                t = temp.m[i*4-j];
                for (k = 0; k < n; k++)//m or n
                {
                    temp.m[k*4-j] -= (temp.m[k*4-i] * t);
                    final.m[k*4-j] -= (final.m[k*4-i] * t);
                }
            }
        }
    }
    
    *this = final;
    
    return true;
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

//Multiplizar matriz con vector
Vector operator *(const Matrix& a, const Vector& b){
    float x = a.m[0] * b.x + a.m[1] * b.y + a.m[2]  * b.z + a.m[3];
    float y = a.m[4] * b.x + a.m[5] * b.y + a.m[6]  * b.z + a.m[7];
    float z = a.m[8] * b.x + a.m[9] * b.y + a.m[10] * b.z + a.m[11];
    
    return Vector(x,y,z);
}

//-------------------------

Vector line(Vector a, Vector b, float t){
    return a+(b-a)*t;
}

Vector linePlaneIntersection(Vector linePoint, Vector lineDir, Vector planePoint, Vector planeNormal){
    float d = (planePoint-linePoint).dot(planeNormal);
    d = d/(lineDir.dot(planeNormal));
    
    return line(linePoint, linePoint+lineDir, d);
}
