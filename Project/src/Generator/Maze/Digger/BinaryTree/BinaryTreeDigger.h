//
//  BinaryTreeDigger.h
//  Dissert
//
//  Created by Olivier Legat on 16/06/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <Generator/Maze/Digger/Digger.h>

class BinaryTreeDigger
extends Digger
{
public:
    /**
     * Create a new digger.
     */
    BinaryTreeDigger(Maze* maze, RandomI* coin);
    ~BinaryTreeDigger();
    
    virtual void Init();
    virtual bool Step();
    virtual void End();
    virtual void GetRandomsUsed(Array<RandomI*> &array);
    virtual void GetRandomsUsed(Array<RandomF*> &array);
    
private:
    RandomI* coin;
    int x, z;
};

#endif
