//
//  DFSDigger.cpp
//  Dissert
//
//  Created by Olivier Legat on 12/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "DeadEndDigger.h"

DeadEndDigger::DeadEndDigger(Maze* maze, int sparseness) : Digger(maze)
{
    assert(sparseness > 0);
    
    this->sparseness = sparseness;
    this->i = 0;
}
DeadEndDigger::~DeadEndDigger() {}

bool DeadEndDigger::Step() 
{
    List<MazeCell*> deadEnds = List<MazeCell*>();
    
    GetDeadEnds(deadEnds);
    BlockDeadEnds(deadEnds);
    
    deadEnds.clear();
    
    return ++i == sparseness;
}

void DeadEndDigger::GetDeadEnds(List<MazeCell*> &deadEnds)
{
    int x, z, w = maze->Width(), l = maze->Length();
    
    for (x = 0; x < w; x++)
        for (z = 0; z < l; z++)
        {
            MazeCell* cell = maze->GetCell(x, z);
            if ( maze->IsDeadEnd( cell ) )
                deadEnds.push_back( cell );
        }
}

void DeadEndDigger::BlockDeadEnds(List<MazeCell*> &deadEnds)
{
    List<MazeCell*>::iterator it;
    for (it = deadEnds.begin(); it != deadEnds.end(); it++)
        maze->WallOff( *it );
}

// This digger doesn't use any random elements
void DeadEndDigger::GetRandomsUsed(Array<RandomI*> &array) { return; }
void DeadEndDigger::GetRandomsUsed(Array<RandomF*> &array) { return; }

