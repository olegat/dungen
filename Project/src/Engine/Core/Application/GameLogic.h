//
//  GameLogic.h
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

#include <platform.h>

class EngineApplication;

class GameLogic
extends Object
{
    friend class EngineApplication;
    
public:
    virtual int Init() = 0;
    virtual bool Update() = 0;
    virtual int End() = 0;
    
    EngineApplication* GetEngine() { return engine; }
    
private:
    EngineApplication* engine;
};

#endif
