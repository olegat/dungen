//
//  Timing.h
//  Dissert
//
//  Created by Olivier Legat on 08/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef TIMING_H_
#define TIMING_H_

#include <Object.h>

class Timing
extends Object 
{
public:
    // Total time elapsed since the start of the application:
    static float GameCurrentTime;
    
    // Time elapse since the last frame:
    static float GameTimeElapsed;
    
    static void Init();
    static void Update();
};

#endif
