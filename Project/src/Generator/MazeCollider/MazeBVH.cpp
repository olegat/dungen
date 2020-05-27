//
//  MazeBVH.cpp
//  Dissert
//
//  Created by Olivier Legat on 22/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include <Generator/Maze/Maze.h>
#include <Generator/MazeMesh/MeshMaker/BasicMeshMaker.h>

#include "MazeBVH.h"

MazeBVH::MazeBVH() 
{
    this->root = NULL;
}
MazeBVH::~MazeBVH() {}

MazeBVH* MazeBVH::CreateBoundingVolumeHierarchy(BasicMeshMaker* maker)
{
    /*
    const Maze* maze = maker->GetMaze();
    
    // Create an AABB node for the floor:
    MazeColliderAABB* floorAABB = new MazeColliderAABB();
    floorAABB->SetHeight(0.01f);
    floorAABB->SetWidth(maker->GetCellWidth() * maze->Width());
    floorAABB->SetLength(maker->GetCellLength() * maze->Length());
    floorAABB->SetTranslation( floorAABB->GetVolume() / 2.0f );
    MazeBVHNode* floorNode = new MazeBVHNode();
    floorNode->collider = floorAABB;
    
    // Get properties of the mesh-maker.
    Vector3 position = maker->GetPosition();
    float width = maker->GetCellWidth();
    float height= maker->GetWallHeight();
    float length= maker->GetCellLength();
    float thick = maker->GetWallThickness();
    
    // Init the array of nodes.
    int maxWallCount = maze->VWallWidth() * maze->VWallLength()
                     + maze->HWallWidth() * maze->HWallLength() + 1;
    Array<MazeBVHNode*> nodes = Array<MazeBVHNode*> (maxWallCount);
    nodes[0] = floorNode;
    int i=1, x, z, n, m;
    
    // Create nodes for each horizontal wall:
    n = maze->HWallWidth();
    m = maze->HWallLength();
    for (x = 0; x < n; x++)
    {
        for ( z = 0; z < m; z++)
        {
            if( maze->GetHWall(x, z)->GetType() == MAZE_WALLTYPE_NONE ) continue;
            
            MazeColliderAABB* box = new MazeColliderAABB();
            
            Vector3 a; // min corner of the AABB.
            a.x = position.x + (width * x);
            a.y = position.y;
            a.z = position.z + (length * z) - thick / 2.0f;
            
            Vector3 b = a; // max corner of the AABB.
            b.x += width;  // just add volume to the min.
            b.y += height;
            b.z += thick;
            
            box->SetTranslation( a/2.0f + b/2.0f );
            box->SetVolume( Vector3(width, height, thick) );
            
            nodes[i++] = new MazeBVHNode(box);
        }
    }
    
    // Create nodes for each vertical wall:
    n = maze->VWallWidth();
    m = maze->VWallLength();
    for (x = 0; x < n; x++)
    {
        for ( z = 0; z < m; z++)
        {
            if( maze->GetVWall(x, z)->GetType() == MAZE_WALLTYPE_NONE ) continue;
            
            MazeColliderAABB* box = new MazeColliderAABB();
            
            Vector3 a; // min corner of the AABB.
            a.x = position.x + (width * x) - thick / 2.0f;
            a.y = position.y;
            a.z = position.z + (length * z);
            
            Vector3 b = a; // max corner of the AABB.
            b.x += thick;  // just add volume to the min.
            b.y += height;
            b.z += length;
            
            box->SetTranslation( a/2.0f + b/2.0f );
            box->SetVolume( Vector3(thick, height, length) );
            
            nodes[i++] = new MazeBVHNode(box);
        }
    }
    
    // Create root node and the BVH:
    MazeBVH* bvh = new MazeBVH();
    bvh->root = new MazeBVHNode(&nodes[0], i);
    
    nodes.clear();
    
    return bvh;*/
    
    const Maze* maze = maker->GetMaze();
    MazeCell* c1 = maze->GetCell(0, 0);
    MazeCell* c2 = maze->GetCell(maze->Width()-1, maze->Width()-1);
    
    MazeBVH* bvh = new MazeBVH();
    bvh->root = CreateBVHNode(maker, c1, c2);
    return bvh;
}

MazeBVHNode* MazeBVH::CreateBVHNode(BasicMeshMaker* maker, MazeCell* from, MazeCell* to)
{
    const Maze* maze = maker->GetMaze();
    MazeBVHNode* leaves[4];
    leaves[0] = leaves[1] = leaves[2] = leaves[3] = NULL;
    
    int leafCount = 0;
    int x = from->X(), z = from->Z();
    
    if ( from == to )
    {
        if ( maze->GetHWall(x, z)->GetType() != MAZE_WALLTYPE_NONE )
            leaves[leafCount++] = CreateHWallLeaf(maker, x, z);
        
        if ( maze->GetVWall(x, z)->GetType() != MAZE_WALLTYPE_NONE )
            leaves[leafCount++] = CreateVWallLeaf(maker, x, z);
        
        if ( x == maze->Width()-1   &&  maze->GetVWall(x+1, z)->GetType() != MAZE_WALLTYPE_NONE )
            leaves[leafCount++] = CreateVWallLeaf(maker, x+1, z);
        
        if ( z == maze->Length()-1  &&  maze->GetHWall(x, z+1)->GetType() != MAZE_WALLTYPE_NONE )
            leaves[leafCount++] = CreateHWallLeaf(maker, x, z+1);
    }
    else
    {
        /**
         * Divide space into 4 sub-spaces:
         *   +----+----+
         *   | s1 | s2 |
         *   +----+----+
         *   | s3 | s4 |
         *   +----+----+
         */
        int w = to->X() - from->X() + 1;
        int l = to->Z() - from->Z() + 1;
        
        // Top left cells of s1, s2, s3 and s4.
        Vector2 s1tl = Vector2 (x,       z      );
        Vector2 s2tl = Vector2 (x + w/2, z      );
        Vector2 s3tl = Vector2 (x,       z + l/2);
        Vector2 s4tl = Vector2 (x + w/2, z + l/2);
        
        int restw = w % 2;
        w = w / 2;
        int restl = l % 2;
        l = l / 2;
        
        // Bottom right cells of s1, s2, s3 and s4.
        Vector2 s1br = s1tl + Vector2(w-1,         l-1        );
        Vector2 s2br = s2tl + Vector2(w-1 + restw, l-1        );
        Vector2 s3br = s3tl + Vector2(w-1,         l-1 + restl);
        Vector2 s4br = s4tl + Vector2(w-1 + restw, l-1 + restl);
        
        if (s1tl.y != s3tl.y && s1tl.x != s2tl.x)
        {
            from = maze->GetCell(s1tl.x, s1tl.y);
            to   = maze->GetCell(s1br.x, s1br.y);
            leaves[leafCount++] = CreateBVHNode(maker, from, to);
        }
        if (s2tl.y != s4tl.y)
        {
            from = maze->GetCell(s2tl.x, s2tl.y);
            to   = maze->GetCell(s2br.x, s2br.y);
            leaves[leafCount++] = CreateBVHNode(maker, from, to);
        }
        if (s3tl.x != s4tl.x)
        {
            from = maze->GetCell(s3tl.x, s3tl.y);
            to   = maze->GetCell(s3br.x, s3br.y);
            leaves[leafCount++] = CreateBVHNode(maker, from, to);
        }
        // always make s4.
        {
            from = maze->GetCell(s4tl.x, s4tl.y);
            to   = maze->GetCell(s4br.x, s4br.y);
            leaves[leafCount++] = CreateBVHNode(maker, from, to);
        }
    }
    
    return new MazeBVHNode(leaves, leafCount);
}


MazeBVHNode* MazeBVH::CreateHWallLeaf(BasicMeshMaker* maker, int x, int z)
{
    // Get the maze:
    const Maze* maze = maker->GetMaze();
    
    // Get properties of the mesh-maker.
    Vector3 position = maker->GetPosition();
    float width = maker->GetCellWidth();
    float height= maker->GetWallHeight();
    float length= maker->GetCellLength();
    float thick = maker->GetWallThickness();
    
    if( maze->GetHWall(x, z)->GetType() == MAZE_WALLTYPE_NONE )
        return NULL;
    
    MazeColliderAABB* box = new MazeColliderAABB();
    
    Vector3 a; // min corner of the AABB.
    a.x = position.x + (width * x);
    a.y = position.y;
    a.z = position.z + (length * z) - thick / 2.0f;
    
    Vector3 b = a; // max corner of the AABB.
    b.x += width;  // just add volume to the min.
    b.y += height;
    b.z += thick;
    
    box->SetTranslation( a/2.0f + b/2.0f );
    box->SetVolume( Vector3(width, height, thick) );
    
    return new MazeBVHNode(box);
}


MazeBVHNode* MazeBVH::CreateVWallLeaf(BasicMeshMaker* maker, int x, int z)
{
    const Maze* maze = maker->GetMaze();
    
    // Get properties of the mesh-maker.
    Vector3 position = maker->GetPosition();
    float width = maker->GetCellWidth();
    float height= maker->GetWallHeight();
    float length= maker->GetCellLength();
    float thick = maker->GetWallThickness();
    
    if( maze->GetVWall(x, z)->GetType() == MAZE_WALLTYPE_NONE )
        return NULL;
    
    MazeColliderAABB* box = new MazeColliderAABB();
    
    Vector3 a; // min corner of the AABB.
    a.x = position.x + (width * x) - thick / 2.0f;
    a.y = position.y;
    a.z = position.z + (length * z);
    
    Vector3 b = a; // max corner of the AABB.
    b.x += thick;  // just add volume to the min.
    b.y += height;
    b.z += length;
    
    box->SetTranslation( a/2.0f + b/2.0f );
    box->SetVolume( Vector3(thick, height, length) );
    
    return new MazeBVHNode(box);
}

