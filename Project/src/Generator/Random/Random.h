//
//  Seeder.h
//  Dissert
//
//  Created by Olivier Legat on 12/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef FEEDER_H_
#define FEEDER_H_

#include <platform.h>

/**
 * An abstract class for generating ints
 */
interface RandomI
{
protected:
    RandomI();
    
public:
    ~RandomI();
    
    virtual int nextInt()=0;
    virtual int nextInt(int max)=0;
    virtual int nextInt(int min, int max)=0;
};

/**
 * An abstract class for generating floats
 */
interface RandomF
{
protected:
    RandomF();
    
public:
    ~RandomF();
    
    virtual float nextFloat()=0;
    virtual float nextFloat(float max)=0;
    virtual float nextFloat(float min, float max)=0;
};

#endif
