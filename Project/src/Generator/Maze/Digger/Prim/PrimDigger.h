//
//  Prim.h
//  Dissert
//
//  Created by Olivier Legat on 18/06/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef PRIM_DIGGER_H_
#define PRIM_DIGGER_H_

#include <platform.h>
#include <Generator/Maze/Digger/Digger.h>
#include <Generator/Maze/Digger/PathLogger.h>

class PrimDigger
extends Digger
implements PathLogger
{
public:
    /**
     * Create a new digger.
     */
    PrimDigger(Maze* maze, RandomI* picker);
    /**
     * Destroy this digger.
     */
    ~PrimDigger();
    
    virtual void Init();
    virtual bool Step();
    virtual void End();
    
    virtual void GetRandomsUsed(Array<RandomI*> &array);
    virtual void GetRandomsUsed(Array<RandomF*> &array);
    
private:
    List<MazeCell*> parentNodes;
    RandomI* picker;
    
    MazeCell* GetRandomParent();
    MazeCell* PickAParentInTheList();
};

#endif
