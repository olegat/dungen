//
//  MazeMesh.cpp
//  Dissert
//
//  Created by Olivier Legat on 08/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "MazeMesh.h"

MazeMesh::MazeMesh() {
    
}
MazeMesh::~MazeMesh() {
    
}

void MazeMesh::SetVertices(List<float> verts) 
{
    this->vertices.clear();
    this->vertices = Array<float>( verts.size() );
    
    int i = 0;
    List<float>::iterator it;
    for ( it = verts.begin(); it != verts.end(); it++)
    {
         this->vertices[i++] = * it;
    }
}

void MazeMesh::SetIndices(List<int> indices) 
{
    this->indices.clear();
    this->indices = Array<int>( indices.size() );
    
    int i = 0;
    List<int>::iterator it;
    for ( it = indices.begin(); it != indices.end(); it++)
    {
        this->indices[i++] = * it;
    }
}

void MazeMesh::SetColors(List<float> color)
{
    this->color.clear();
    this->color = Array<float>( color.size() );
    
    int i = 0;
    List<float>::iterator it;
    for ( it = color.begin(); it != color.end(); it++)
    {
        this->color[i++] = * it;
    }
}

void MazeMesh::SetTexCoords(List<float> texcoords)
{
    this->texcoords.clear();
    this->texcoords = Array<float>( texcoords.size() );
    
    int i = 0;
    List<float>::iterator it;
    for ( it = texcoords.begin(); it != texcoords.end(); it++)
    {
        this->texcoords[i++] = * it;
    }
}

void MazeMesh::SetVertices(const float* vertices, const int count) 
{    
    assert(vertices);

    this->vertices.clear();
    this->vertices = Array<float>(count);
    
    for (int i = 0; i < count; i++) {
        this->vertices[i] = vertices[i];
    }
}

void MazeMesh::SetIndices(const int* indices, const int count)
{
    assert(indices);

    
    this->indices.clear();
    this->indices = Array<int>(count);
    
    for (int i = 0; i < count; i++) {
        this->indices[i] = indices[i];
    }
}

void MazeMesh::SetColors(const float* colors, const int count)
{
    assert(colors);
    
    this->color.clear();
    this->color = Array<float>(count);
    
    for (int i = 0; i < count; i++) {
        this->color[i] = colors[i];
    }
}

void MazeMesh::SetTexCoords(const float* texcoords, const int count)
{
    assert(texcoords);
    
    this->texcoords.clear();
    this->texcoords = Array<float>(count);
    
    for (int i = 0; i < count; i++) {
        this->texcoords[i] = texcoords[i];
    }
}

float* MazeMesh::GetVertices(int* n) const {
    *n = (int) vertices.size();
    return (float*) &vertices[0];
}
int* MazeMesh::GetIndices(int* n) const {
    *n = (int) indices.size();
    return (int*) &indices[0];
}
float* MazeMesh::GetColors(int* n) const {
    *n = (int) color.size();
    return (float*) &color[0];
}
float* MazeMesh::GetTexCoords(int *n) const {
    *n = (int) texcoords.size();
    return (float*) &texcoords[0];
}
