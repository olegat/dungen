//
//  WeighedRoomDigger.cpp
//  Dissert
//
//  Created by Olivier Legat on 16/06/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "WeighedRoomDigger.h"
#include <Generator/Maze/Maze.h>

WeighedRoomDigger::WeighedRoomDigger(
                Maze* maze,
                RoomDiggerWeights weight,
                RandomElementI roomSize,
                RandomElementI roomPosition,
                RandomElementI numberOfRooms)
: RoomDigger(maze, roomSize, roomPosition, numberOfRooms)
{
    this->weight = weight;
}

WeighedRoomDigger::~WeighedRoomDigger()
{
    
}

bool WeighedRoomDigger::Step()
{
    best = maze->GetCell(0, 0);
    bestWeight = 99999;
    
    // Get a random width and length:
    int w = roomSize.nextInt();
    int l = roomSize.nextInt();
    
    int x, z;
    int NX = maze->Width()  - w;
    int NZ = maze->Length() - l;
    
    // For each cell in the maze
    for ( x = 0; x < NX; x++ )
    for ( z = 0; z < NZ; z++ )
    {
        int thisWeight = 0;
        bool ok = false;
        
        // For each cell in the room:
        for (int cx = 0; cx < w; cx++)
        for (int cz = 0; cz < l; cz++)
        {
            MazeCell* cell = maze->GetCell(x + cx, z + cz);
            MazeCell* neighbours[4];
            int neighbourCount;
            
            // Apply weight for all rooms this cell is touching:
            thisWeight += touchesRoom(x + cx, z + cz) * weight.OnRoom;
            
            // Apply weight if the cell is on a corridor:
            if (maze->GetWallCount(cell) != 4) {
                thisWeight += weight.OnCorridor;
                ok = true;
            }
            
            // Apply weight for each corrider this cell is touching
            neighbourCount = maze->GetAdjacentCells(cell, neighbours);
            for (int i = 0; i < neighbourCount; i++)
                 if (maze->GetWallCount(neighbours[i]))
                     thisWeight += weight.TouchingCorridor;
        }
        
        // If this room is touching nothing then don't place it here.
        if (!ok) continue;
        
        // Overwrite:
        else if (thisWeight < bestWeight)
        {
            best = maze->GetCell(x, z);
            bestWeight = thisWeight;
        }
    }
    
    addedRooms.push_back(w);
    addedRooms.push_back(l);
    addedRooms.push_back(best->X());
    addedRooms.push_back(best->Z());
    
    return ++nRooms == nRoomsTotal;
}

void WeighedRoomDigger::End()
{
    for ( size_t i = 0; i < addedRooms.size(); i += 4 )
    {
        int w = addedRooms[i+0];
        int l = addedRooms[i+1];
        int rx= addedRooms[i+2];
        int rz= addedRooms[i+3];
        
        MazeCell* topLeft = maze->GetCell(rx, rz);
        MazeCell* bottomRight = maze->GetCell(rx+w, rz+l);
        
        maze->BreakWalls(topLeft, bottomRight);
    }
    
    addedRooms.clear();
}

int WeighedRoomDigger::touchesRoom(int x, int z)
{
    int touches = 0;
    
    for ( size_t i = 0; i < addedRooms.size(); i += 4 )
    {
        int w = addedRooms[i+0];
        int l = addedRooms[i+1];
        int rx= addedRooms[i+2];
        int rz= addedRooms[i+3];
        
        if (x >= rx && x < rx + w &&
            z >= rz && z < rz + l) 
        {
            touches++;
        }
    }
    return touches;
}
                 
