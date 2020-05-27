//
//  SceneDynamic.h
//  Dissert
//
//  Created by Olivier Legat on 24/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef SCENE_DYNAMIC_H_
#define SCENE_DYNAMIC_H_

#include <platform.h>
#include <Generator/MazeCollider/MazeCollider.h>

class SceneDynamic
extends Object
{
public:
    SceneDynamic(MazeColliderAABB* aabb);
    ~SceneDynamic();
    
    Vector3 GetTranslation() const {return aabb->GetTranslation();}
    void SetTranslation(Vector3 t) {this->aabb->SetTranslation(t);}
    void SetTranslation(float x, float y, float z) {SetTranslation(Vector3(x,y,z));}
    void Translate(Vector3 t);
    void Translate(float x, float y, float z) {Translate(Vector3(x,y,z));}
    
    MazeColliderAABB* GetAABB() const {return aabb;}
    void SetAABB(MazeColliderAABB* aabb) {this->aabb = aabb;}

    bool IsVisible() const {return visible;}
    void SetVisible(bool v) {visible = v;}
    
private:
    MazeColliderAABB* aabb;
    bool visible;
};

#endif
