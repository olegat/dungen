//
//  BasicMeshMaker.cpp
//  Dissert
//
//  Created by Olivier Legat on 08/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "BasicMeshMaker.h"
#include "VertexFactory.h"
#include "../MazeMesh.h"
#include <Engine/Tools/Math.h>

BasicMeshMaker::BasicMeshMaker(Maze* maze) {
    this->maze = maze;
    
    this->width = 1.0f;   // cell width
    this->length = 1.0f;  // cell length
    this->height = 1.0f;  // wall height
    this->wallThickness = 0.08f; // wall thickness
    
    this->position = Vector3(0);
    this->primitiveType = GL_TRIANGLES;
}

BasicMeshMaker::~BasicMeshMaker() {
    
}

void BasicMeshMaker::MakeMeshes(Array<MazeMesh*> &meshes) 
{
    meshes = Array<MazeMesh*>(3);
    
    // Make the walls:
    List<float> lverts = List<float>();
    List<int> linds = List<int>();
    List<float> ltexs = List<float>();
    Array<float> wallColors;
    makeWallVertices(lverts, linds, ltexs);
    VertexFactory::CreateColorArray(wallColors, (int) lverts.size() / 3, 1.0f, 0.0f, 0.0f);
    meshes[0] = new MazeMesh();
    meshes[0]->SetVertices(lverts);
    meshes[0]->SetIndices(linds);
    meshes[0]->SetColors(wallColors);
    meshes[0]->SetTexCoords(ltexs);
    meshes[0]->SetName("walls");
    lverts.clear();
    linds.clear();
    wallColors.clear();
    
    // Make the floor
    Array<float> floorVerts = Array<float>();
    Array<int> floorInds = Array<int>();
    Array<float> floorColor = Array<float>();
    Array<float> floorTexs = Array<float>();
    makeFloorVertices(floorVerts, floorInds, floorTexs);
    VertexFactory::CreateColorArray(floorColor, (int) floorVerts.size(), 0.5f, 0.5f, 0.2f);
    meshes[1] = new MazeMesh();
    meshes[1]->SetVertices(floorVerts);
    meshes[1]->SetIndices(floorInds);
    meshes[1]->SetColors(floorColor);
    meshes[1]->SetTexCoords(floorTexs);
    meshes[1]->SetName("floor");
    floorVerts.clear();
    floorInds.clear();
    floorColor.clear();
    
    // Make the ceiling
    Array<float> ceilingVerts = Array<float>();
    Array<int> ceilingInds = Array<int>();
    Array<float> ceilingColor = Array<float>();
    Array<float> ceilingTexs = Array<float>();
    makeCeilingVertices(ceilingVerts, ceilingInds, ceilingTexs);
    VertexFactory::CreateColorArray(ceilingColor, (int) ceilingVerts.size(), 0.5f, 0.5f, 0.2f);
    meshes[2] = new MazeMesh();
    meshes[2]->SetVertices(ceilingVerts);
    meshes[2]->SetIndices(ceilingInds);
    meshes[2]->SetColors(ceilingColor);
    meshes[2]->SetTexCoords(ceilingTexs);
    meshes[2]->SetName("ceiling");
    ceilingVerts.clear();
    ceilingInds.clear();
    ceilingColor.clear();
}

void BasicMeshMaker::makeWallVertices(List<float> &verts, List<int> &inds, List<float> &texcoords)
{
    unsigned int x, z, n, m;
    MazeWall* wall;
    
    // Init wall data arrays:
    Array<float> wallVerts = Array<float>();
    Array<int> wallInds = Array<int>();
    
    // For each horizontal wall:
    n = maze->HWallWidth();
    m = maze->HWallLength();
    for (x = 0; x < n; x++)
        for ( z = 0; z < m; z++)
        {
            wall = maze->GetHWall(x, z);
            if (wall->GetType() == MAZE_WALLTYPE_NONE) continue; // No wall. Ditch.
            
            Vector3 o; // center of the wall (pivot point, origin).
            o.x = position.x + (width * x) + width / 2;
            o.y = position.y + height / 2;
            o.z = position.z + (length * z);
            Quaternion r = Quaternion(Vector3(0));
            
            VertexFactory::CreateCuboid(wallVerts, wallInds, o, r, Vector3(width, height, wallThickness),
                                        1, 1, 1, primitiveType);
            VertexFactory::MergeVertices(verts, inds, wallVerts, wallInds);
            
            {
                // Front face
                texcoords.push_back(0.0f); texcoords.push_back(0.0f);
                texcoords.push_back(0.0f); texcoords.push_back(1.0f);
                texcoords.push_back(1.0f); texcoords.push_back(0.0f);
                texcoords.push_back(1.0f); texcoords.push_back(1.0f);
                
                // Back face (mirrored vertically)
                texcoords.push_back(1.0f); texcoords.push_back(1.0f);
                texcoords.push_back(1.0f); texcoords.push_back(0.0f);
                texcoords.push_back(0.0f); texcoords.push_back(1.0f);
                texcoords.push_back(0.0f); texcoords.push_back(0.0f);
                
                // Left face (flipped 90°)
                texcoords.push_back(0.0f); texcoords.push_back(0.0f);
                texcoords.push_back(1.0f); texcoords.push_back(0.0f);
                texcoords.push_back(0.0f); texcoords.push_back(1.0f);
                texcoords.push_back(1.0f); texcoords.push_back(1.0f);
                
                // Right face (flipped 270°)
                texcoords.push_back(1.0f); texcoords.push_back(1.0f);
                texcoords.push_back(0.0f); texcoords.push_back(1.0f);
                texcoords.push_back(1.0f); texcoords.push_back(0.0f);
                texcoords.push_back(0.0f); texcoords.push_back(0.0f);
                
                // Top face (flipped 90°)
                texcoords.push_back(0.0f); texcoords.push_back(0.0f);
                texcoords.push_back(1.0f); texcoords.push_back(0.0f);
                texcoords.push_back(0.0f); texcoords.push_back(1.0f);
                texcoords.push_back(1.0f); texcoords.push_back(1.0f);
                
                // Bottom face
                texcoords.push_back(0.0f); texcoords.push_back(0.0f);
                texcoords.push_back(0.0f); texcoords.push_back(1.0f);
                texcoords.push_back(1.0f); texcoords.push_back(0.0f);
                texcoords.push_back(1.0f); texcoords.push_back(1.0f);
            }
            
            wallVerts.clear();
            wallInds.clear();
        }
    
    
    // For each horizontal wall:
    n = maze->VWallWidth();
    m = maze->VWallLength();
    for (x = 0; x < n; x++)
        for ( z = 0; z < m; z++)
        {
            wall = maze->GetVWall(x, z);
            if (wall->GetType() == MAZE_WALLTYPE_NONE) continue; // No wall. Ditch.
            
            Vector3 o; // center of the wall (pivot point, origin).
            o.x = position.x + (width * x);
            o.y = position.y + height / 2;
            o.z = position.z + (length * z) + length / 2;
            Quaternion r = Quaternion(Vector3(0));
            
            VertexFactory::CreateCuboid(wallVerts, wallInds, o, r, Vector3(wallThickness, height, length),
                                        1, 1, 1, primitiveType);
            VertexFactory::MergeVertices(verts, inds, wallVerts, wallInds);
            
            {
                // Front face
                texcoords.push_back(0.0f); texcoords.push_back(0.0f);
                texcoords.push_back(0.0f); texcoords.push_back(1.0f);
                texcoords.push_back(1.0f); texcoords.push_back(0.0f);
                texcoords.push_back(1.0f); texcoords.push_back(1.0f);
                
                // Back face (mirrored vertically)
                texcoords.push_back(1.0f); texcoords.push_back(1.0f);
                texcoords.push_back(1.0f); texcoords.push_back(0.0f);
                texcoords.push_back(0.0f); texcoords.push_back(1.0f);
                texcoords.push_back(0.0f); texcoords.push_back(0.0f);
                
                // Left face (flipped 90°)
                texcoords.push_back(0.0f); texcoords.push_back(0.0f);
                texcoords.push_back(1.0f); texcoords.push_back(0.0f);
                texcoords.push_back(0.0f); texcoords.push_back(1.0f);
                texcoords.push_back(1.0f); texcoords.push_back(1.0f);
                
                // Right face (flipped 270°)
                texcoords.push_back(1.0f); texcoords.push_back(1.0f);
                texcoords.push_back(0.0f); texcoords.push_back(1.0f);
                texcoords.push_back(1.0f); texcoords.push_back(0.0f);
                texcoords.push_back(0.0f); texcoords.push_back(0.0f);
                
                // Top face
                texcoords.push_back(0.0f); texcoords.push_back(0.0f);
                texcoords.push_back(0.0f); texcoords.push_back(1.0f);
                texcoords.push_back(1.0f); texcoords.push_back(0.0f);
                texcoords.push_back(1.0f); texcoords.push_back(1.0f);
                
                // Bottom face
                texcoords.push_back(0.0f); texcoords.push_back(0.0f);
                texcoords.push_back(0.0f); texcoords.push_back(1.0f);
                texcoords.push_back(1.0f); texcoords.push_back(0.0f);
                texcoords.push_back(1.0f); texcoords.push_back(1.0f);
            }
            
            wallVerts.clear();
            wallInds.clear();
        }
}

void BasicMeshMaker::makeFloorVertices(Array<float> &verts, Array<int> &inds, Array<float> &texcoords)
{
    // Calculate width / length of the mesh.
    float totalWidth = width * maze->Width();
    float totalLength = length * maze->Length();
    
    Vector3 o = position + Vector3(totalWidth / 2.0f, 0, totalLength / 2.0f);
    
    VertexFactory::CreatePlane(verts, inds, o, Quaternion(Vector3(0)),
                               totalWidth, totalLength, 1, 1, primitiveType);
    
    texcoords.push_back(0.0f); texcoords.push_back(0.0f);
    texcoords.push_back(0.0f); texcoords.push_back(totalLength);
    texcoords.push_back(totalWidth); texcoords.push_back(0.0f);
    texcoords.push_back(totalWidth); texcoords.push_back(totalLength);
}

void BasicMeshMaker::makeCeilingVertices(Array<float> &verts, Array<int> &inds, Array<float> &texcoords)
{
    // Calculate width / length of the mesh.
    float totalWidth = width * maze->Width();
    float totalLength = length * maze->Length();
    
    Vector3 o = position + Vector3(totalWidth / 2.0f, 1, totalLength / 2.0f);
    
    VertexFactory::CreatePlane(verts, inds, o, Quaternion(Vector3(PI, 0, 0)),
                               totalWidth, totalLength, 1, 1, primitiveType);
    
    texcoords.push_back(0.0f); texcoords.push_back(0.0f);
    texcoords.push_back(0.0f); texcoords.push_back(totalLength);
    texcoords.push_back(totalWidth); texcoords.push_back(0.0f);
    texcoords.push_back(totalWidth); texcoords.push_back(totalLength);
}

