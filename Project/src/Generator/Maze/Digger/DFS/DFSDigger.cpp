//
//  DFSDigger.cpp
//  Dissert
//
//  Created by Olivier Legat on 12/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "DFSDigger.h"

#include <Generator/Random/Random.h>

DFSDigger::DFSDigger(Maze* maze, RandomI* feeder) : Digger(maze)
{
    assert ( feeder );
    
    this->picker = feeder;
    this->backtrackNodes = List<MazeCell*>();
}


DFSDigger::~DFSDigger() {}

bool DFSDigger::Step() 
{
    MazeCell* parent = getExpandingCell();
    if(parent == NULL) return true; // done
    else lastVisitedCell = parent;
    
    if (this->isLoggingPath())
        std::cout << parent->X() << "," << parent->Z() << std::endl;
    
    // not done... get the children:
    MazeCell* children[4];
    int count = maze->GetUnvisitedCells(parent, children);
    
    // pick one at random:
    int pick = picker->nextInt(0, count);
    MazeCell* child = children [ pick ];
    child->SetVisited(true);
    
    // break the wall:
    maze->BreakWalls(parent, child);
    
    // add this visited node to backtracking list (or not ...)
    if (count > 1) backtrackNodes.push_back(child);
    
    // update last visited:
    lastVisitedCell = child;
    
    return false;
}

MazeCell* DFSDigger::getExpandingCell()
{
    // is this current cell a leaf?
    if( maze->GetUnvisitedCells(lastVisitedCell, NULL) == 0 )
        return backtrack(); // yes.
    
    // no.. expand it.
    else return lastVisitedCell;
}

MazeCell* DFSDigger::backtrack()
{
    MazeCell* c = NULL;
    
    while ( ! backtrackNodes.empty() && c == NULL) 
    {
        c = backtrackNodes.back();
        int count = maze->GetUnvisitedCells(c, NULL);
        
        if (count <= 1) backtrackNodes.pop_back();
        if (count == 0) c = NULL;
    }
    
    return c;
}

// push the picker.
void DFSDigger::GetRandomsUsed(Array<RandomI*> &array) 
{
    array.push_back(picker);
    return;
}

// this digger doesn't use any random float generators
void DFSDigger::GetRandomsUsed(Array<RandomF*> &array) { return; }
