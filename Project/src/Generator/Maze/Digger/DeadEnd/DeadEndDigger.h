//
//  Digger.h
//  Dissert
//
//  Created by Olivier Legat on 12/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef DEAD_END_DIGGER_H_
#define DEAD_END_DIGGER_H_

#include <platform.h>
#include <Generator/Maze/Digger/Digger.h>

class RandomI;
class DeadEndDigger
extends Digger
{
public:
    /**
     * Create a new depth-first search digger.
     */
    DeadEndDigger(Maze* maze, int sparseness);
    
    /**
     * Destroy this digger.
     */
    ~DeadEndDigger();
    
    /**
     * Do a single iteration. 
     * @return true when done.
     */
    virtual bool Step();
    
    virtual void GetRandomsUsed(Array<RandomI*> &array);
    virtual void GetRandomsUsed(Array<RandomF*> &array);
    
private:
    void GetDeadEnds(List<MazeCell*> &deadEnds);
    void BlockDeadEnds(List<MazeCell*> &deadEnds);
    
    int i, sparseness;
};

#endif
