//
//  Digger.h
//  Dissert
//
//  Created by Olivier Legat on 12/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef ROOM_DIGGER_H_
#define ROOM_DIGGER_H_

#include <platform.h>
#include <Generator/Maze/Digger/Digger.h>

#include <Generator/Random/RandomElement.h>

class RandomI;

class RoomDigger
extends Digger
{
public:
    
    /**
     * Create a room digger.
     * @param maze A Maze to dig through.
     * @param roomSize Number generator used to randomize room sizes
     * @param roomPosition Number generator used to randomize room positions.
     * @param numberOfRooms Number generator used to randomize the number of rooms.
     */
    RoomDigger(Maze* maze,
               RandomElementI roomSize,
               RandomElementI roomPosition,
               RandomElementI numberOfRooms);
    
    /**
     * Destroy this digger.
     */
    ~RoomDigger();
    
    virtual void Init();
    
    /**
     * Do a single iteration. 
     * @return true when done.
     */
    virtual bool Step();
    
    virtual void GetRandomsUsed(Array<RandomI*> &array);
    virtual void GetRandomsUsed(Array<RandomF*> &array);
    
protected:
    int nRooms;      // number of rooms added.
    int nRoomsTotal; // number of rooms in total (goal).
    RandomElementI roomSize;
    RandomElementI roomPosition;
    RandomElementI roomNumberGenerator;
};

#endif
