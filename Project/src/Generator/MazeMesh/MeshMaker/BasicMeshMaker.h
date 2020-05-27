//
//  BasicMeshMaker.h
//  Dissert
//
//  Created by Olivier Legat on 08/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef BASIC_MESH_MAKER_H_
#define BASIC_MESH_MAKER_H_

#include <platform.h>
#include "MeshMaker.h"

class Maze;

/**
 * A very primitive maze mesh factory.
 */
class BasicMeshMaker
extends Object
implements MeshMaker
{
public:
    /**
     * @param maze An initialized instance of maze (not NULL)
     */
    BasicMeshMaker(Maze* maze);
    /**
     * Destroy this factory. Doesn't free its assigned maze.
     */
    ~BasicMeshMaker();
    
    /**
     * Get the maze used to make the meshes.
     */
    const Maze* GetMaze() const {return this->maze;}
    
    /**
     * @param GL_QUADS or GL_TRIANGLES
     */
    void SetPrimitiveType(GLenum mode) {this->primitiveType = mode;}
    
    /**
     * @return GL_QUADS or GL_TRIANGLES
     */
    GLenum GetPrimitiveType() const {return this->primitiveType;}
    
    /**
     * @param t Thickness of the walls.
     */
    void SetWallThickness(float t) {this->wallThickness = t;}
    
    /**
     * @return The thickness of walls.
     */
    float GetWallThickness() const {return this->wallThickness;}
    
    /**
     * @param h The height of the walls.
     */
    void SetWallHeight(float h) {this->height = h;}
    
    /**
     * @return The height of the walls.
     */
    float GetWallHeight() {return this->height;}
    
    /**
     * @param w The width (x-distance) of each cell.
     */
    void SetCellWidth(float w) {this->width = w;}
    
    /**
     * @return The width (x-distance) of each cell.
     */
    float GetCellWidth() const {return this->width;}
    
    /**
     * @param l The length (z-distance) of each cell.
     */
    void SetCellLength(float l) {this->length = l;}
    
    /**
     * @param The length (z-distance) of each cell.
     */
    float GetCellLength() const {return this->length;}
    
    /**
     * Set the position of the bottom corner of cell 0,0
     * @param p The position.
     */
    void SetPosition(Vector3 p) {this->position = p;}
    
    /**
     * @return The position of the bottom corner of cell 0,0
     */
    Vector3 GetPosition() const {return this->position;}
    
    /** @see MeshMaker.h */
    virtual void MakeMeshes(Array<MazeMesh*> &meshes);
    
private:
    /**
     * The maze which we are using to generate the mesh.
     */
    Maze* maze;
    
    /**
     * Width / length of a single cell:
     */
    float width;
    float length;
    /**
     * Height of a wall:
     */
    float height;
    
    /**
     * Thickness of a wall:
     */
    float wallThickness;
    
    /**
     * Position the corner of the mesh at cell 0,0
     */
    Vector3 position;
    
    /**
     *
     */
    GLenum primitiveType;
    
    /**
     * @param verts [output] Appends created vertices to this array.
     * @param inds  [output] Append created indices to this array.
     */
    void makeWallVertices(List<float> &verts, List<int> &inds, List<float> &texcoords);
    /**
     * @param verts [output] Appends created vertices to this array.
     * @param inds  [output] Append created indices to this array.
     */
    void makeFloorVertices(Array<float> &verts, Array<int> &inds, Array<float> &texcoords);
    /**
     * @param verts [output] Appends created vertices to this array.
     * @param inds  [output] Append created indices to this array.
     */
    void makeCeilingVertices(Array<float> &verts, Array<int> &inds, Array<float> &texcoords);
};

#endif
