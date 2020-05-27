//
//  RandomElement.h
//  Dissert
//
//  Created by Olivier Legat on 25/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef RANDOM_ELEMENT_H_
#define RANDOM_ELEMENT_H_

class RandomI;
class RandomF;

struct RandomElementI
{
public:
    RandomElementI();
    RandomElementI(int min, int max);
    RandomElementI(int min, int max, RandomI* generator);
    
    int min;
    int max;
    RandomI* generator;
    
    int nextInt();
};

struct RandomElementF
{
public:
    RandomElementF();
    RandomElementF(float min, float max);
    RandomElementF(float min, float max, RandomF* generator);
    
    float min;
    float max;
    RandomF* generator;
    
    float nextFloat();
};

#endif
