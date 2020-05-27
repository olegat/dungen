//
//  MazeMesh.h
//  Dissert
//
//  Created by Olivier Legat on 08/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef MAZE_MESH_H_
#define MAZE_MESH_H_

#include <platform.h>

class MazeMesh : Object
{
    friend class MeshMaker;
public:
    MazeMesh();
    ~MazeMesh();
    
    String GetName() const {return name;}
    void SetName(const String name) {this->name = name;}
    
    void SetVertices(Array<float> vertices) {SetVertices(&vertices[0], (int) vertices.size());}
    void SetIndices(Array<int> indices) {SetIndices(&indices[0], (int) indices.size());}
    void SetColors(Array<float> color) {SetColors(&color[0], (int) color.size());}
    void SetTexCoords(Array<float> texcoords) {SetTexCoords(&texcoords[0], (int) texcoords.size());}
    
    void SetVertices(List<float> vertices);
    void SetIndices(List<int> indices);
    void SetColors(List<float> color);
    void SetTexCoords(List<float> color);
    
    void SetVertices(const float* vertices, const int count);
    void SetIndices(const int* indices, const int count);
    void SetColors(const float* colors, const int count);
    void SetTexCoords(const float* colors, const int count);
    
    float* GetVertices(int* n) const;
    int* GetIndices(int* n) const;
    float* GetColors(int* n) const;
    float* GetTexCoords(int* n) const;
    
private:
    bool cacheData;
    
    Array<float> vertices;
    Array<int> indices;
    Array<float> color;
    Array<float> texcoords;
    
    String name;
};

#endif
