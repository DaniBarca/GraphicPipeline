//
//  Object.h
//  GraphicPipeline
//
//  Created by Dani Barca on 21/05/13.
//  Copyright (c) 2013 Dani Barca. All rights reserved.
//

#ifndef __GraphicPipeline__Object__
#define __GraphicPipeline__Object__

#include <iostream>
#include <vector>
#include "framework.h"

class Object{
private:
    std::vector<Vector*> vertices;
public:
    Object();
};

#endif /* defined(__GraphicPipeline__Object__) */
