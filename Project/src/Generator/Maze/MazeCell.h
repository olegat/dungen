//
//  Cell.h
//  Dissert
//
//  Created by Olivier Legat on 07/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef MAZE_CELL_H_
#define MAZE_CELL_H_

#include <platform.h>

enum MazeCellType
{
    MAZE_CELL_WALL,
    MAZE_CELL_FLOOR
};

class MazeCell
extends Object
{
public:
    MazeCell(int x, int z, MazeCellType type);
    ~MazeCell();
    
    bool IsVisited() const {return visited;}
    void SetVisited(const bool b) {visited = b;}
    
    MazeCellType GetCellType() const {return type;}
    void SetCellType(MazeCellType celltype) {type = celltype;}
    
    int X() const {return x;}
    int Z() const {return z;}
    
    Object* GetObject() const {return obj;}
    void SetObject(Object* o) {this->obj = o;}
    
private:
    int x, z;
    MazeCellType type;
    bool visited;
    Object* obj;
};

#endif
