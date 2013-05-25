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
};

static Vector operator +(const Vector& a, const Vector& b);
static Vector operator -(const Vector& a, const Vector& b);
static Vector operator /(const Vector& a, const float&  b);

class Matrix{
public:
    float m[16];
    
    Matrix();
    void setIdentity();
};


#endif /* defined(__GraphicPipeline__framework__) */
