//
//  Renderer.cpp
//  Dissert
//
//  Created by Olivier Legat on 08/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include <platform.h>

#include <Engine/Core/Timing/Timing.h>
#include <Engine/Graphics/Graphics.h>
#include <Engine/Tools/Math.h>

#include <Generator/MazeCollider/MazeBVH.h>
#include <Generator/MazeCollider/MazeBVHNode.h>
#include <Generator/MazeCollider/MazeCollider.h>

#include "Renderer.h"
#include "RenderPipeline.h"

Renderer::Renderer(RenderPipeline* pipe)
{
    this->pipe = pipe;
}

Renderer::~Renderer()
{
    
}

void Renderer::ProcessCamera() 
{
    Camera* cam = pipe->GetCamera();
    
    if(cam == NULL) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    else {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(cam->fov, pipe->GetAspectRatio(), cam->nearClip, cam->farClip);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glRotatef(RAD2DEG( cam->pitch ), 1, 0, 0);
        glRotatef(RAD2DEG( cam->yaw ), 0, 1, 0);
        glRotatef(RAD2DEG( cam->roll ), 0, 0, 1);
        
        glTranslatef(cam->x, cam->y, cam->z);
    }
}


void Renderer::ProcessObjects() 
{
    Array<Mesh*> meshes;
    pipe->GetMeshes(&meshes);
    int n = (int) meshes.size();
    for (int i = 0; i < n; i++)
    {
        if (meshes[i] == NULL) continue;
        RenderMesh(meshes[i]);
    }
    meshes.clear();
    
    
    Array<MazeBVH*> bvhs;
    pipe->GetBVHs(&bvhs);
    n = (int) bvhs.size();
    
    for (int i = 0; i < n; i++)
    {
        if (bvhs[i] == NULL) continue;
        
        int h = bvhs[i]->GetRoot()->GetHeight();
        float rate = 0.8f;
        int depth = (int) (Timing::GameCurrentTime / rate) % h;
        
        RenderBVH(bvhs[i], depth);
    }
    bvhs.clear();
    
    
    Array<MazeColliderAABB*> bbs;
    pipe->GetDynamicAABBs(&bbs);
    n = (int) bbs.size();
    for (int i = 0; i < n; i++)
    {
        if (bbs[i] == NULL) continue;
        RenderAABB(bbs[i], Vector3(0, 1, 0));
    }
    bbs.clear();
}

void Renderer::RenderMesh(Mesh *mesh) 
{
    // Set cull mode:
    if (mesh->IsTwoSided()) glDisable(GL_CULL_FACE);
    else                    glEnable(GL_CULL_FACE);
    
    switch (mesh->GetDisplayMode()) {
        case MESH_EDGED: RenderEdgedMesh(mesh); break;
        case MESH_SOLID: RenderSolidMesh(mesh); break;
        case MESH_TEXTURED: RenderTexturedMesh(mesh); break;
        case MESH_WIREFRAME: RenderWireframedMesh(mesh); break;
        default: break;
    }
}

void Renderer::RenderWireframedMesh(Mesh* mesh)
{
    int nverts, nindices, ncolors;
    
    // Get data:
    float* vertices = mesh->GetVertices(&nverts);
    int* indices = mesh->GetIndices(&nindices);
    float* colors = mesh->GetColors(&ncolors);
    glDisable ( GL_TEXTURE_2D );
    
    // Draw triangles:
    glFrontFace (GL_CW);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glBegin( mesh->GetPrimitiveType() );
    for (int i = 0; i < nindices; i++) 
    {
        int j = indices[i];
        
        glColor3f(colors[j], colors[j+1], colors[j+2]);
        glVertex3f(vertices[j], vertices[j+1], vertices[j+2]);
        
    }
    glEnd();
}

void Renderer::RenderSolidMesh(Mesh* mesh)
{
    int nverts, nindices, ncolors;
    
    // Get data:
    float* vertices = mesh->GetVertices(&nverts);
    int* indices = mesh->GetIndices(&nindices);
    float* colors = mesh->GetColors(&ncolors);
    glDisable (GL_TEXTURE_2D);
    
    // Draw triangles:
    glFrontFace (GL_CW);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glBegin( mesh->GetPrimitiveType() );
    for (int i = 0; i < nindices; i++) 
    {
        int j = indices[i];
        
        glColor3f(colors[j], colors[j+1], colors[j+2]);
        glVertex3f(vertices[j], vertices[j+1], vertices[j+2]);
        
    }
    glEnd();
}

void Renderer::RenderEdgedMesh(Mesh* mesh)
{
    int nverts, nindices, ncolors;
    
    glFrontFace (GL_CCW);
    
    // Get data:
    float* vertices = mesh->GetVertices(&nverts);
    int* indices = mesh->GetIndices(&nindices);
    float* colors = mesh->GetColors(&ncolors);
    glDisable (GL_TEXTURE_2D);
    
    // Draw triangles:
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glBegin( mesh->GetPrimitiveType() );
    for (int i = 0; i < nindices; i++) 
    {
        int j = indices[i];
        
        glColor3f(colors[j], colors[j+1], colors[j+2]);
        glVertex3f(vertices[j], vertices[j+1], vertices[j+2]);
        
    }
    glEnd();
    
    // Draw edges:
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glBegin( mesh->GetPrimitiveType() );
    for (int i = 0; i < nindices; i++) 
    {
        int j = indices[i];
        
        glColor3f(1 - colors[j], 1 - colors[j+1], 1 - colors[j+2]); //invert color
        glVertex3f(vertices[j], vertices[j+1], vertices[j+2]);
        
    }
    glEnd();
}

void Renderer::RenderTexturedMesh(Mesh* mesh)
{
    int nverts, nindices, ncolors;
    
    // Get data:
    float* vertices = mesh->GetVertices(&nverts);
    int* indices = mesh->GetIndices(&nindices);
    float* texcoords = mesh->GetTexCoords(&ncolors);
    Texture* diffuse = mesh->GetMaterial()->GetDiffuse();
    
    // Bind and enable texture
    glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, diffuse->GetTextureId());
    
    // Draw triangles:
    glFrontFace (GL_CW);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glBegin( mesh->GetPrimitiveType() );
    for (int i = nindices-1; i >= 0; i--) 
    {
        int j = indices[i];
        int t = (j / 3) * 2;
        
        glTexCoord2f(texcoords[t], 1 - texcoords[t+1]);
        glColor3f(0.7f, 0.7f, 0.7f);
        glVertex3f(vertices[j], vertices[j+1], vertices[j+2]);
        
    }
    glEnd();
}

void Renderer::Render() 
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glClearColor(0, 0, 0, 1.0f);
    
    ProcessCamera();
    
    ProcessObjects();
    
    glFlush();
}

void Renderer::RenderBVH(MazeBVH* bvh, int depth)
{
    RenderBVH(bvh->GetRoot(), depth);
}

void Renderer::RenderBVH(MazeBVHNode* root, int depth)
{
    if (depth == 0)
    {
        MazeColliderAABB* aabb = dynamic_cast<MazeColliderAABB*>(root->GetCollider());
        if (aabb != NULL)
            RenderAABB( aabb );
    }
    else
        for (int i = 0; i < root->GetChildrenCount(); i++)
            RenderBVH(root->GetChild(i), depth-1);
}

void Renderer::RenderBVHNode(MazeBVHNode* node)
{
    RenderAABB( (MazeColliderAABB*) node->GetCollider() );
    
    int n = node->GetChildrenCount();
    for (int i = 0; i < n; i++)
    {
        RenderBVHNode(node->GetChild(i));
    }
}

void Renderer::RenderAABB(MazeColliderAABB *bb)
{
    RenderAABB(bb, Vector3(1.0f, 0, 0) );
}

void Renderer::RenderAABB(MazeColliderAABB *bb, Vector3 color)
{
    if (bb == NULL) return;
    
	glFrontFace (GL_CW);
    glDisable ( GL_TEXTURE_2D );
    glDisable ( GL_CULL_FACE );
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    float x,y,z,X,Y,Z,w,l,h;
    bb->GetAllMinMax(&x, &y, &z, &X, &Y, &Z);
    bb->GetVolume(&w, &h, &l);
    
    glBegin(GL_LINES);
    
    glColor3f(color.x, color.y, color.z);
    
    // Front face:
    glVertex3f(x, y, z);
    glVertex3f(x, y+h, z);
    glVertex3f(x, y+h, z);
    glVertex3f(x+w, y+h, z);
    glVertex3f(x+w, y+h, z);
    glVertex3f(x+w, y, z);
    glVertex3f(x+w, y, z);
    glVertex3f(x, y, z);
    
    // Back face:
    glVertex3f(x, y, z+l);
    glVertex3f(x, y+h, z+l);
    glVertex3f(x, y+h, z+l);
    glVertex3f(x+w, y+h, z+l);
    glVertex3f(x+w, y+h, z+l);
    glVertex3f(x+w, y, z+l);
    glVertex3f(x+w, y, z+l);
    glVertex3f(x, y, z+l);
    
    // Edges linking front and back:
    glVertex3f(x, y, z);
    glVertex3f(x, y, z+l);
    glVertex3f(x, y+h, z);
    glVertex3f(x, y+h, z+l);
    glVertex3f(x+w, y, z);
    glVertex3f(x+w, y, z+l);
    glVertex3f(x+w, y+h, z);
    glVertex3f(x+w, y+h, z+l);
    
    glEnd();
}



