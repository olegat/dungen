//
//  Cell.cpp
//  Dissert
//
//  Created by Olivier Legat on 07/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "MazeCell.h"

MazeCell::MazeCell(int x, int z, MazeCellType type) {
    this->type = type;
    this->visited = false;
    this->x = x;
    this->z = z;
    this->obj = NULL;
}

MazeCell::~MazeCell() {
    
}
