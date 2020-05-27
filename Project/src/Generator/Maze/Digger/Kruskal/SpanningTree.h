//
//  SpanningTree.h
//  Dissert
//
//  Created by Olivier Legat on 22/06/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef SPANNING_TREE_H_
#define SPANNING_TREE_H_

#include <platform.h>

class Maze;
class MazeCell;

/**
 * This SpanningTree class in intended only for the use of Kruskal's algorithm
 * to quickly identify connected graphs.
 */
class SpanningTree
extends Object
{
public:
    SpanningTree();
    SpanningTree(MazeCell* firstNode);
    ~SpanningTree();

    int GetId() const {return Id;}
    List<MazeCell*>& GetCells() {return cells;}
    
    /**
     * Add all the cells of the other tree into this tree and DELETES that other tree.
     * Effectively this this merges both instances into 1.
     * This function also breaks the approriate walls in the maze.
     * @param otherTree A spanning tree to merge with.
     * @param maze The maze used to break walls.
     * @param cell1, cell2 The 2 nodes used to connect the 2 spanning trees.
     */
    void MergeWith(SpanningTree* otherTree, Maze* maze, MazeCell* cell1, MazeCell* cell2);
    
private:
    static int current_id;
    List<MazeCell*> cells;
    int Id;
};

#endif
