//
//  Digger.h
//  Dissert
//
//  Created by Olivier Legat on 12/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef DFS_DIGGER_H_
#define DFS_DIGGER_H_

#include <platform.h>
#include <Generator/Maze/Digger/Digger.h>
#include <Generator/Maze/Digger/PathLogger.h>

class RandomI;

class DFSDigger
extends Digger
implements PathLogger
{
public:
    /**
     * Create a new depth-first search digger.
     */
    DFSDigger(Maze* maze, RandomI* feeder);
    
    /**
     * Destroy this digger.
     */
    ~DFSDigger();
    
    /**
     * Do a single iteration. 
     * @return true when done.
     */
    virtual bool Step();
    
    virtual void GetRandomsUsed(Array<RandomI*> &array);
    virtual void GetRandomsUsed(Array<RandomF*> &array);
    
private:
    List<MazeCell*> backtrackNodes;
    RandomI* picker;
    
    /**
     * Backtracks. Automatically removes nodes that have no more unvisited cells.
     *
     * @return The node where backtracking first stopped. NULL if no such node exists.
     */
    MazeCell* backtrack();
    
    /**
     * @return The maze cell which we are expanding.
     */
    MazeCell* getExpandingCell();
};

#endif
