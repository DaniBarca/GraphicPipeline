//
//  image.cpp
//  GraphicPipeline
//
//  Created by Dani Barca - Álvaro Ibañez - Lucas Enric de Haan on 03/06/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#include "image.hpp"

float clamp(float x, float a, float b) { return x < a ? a : (x > b ? b : x); }

Color operator * (const Color& c,float v) { return Color(c.r*v, c.g*v, c.b*v); }
void operator *= (Color& c,float v) { c = c * v; }
Color operator / (const Color& c,float v) { return Color(c.r/v, c.g/v, c.b/v); }
void operator /= (Color& c,float v) { c = c / v; }
Color operator * (float v, const Color& c) { return Color(c.r*v, c.g*v, c.b*v); }
Color operator + (const Color& a, const Color& b) { return Color(a.r+b.r, a.g+b.g, a.b+b.b); }
void operator += (Color& a,const Color& b) { a = a + b; }
Color operator - (const Color& a, const Color& b) { return Color(a.r-b.r, a.g-b.g, a.b-b.b); }
void operator -= (Color& a,const Color& b) { a = a - b; }