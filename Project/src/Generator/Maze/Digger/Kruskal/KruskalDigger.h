//
//  Kruskal.h
//  Dissert
//
//  Created by Olivier Legat on 22/06/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef KRUSKAL_DIGGER_H_
#define KRUSKAL_DIGGER_H_

#include <Generator/Maze/Digger/Digger.h>
#include "KruskalEdge.h"

class KruskalDigger
extends Digger
{
public:
    KruskalDigger(Maze* maze, RandomI* picker);
    ~KruskalDigger();
    
    virtual void Init();
    virtual bool Step();
    virtual void End();
    
    virtual void GetRandomsUsed(Array<RandomI*> &array);
    virtual void GetRandomsUsed(Array<RandomF*> &array);
    
private:
    RandomI* picker;
    int currentEdge;
    Array<KruskalEdge> edges;
    
    void pick2(MazeCell** c1, MazeCell** c2);
};

#endif
