//
//  SceneSpace.cpp
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "SceneDynamic.h"
#include "SceneSpace.h"
#include "SceneObject.h"
#include <Engine/Graphics/Graphics.h>
#include <Engine/Tools/Math.h>
#include <Generator/MazeMesh/MeshMaker/VertexFactory.h>
#include <Generator/MazeCollider/MazeBVH.h>
#include <Generator/MazeCollider/MazeBVHNode.h>
#include <Generator/MazeCollider/MazeCollider.h>

SceneSpace::SceneSpace() 
{
    this->activeCamera = NULL;
}

SceneSpace::~SceneSpace() 
{
    int i,n;
    
    n = (int) objects.size();
    for ( i = 0; i < n; i++ ) delete objects[i];
    objects.clear();
    
    n = (int) dynamics.size();
    for ( i = 0; i < n; i++ ) delete dynamics[i];
    dynamics.clear();
}

SceneObject* SceneSpace::AddSceneObject() 
{
    return AddSceneObject("unnamed");
}
SceneObject* SceneSpace::AddSceneObject(String name)
{
    SceneObject* object;
    object = new SceneObject( (int) objects.size(), name);
    objects.push_back(object);
    return object;
}

SceneObject* SceneSpace::AddSceneObject(String name, Mesh* mesh)
{
    SceneObject* object = AddSceneObject(name);
    object->SetMesh(mesh);
    return object;
}

SceneDynamic* SceneSpace::AddSceneDynamic(Vector3 startPos, Vector3 volume)
{
    MazeColliderAABB* bb = new MazeColliderAABB();
    bb->SetTranslation(startPos);
    bb->SetVolume(volume);
    SceneDynamic* d = new SceneDynamic(bb);
    dynamics.push_back(d);
    return d;
}

SceneObject* SceneSpace::MakeGrid()
{
    Mesh* gridMesh = new Mesh();
    
    // Declare arrays:
    Array<float> gridVerts;
    Array<int> gridInds;
    Array<float> gridColors;
    
    // Init translation and orientation
    Vector3 pos = Vector3(0);
    Quaternion rot = Quaternion(Vector3(0, 0, 0));
    
    // Create data:
    VertexFactory::CreatePlane(gridVerts, gridInds, pos, rot, 10.0f, 10.0, 10, 10, GL_QUADS);
    VertexFactory::CreateColorArray(gridColors, (int) gridVerts.size() / 3, 0.5f, 0.5f, 0.5f);
    
    // Init mesh:
    gridMesh->SetVertices(&gridVerts[0], (int)gridVerts.size());
    gridMesh->SetIndices(&gridInds[0], (int)gridInds.size());
    gridMesh->SetColors(&gridColors[0], (int)gridColors.size());
    gridMesh->SetPrimitiveType(GL_QUADS);
    gridMesh->SetWireFramed(true);
    gridMesh->SetTwoSided(true);
    
    // Create scene object:
    return this->AddSceneObject("grid", gridMesh);
}

void SceneSpace::Update()
{
    if (activeCamera != NULL) activeCamera->Update();
    
    int nd = (int) dynamics.size();
    for (int d = 0; d < nd; d++)
    {
        checkCollisions(dynamics[d]);
    }
}

void SceneSpace::checkCollisions(SceneDynamic* dyn)
{
    int n = (int) objects.size();
    for (int i = 0; i < n; i++)
    {
        if ( objects[i]== NULL ) continue;
        if ( objects[i]->GetBVH() == NULL ) continue;
        
        checkCollisions(dyn, objects[i]->GetBVH());
    }
}

void SceneSpace::checkCollisions(SceneDynamic* dyn, MazeBVH* bvh)
{
    checkCollisions(dyn, bvh->GetRoot());
}

void SceneSpace::checkCollisions(SceneDynamic* dyn, MazeBVHNode* node)
{
    MazeColliderAABB* a = (MazeColliderAABB*) dyn->GetAABB();
    MazeColliderAABB* b = (MazeColliderAABB*) node->GetCollider();
    
    if ( a == NULL || b == NULL ) return; // no collider, hence no collision.
    
    if ( isColliding(dyn, b) )
    { 
        if ( node->IsLeaf() ) 
        { // do collision response:
            Vector3 overlap = calcOverlap(dyn, b);
            Vector3 direction = a->GetTranslation() - b->GetTranslation();
            
            // find axis where the difference is smallest:
            if (overlap.x <= overlap.y && overlap.x <= overlap.z) // x has the smallest distance.
            {
                float s = Math::sign(direction.x);
                float x = b->GetX() + s*((a->GetWidth() + b->GetWidth()) / 2.0f);
                a->SetX( x );
            }
            if (overlap.y <= overlap.x && overlap.y <= overlap.z) // y has the smallest distance.
            {
                float s = Math::sign(direction.y);
                float y = b->GetY() + s*((a->GetHeight() + b->GetHeight()) / 2.0f);
                a->SetY( y );
            }
            if (overlap.z <= overlap.x && overlap.z <= overlap.y) // z has the smallest distance.
            {
                float s = Math::sign(direction.z);
                float z = b->GetZ() + s*((a->GetLength() + b->GetLength()) / 2.0f);
                a->SetZ( z );
            }
        }
        
        else /* ( node is a parent ) */
        { // recurse on children:
            int n = node->GetChildrenCount();
            for ( int i = 0; i < n; i++ )
                checkCollisions(dyn, node->GetChild(i));
        }
    }
    else {/* no collision, do nothing. */}
}

Vector3 SceneSpace::calcOverlap(const SceneDynamic* dyn, const MazeColliderAABB* aabb) const
{
    Vector3 min = Math::min(dyn->GetAABB()->GetMinCorner(), aabb->GetMinCorner());
    Vector3 max = Math::max(dyn->GetAABB()->GetMaxCorner(), aabb->GetMaxCorner());
    
    return max - min;
}

bool SceneSpace::isColliding(const SceneDynamic* dyn, const MazeColliderAABB* b) const
{
    const MazeColliderAABB* a = dyn->GetAABB();
    
    float ax, ay, az, AX, AY, AZ;
    float bx, by, bz, BX, BY, BZ;
    
    a->GetAllMinMax(&ax,&ay,&az,&AX,&AY,&AZ);
    b->GetAllMinMax(&bx,&by,&bz,&BX,&BY,&BZ);
    
    return 
    !((ax >= BX) || (bx >= AX) ||
      (ay >= BY) || (by >= AY) ||
      (az >= BZ) || (bz >= AZ));
}

