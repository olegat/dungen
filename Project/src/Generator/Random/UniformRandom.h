//
//  UniformSeeder.h
//  Dissert
//
//  Created by Olivier Legat on 12/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef UNIFORM_SEEDER_H_
#define UNIFORM_SEEDER_H_

#include "Random.h"

#define MAZE_LCG_A 16807      // 7^5
#define MAZE_LCG_M 2147483647 // 2^31 − 1
#define MAZE_LCG_C 0          // 0

class UniformRandom
extends Object
implements RandomI
implements RandomF
{
public:
    UniformRandom();
    UniformRandom(unsigned long seed);
    ~UniformRandom();
    
    virtual int nextInt();
    virtual int nextInt(int max);
    virtual int nextInt(int min, int max);
    
    virtual float nextFloat();
    virtual float nextFloat(float max);
    virtual float nextFloat(float min, float max);
    
private:
    unsigned long x;
};

#endif
