//
//  Wall.h
//  Dissert
//
//  Created by Olivier Legat on 07/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef MAZE_WALL_H_
#define MAZE_WALL_H_

#include <platform.h>

enum MazeWallType
{
    MAZE_WALLTYPE_NONE,
    MAZE_WALLTYPE_DEFAULT
};

enum MazeWallPosition
{
    MAZE_WALLPOS_UP,
    MAZE_WALLPOS_DOWN,
    MAZE_WALLPOS_LEFT,
    MAZE_WALLPOS_RIGHT
};

class MazeWall
extends Object
{
public:
    MazeWall();
    ~MazeWall();
    
    MazeWallType GetType() const { return type; }
    void SetType(MazeWallType t) {type = t;}
    
private:
    MazeWallType type;
};

#endif
