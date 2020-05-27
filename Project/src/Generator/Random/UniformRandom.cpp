//
//  Uniform.cpp
//  Dissert
//
//  Created by Olivier Legat on 12/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//
//  Implementation reference:
//     http://en.wikipedia.org/wiki/Linear_congruential_generator
//     http://stackoverflow.com/questions/4768180/rand-implementation

#include "UniformRandom.h"

UniformRandom::UniformRandom()
{
    x = (unsigned long) time(NULL);
}

UniformRandom::UniformRandom(unsigned long seed)
{
    x = seed;
}

UniformRandom::~UniformRandom()
{
    
}

int UniformRandom::nextInt()
{
    x = (x * MAZE_LCG_A + MAZE_LCG_C) % MAZE_LCG_M;
    return (int) ( x & 0x00FF );
}

int UniformRandom::nextInt(int max)
{
    return nextInt(0, max);
}

int UniformRandom::nextInt(int min, int max)
{
    assert(max > 0);
    assert(min >= 0);
    int l = max - min; if(l < 0) l *= -1;
    return ((int) nextInt() % l) + min;
}

float UniformRandom::nextFloat()
{
    return nextFloat(0.0f, 1.0f);
}

float UniformRandom::nextFloat(float max)
{
    assert(max >= 0.0f);
    return nextFloat(0.0f, max);
}

float UniformRandom::nextFloat(float min, float max)
{
    assert(min <= max);
    /* calculate the random number & return it */
	return ((float)rand() / (static_cast<float>(RAND_MAX) + 1.0f))
	* (max - min) + min;
}
