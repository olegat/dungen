//
//  DoorDecoDigger.h
//  Dissert
//
//  Created by Olivier Legat on 03/08/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef DOOR_DECO_DIGGER_H_
#define DOOR_DECO_DIGGER_H_

#include <platform.h>
#include <Generator/Maze/Digger/Digger.h>
#include <Generator/Maze/Digger/ExternalMeshDigger.h>
#include <Generator/Maze/Digger/WeightFile.h>

class DoorDecoDigger
extends Digger
implements ExternalMeshDigger
{
public:
    DoorDecoDigger(Maze* maze, RandomI* randomI, RandomF* randomF, float density, String filename);
    ~DoorDecoDigger();
    
    virtual void Init();
    virtual bool Step();
    virtual void End();
    
    virtual void GetRandomsUsed(Array<RandomI*> &array);
    virtual void GetRandomsUsed(Array<RandomF*> &array);
    
private:
	RandomI* randomI;
	RandomF* randomF;
	float density;
	WeightFile* weightFile;
    
    bool canBeHDoor(int x, int z);
    bool canBeVDoor(int x, int z);
    void MakeRandomDoor(Quaternion rot, Vector3 translation);
};

#endif
