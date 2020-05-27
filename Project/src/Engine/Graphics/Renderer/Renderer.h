//
//  Renderer.h
//  Dissert
//
//  Created by Olivier Legat on 08/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef RENDERER_H_
#define RENDERER_H_

#include <platform.h>

class RenderPipeline;
class Mesh;
class MazeBVH;
class MazeBVHNode;
class MazeColliderAABB;

class Renderer
extends Object
{
public:
    Renderer(RenderPipeline* pipe);
    ~Renderer();
    
    void Render();
    
private:
    RenderPipeline* pipe;
    
    void ProcessCamera();
    void ProcessObjects();
    
    void RenderMesh(Mesh* mesh);
    void RenderWireframedMesh(Mesh* mesh);
    void RenderSolidMesh(Mesh* mesh);
    void RenderEdgedMesh(Mesh* mesh);
    void RenderTexturedMesh(Mesh* mesh);
    
    void RenderBVH(MazeBVH* bvh, int depth);
    void RenderBVH(MazeBVHNode* root, int depth);
    void RenderBVHNode(MazeBVHNode* node);
    
    void RenderAABB(MazeColliderAABB* aabb);
    void RenderAABB(MazeColliderAABB* aabb, Vector3 color);
};

#endif
