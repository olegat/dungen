//
//  Prim.cpp
//  Dissert
//
//  Created by Olivier Legat on 18/06/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "PrimDigger.h"
#include <Generator/Random/Random.h>

PrimDigger::PrimDigger(Maze* maze, RandomI* picker) : Digger(maze)
{
    this->picker = picker;
}

PrimDigger::~PrimDigger()
{
    
}

void PrimDigger::Init()
{
    Digger::Init();
    parentNodes.push_back( lastVisitedCell );
}

bool PrimDigger::Step()
{
    // Pick a parent:
    MazeCell* parent = GetRandomParent();
    if (parent == NULL) return true;
    
    // Get all children:
    MazeCell* children[4] = {NULL, NULL, NULL, NULL};
    int childrenCount = 0;
    childrenCount = maze->GetUnvisitedCells(parent, children);
    
    // Pick a child:
    MazeCell* child = children[ picker->nextInt(0, childrenCount) ];
    
    // Log path:
    if (this->isLoggingPath())
        std::cout << parent->X() << "," << parent->Z() << std::endl;
    
    // Visit child and break wall:
    child->SetVisited(true);
    maze->BreakWalls(parent, child);
    
    // Update the parent node list:
    if (maze->GetUnvisitedCells(parent, NULL) == 0)
        parentNodes.remove( parent );
    
    if (maze->GetUnvisitedCells(child, NULL) != 0)
        parentNodes.push_back( child );
    
    return false;
}

MazeCell* PrimDigger::PickAParentInTheList()
{
    int n = (int) parentNodes.size();
    int picked = picker->nextInt(0, n);
    int i = 0;
    
    for (List<MazeCell*>::iterator j = parentNodes.begin(); j != parentNodes.end(); j++)
        if (i++ == picked) return *j;
    
    return NULL;
}

MazeCell* PrimDigger::GetRandomParent()
{
    MazeCell* parent = NULL;
    
    while ( parent == NULL && parentNodes.size() > 0 )
    {
        parent = PickAParentInTheList();
        if ( maze->GetUnvisitedCells(parent, 0) == 0 )
        {
            parentNodes.remove(parent);
            parent = NULL;
        }
    }
    
    return parent;
}

void PrimDigger::End()
{
    
}

void PrimDigger::GetRandomsUsed(Array<RandomI*> &array)
{
    array.push_back(picker);
}

void PrimDigger::GetRandomsUsed(Array<RandomF*> &array)
{
    
}
