//
//  Digger.h
//  Dissert
//
//  Created by Olivier Legat on 12/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef DIGGER_H_
#define DIGGER_H_

#include <platform.h>
#include <Generator/Maze/Maze.h>

class RandomI;
class RandomF;

class Digger
extends Object
{
protected:
    /**
     * Create a new digger.
     */
    Digger(Maze* maze);
    
    /**
     * Last visited maze cell.
     */
    MazeCell* lastVisitedCell;
    
    /**
     * The maze we are digging through.
     */
    Maze* maze;
    
public:
    /**
     * Destroy this digger.
     */
    ~Digger();
    
    /**
     * Get the last visitied cell.
     */
    MazeCell* GetLastVisited() {return lastVisitedCell;}
    
    /**
     * Get the maze.
     */
    Maze* GetMaze() {return maze;}
    
    /**
     * Initialize the algorithm.
     */
    virtual void Init();
    
    /**
     * Do a single iteration. 
     * @return true when done.
     */
    virtual bool Step()=0;
    
    /**
     * End the algorithm.
     */
    virtual void End();
    
    /**
     * Get all the random int generators used.
     * @param array [output] initialised array initially of size 0. 
     *              Outputs all RandomI instances references by this class.
     */
    virtual void GetRandomsUsed(Array<RandomI*> &array)=0;
    
    /**
     * Get all the random float generators used.
     * @param array [output] initialised array initially of size 0. 
     *              Outputs all RandomF instances references by this class.
     */
    virtual void GetRandomsUsed(Array<RandomF*> &array)=0;
    
    /**
     * Run all steps immediately (including Init and End).
     */
    void DigFully();
};

#endif
