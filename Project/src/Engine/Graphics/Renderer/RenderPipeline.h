//
//  RenderPipeline.h
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef RENDER_PIPELINE_H_
#define RENDER_PIPELINE_H_

#include <platform.h>

class Camera;
class SceneSpace;
class Mesh;
class MazeBVH;
class MazeColliderAABB;

class RenderPipeline
extends Object
{
public:
    RenderPipeline(SceneSpace* scene);
    ~RenderPipeline();
    
    Camera* GetCamera() const;
    float GetAspectRatio() const;
    void GetMeshes(Array<Mesh*> *meshes) const;
    void GetBVHs(Array<MazeBVH*> *bvhs) const;
    void GetDynamicAABBs(Array<MazeColliderAABB*> *bbs) const;
    
private:
    SceneSpace* scene;
};

#endif
