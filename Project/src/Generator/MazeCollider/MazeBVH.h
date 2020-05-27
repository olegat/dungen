//
//  MazeBVH.h
//  Dissert
//
//  Created by Olivier Legat on 22/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef MAZE_BVH_H_
#define MAZE_BVH_H_

#include <platform.h>

#include "MazeBVHNode.h"

class MazeCell;
class BasicMeshMaker;

class MazeBVH
extends Object
{
public:
    MazeBVH();
    ~MazeBVH();
    
    MazeBVHNode* GetRoot() const { return root; }
    
    /**
     * @param maker A basic mesh maker with a referenced maze (maker->GetMaze() != NULL)
     * @return A new allocated instance of MazeBVH.
     */
    static MazeBVH* CreateBoundingVolumeHierarchy(BasicMeshMaker* maker);
    
private:
    MazeBVHNode* root;
    
    /**
     * Create a node recursively
     */
    static MazeBVHNode* CreateBVHNode(BasicMeshMaker* maker, MazeCell* from, MazeCell* to);
    
    /**
     * Create the AABB and MazeBVHNode instances for the horizontal (x, z).
     * @return NULL if there's no wall at (x,z)
     *         otherwise it returns a newly created leaf containing the collider of hwall (x,z).
     */
    static MazeBVHNode* CreateHWallLeaf(BasicMeshMaker* maker, int x, int z);
    
    /**
     * Create the AABB and MazeBVHNode instances for the vertical (x, z).
     * @return NULL if there's no wall at (x,z)
     *         otherwise it returns a newly created leaf containing the collider of vwall (x,z).
     */
    static MazeBVHNode* CreateVWallLeaf(BasicMeshMaker* maker, int x, int z);
};

#endif
