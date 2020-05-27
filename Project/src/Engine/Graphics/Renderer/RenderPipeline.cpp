//
//  RenderPipeline.cpp
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include <Engine/Scene/Scene.h>
#include <Engine/Graphics/Camera/Camera.h>

#include <Generator/MazeCollider/MazeBVH.h>
#include <Generator/MazeCollider/MazeCollider.h>

#include "RenderPipeline.h"

RenderPipeline::RenderPipeline(SceneSpace* scene)
{
    this->scene = scene;
}

RenderPipeline::~RenderPipeline()
{
    
}

Camera* RenderPipeline::GetCamera() const
{
    return this->scene->GetActiveCamera();
}

float RenderPipeline::GetAspectRatio() const
{
    return 4.0f / 3.0f;
}

void RenderPipeline::GetMeshes(Array<Mesh*> *meshes) const
{
    int n = this->scene->GetObjectCount();
    
    for (int i = 0; i < n; i ++)
    {
        SceneObject* obj = scene->GetSceneObject(i);
        if(obj == NULL || !obj->IsMeshVisible()) continue;
        
        meshes->push_back(obj->GetMesh());
    }
}

void RenderPipeline::GetBVHs(Array<MazeBVH*> *bvhs) const
{
    int n = this->scene->GetObjectCount();
    
    for (int i = 0; i < n; i ++)
    {
        SceneObject* obj = scene->GetSceneObject(i);
        if(obj == NULL || !obj->IsBVHVisible()) continue;
        
        bvhs->push_back(obj->GetBVH());
    }
}

void RenderPipeline::GetDynamicAABBs(Array<MazeColliderAABB*> *bbs) const
{
    int n = this->scene->GetDynamicCount();
    
    for (int i = 0; i < n; i ++)
    {
        SceneDynamic* d = scene->GetSceneDynamic(i);
        if( d == NULL || ! d->IsVisible() || d->GetAABB() == NULL ) continue;
        
        bbs->push_back(d->GetAABB());
    }
}

