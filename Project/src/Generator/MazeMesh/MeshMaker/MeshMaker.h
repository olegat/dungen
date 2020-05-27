//
//  MeshMaker.h
//  Dissert
//
//  Created by Olivier Legat on 08/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef MESH_MAKER_H_
#define MESH_MAKER_H_

#include <platform.h>
#include <Generator/Maze/Maze.h>

class MazeMesh;

/**
 * Abstract factor for generating meshes.
 * This class creates instances of MazeMesh but doesn't free them.
 */
interface MeshMaker
{
protected:
    /**
     * Create a factory
     */
    MeshMaker();
    
public:
    /**
     * Delete the factory
     */
    ~MeshMaker();
    
    /**
     * Generates Maze meshes
     * @param meshes [output] An array of generated meshed. 
     * @new Creates a new mesh instance for each element in the array. 
     */
    virtual void MakeMeshes(Array<MazeMesh*> &meshes)=0;
};

#endif
