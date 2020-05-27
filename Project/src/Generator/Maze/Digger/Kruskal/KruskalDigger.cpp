//
//  Kruskal.cpp
//  Dissert
//
//  Created by Olivier Legat on 22/06/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "KruskalDigger.h"
#include "SpanningTree.h"
#include <Generator/Maze/Maze.h>

KruskalDigger::KruskalDigger(Maze* maze, RandomI* picker) : Digger(maze)
{
    this->picker = picker;
}

KruskalDigger::~KruskalDigger()
{
    
}

void KruskalDigger::Init()
{
    Digger::Init();
    
    int x, z;
    
    // Create initial spanning trees.
    for (x = 0; x < maze->Width();  x++)
    for (z = 0; z < maze->Length(); z++)
    {
        MazeCell* cell = maze->GetCell(x, z);
        cell->SetObject(new SpanningTree(cell));
    }
    
    // Initialise wall structure:
    int nVWalls = (maze->VWallWidth()-2) * maze->VWallLength();
    int nHWalls = maze->HWallWidth() * (maze->HWallLength()-2);
    int nWalls =  nVWalls + nHWalls;
    edges = Array<KruskalEdge>(nWalls);
    currentEdge = 0;
    int i = 0;
    
    // Initialise v-walls:
    for (x = 1; x < maze->Width();  x++)
    for (z = 0; z < maze->Length(); z++)
    {
        edges[i].type = KRUSKAL_EDGE_TYPE_VWALL;
        edges[i].x = x;
        edges[i].z = z;
        i++;
    }
    
    // Initialise h-walls:
    for (x = 0; x < maze->Width();  x++)
    for (z = 1; z < maze->Length(); z++)
    {
        edges[i].type = KRUSKAL_EDGE_TYPE_HWALL;
        edges[i].x = x;
        edges[i].z = z;
        i++;
    }
    
    KruskalEdge::Shuffle(edges, picker, 3);
}

bool KruskalDigger::Step()
{    
    // Pick two cells
    MazeCell *c1, *c2;
    pick2(&c1, &c2);
    
    // Get the spanning trees:
    SpanningTree *t1, *t2;
    t1 = dynamic_cast<SpanningTree*>(c1->GetObject());
    t2 = dynamic_cast<SpanningTree*>(c2->GetObject());
    assert(t1 && t2);
    
    // Are they 2 distinct spanning tree?
    if (t1->GetId() != t2->GetId())
    {
        // Pour t2's content into t1. Delete t2. Break walls:
        t1->MergeWith(t2, maze, c1, c2);
    }
    
    return currentEdge >= edges.size();
}

void KruskalDigger::pick2(MazeCell** c1, MazeCell** c2)
{
    *c1 = NULL;
    *c2 = NULL;
    
    while((*c1 == NULL || *c2 == NULL) && currentEdge < edges.size() )
    {
        assert (edges[currentEdge].type);
        
        int x = edges[currentEdge].x;
        int z = edges[currentEdge].z;
        
        if ( edges[currentEdge].type == KRUSKAL_EDGE_TYPE_HWALL )
            maze->GetTopAndBottomCell(x, z, c1, c2);
        
        else if ( edges[currentEdge].type == KRUSKAL_EDGE_TYPE_VWALL )
            maze->GetLeftAndRightCell(x, z, c1, c2);
        
        currentEdge++;
    }
}

void KruskalDigger::End()
{
    Digger::End();
    
    // Find all remaining spanning tree instances:
    Array<SpanningTree*> trees;
    for (int x = 0; x < maze->Width();  x++)
    for (int z = 0; z < maze->Length(); z++)
    {
        MazeCell* cell = maze->GetCell(x, z);
        SpanningTree* tree = dynamic_cast<SpanningTree*>(cell->GetObject());
        assert(tree);
        
        bool contains = false;
        for( size_t i = 0; i < trees.size(); i++ )
            if ( trees[i] == tree )
            {
                contains = true;
                break;
            }
        
        if (! contains ) trees.push_back(tree);
    }
    
    // Delete all remaining spanning tree instances:
    for( size_t j = 0; j < trees.size(); j++ )
    {
        delete trees[j];
    }
    trees.clear();
    
    // Delete all edges:
    edges.clear();
}

void KruskalDigger::GetRandomsUsed(Array<RandomI*> &array)
{
    
}
void KruskalDigger::GetRandomsUsed(Array<RandomF*> &array) {}
