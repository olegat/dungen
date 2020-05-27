//
//  BinaryTreeDigger.cpp
//  Dissert
//
//  Created by Olivier Legat on 16/06/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "BinaryTreeDigger.h"
#include <Generator/Random/UniformRandom.h>

BinaryTreeDigger::BinaryTreeDigger(Maze* maze, RandomI* coin) : Digger(maze)
{
    this->coin = coin;
}

BinaryTreeDigger::~BinaryTreeDigger()
{
    
}

void BinaryTreeDigger::Init()
{
    x = 0;
    z = 1;
    lastVisitedCell = maze->GetCell(0, 0);
}
bool BinaryTreeDigger::Step()
{    
    MazeCell* cell = this->maze->GetCell(x, z);
            
    if ( z == 0 ) {
        // Break left wall:
        this->maze->GetWall(cell, MAZE_WALLPOS_LEFT)->SetType(MAZE_WALLTYPE_NONE);
    }
    else if ( x == 0 ) {
        // Break top wall:
        this->maze->GetWall(cell, MAZE_WALLPOS_UP)->SetType(MAZE_WALLTYPE_NONE);
    }
    else
    {
        // Break left OR top wall:
        int which = coin->nextInt(0, 2);
        
        if ( which == 0 ) {
            // Break left wall:
            this->maze->GetWall(cell, MAZE_WALLPOS_LEFT)->SetType(MAZE_WALLTYPE_NONE);
            
        }
        else {
            // Break top wall:
            this->maze->GetWall(cell, MAZE_WALLPOS_UP)->SetType(MAZE_WALLTYPE_NONE);
        }
    }

	// Increase iterators:
    int NX = this->maze->Width();
    int NZ = this->maze->Length();
    z++;
    if (z == NZ)
    {
        z = 0;
        x++;
    }

    return x == NX;
}
void BinaryTreeDigger::End()  {}

void BinaryTreeDigger::GetRandomsUsed(Array<RandomI*> &array)
{
    array.push_back(coin);
}
void BinaryTreeDigger::GetRandomsUsed(Array<RandomF*> &array) {}
