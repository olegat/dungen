//
//  SpanningTree.cpp
//  Dissert
//
//  Created by Olivier Legat on 22/06/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "SpanningTree.h"

#include <Generator/Maze/Maze.h>

int SpanningTree::current_id = 0;

SpanningTree::SpanningTree()
{
    Id = current_id++;
}
SpanningTree::SpanningTree(MazeCell* firstNode)
{
    this->Id = current_id++;
    this->cells.push_back(firstNode);
}

SpanningTree::~SpanningTree()
{
    this->cells.clear();
}

void SpanningTree::MergeWith(SpanningTree* otherTree, Maze* maze, MazeCell* cell1, MazeCell* cell2)
{
    // Get other cells
    List<MazeCell*> otherCells = otherTree->GetCells();
    List<MazeCell*>::iterator it;
    
    // Move other cells:
    for (it = otherCells.begin(); it != otherCells.end(); it ++)
    {
        cells.push_back(*it);
        (*it)->SetObject(this);
    }
    
    // Delete other tree
    delete otherTree;
    
    // Break walls:
    maze->BreakWalls(cell1, cell2);
}
