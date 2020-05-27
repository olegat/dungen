//
//  SceneObject.h
//  Dissert
//
//  Created by Olivier Legat on 07/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef SCENE_OBJECT_H_
#define SCENE_OBJECT_H_

#include <platform.h>

class Mesh;
class MazeBVH;
class MazeColliderAABB;

class SceneObject
extends Object
{
public:
    SceneObject(unsigned int Id, String name);
    ~SceneObject();
    
    virtual String ToString() {return name; }
    
    Mesh* GetMesh() const {return this->mesh;}
    void SetMesh(Mesh* mesh) {this->mesh = mesh;}
    
    MazeBVH* GetBVH() const {return bvh;}
    void SetBVH(MazeBVH* bvh) {this->bvh = bvh;}
    
    bool IsMeshVisible() const {return rendermesh;}
    void SetMeshVisible(bool b) {this->rendermesh = b;}
    
    bool IsBVHVisible() const {return renderbvh;}
    void SetBVHVisible(bool b) {this->renderbvh = b;}
    
private:
    unsigned int Id;
    String name;
    Mesh* mesh;
    MazeBVH* bvh;
    
    bool rendermesh;
    bool renderbvh;
};

#endif
