//
//  WeighedRoomDigger.h
//  Dissert
//
//  Created by Olivier Legat on 16/06/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef WEIGHED_ROOM_DIGGER_H_
#define WEIGHED_ROOM_DIGGER_H_

#include "RoomDigger.h"

typedef struct RoomDiggerWeights
{
    int OnCorridor;
    int TouchingCorridor;
    int OnRoom;
}
RoomDiggerWeights;

class WeighedRoomDigger
extends RoomDigger
{
public:
    WeighedRoomDigger(Maze* maze,
                      RoomDiggerWeights weight,
                      RandomElementI roomSize,
                      RandomElementI roomPosition,
                      RandomElementI numberOfRooms);
    ~WeighedRoomDigger();
    
    virtual bool Step();
    virtual void End();
    
private:
    RoomDiggerWeights weight;
    MazeCell* best;
    int bestWeight;
    
    // Rooms added. every room get 4 ints:
    // (Width, Length, topLeftX, topLeftZ)
    //
    // addedRooms = {w0, l0, x0, z0, w1, l1, x1, z1,...} where
    // {w0, l0, x0, z0} is room 0
    // {w1, l1, x1, z1} is room 1
    Array<int> addedRooms;
    
    int touchesRoom(int x, int z);
};

#endif
