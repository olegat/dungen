//
//  DFSDigger.cpp
//  Dissert
//
//  Created by Olivier Legat on 12/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "RoomDigger.h"

RoomDigger::RoomDigger(Maze* maze,
                       RandomElementI roomSize,
                       RandomElementI roomPosition,
                       RandomElementI numberOfRooms) 
: Digger(maze)
{
    this->nRooms = 0;
    this->nRoomsTotal = 0; // don't call nextInt() yet! That will screw the LCG's random sequence.
    this->maze = maze;
    this->roomSize = roomSize;
    this->roomPosition = roomPosition;
    this->roomNumberGenerator = numberOfRooms;
}

RoomDigger::~RoomDigger() { }

void RoomDigger::Init()
{
    this->nRoomsTotal = roomNumberGenerator.nextInt();
}

bool RoomDigger::Step() 
{
    // Get a random width and length:
    int w = roomSize.nextInt();
    int l = roomSize.nextInt();
    
    // Calculate number of cells on the left,right,.. relative to a random position
    int left  = (w / 2);
    int right = (w / 2) + (w % 2);
    int down  = (l / 2);
    int up    = (l / 2) + (l % 2);
    
    // Get a random x-coordinate:
    int x = -1;
    while ( x - left < 0 || x + right > maze->Width() -1 )
        x = roomPosition.nextInt();
    
    // Get a random z-coordinate:
    int z = -1;
    while ( z - down < 0 || z + up > maze->Length() -1 )
        z = roomPosition.nextInt();
    
    // Break the walls:
    const MazeCell* cell1 = maze->GetCell(x - left,  z - down);
    const MazeCell* cell2 = maze->GetCell(x + right, z + up);
    maze->BreakWalls(cell1, cell2);
    
    return ++nRooms == nRoomsTotal;
}

// Push all 3 RandomI generators:
void RoomDigger::GetRandomsUsed(Array<RandomI*> &array)
{
    array.push_back(this->roomSize.generator);
    array.push_back(this->roomPosition.generator);
    array.push_back(this->roomNumberGenerator.generator);
    return;
}

// This digger doesn't use any float generators
void RoomDigger::GetRandomsUsed(Array<RandomF*> &array) { return; }
