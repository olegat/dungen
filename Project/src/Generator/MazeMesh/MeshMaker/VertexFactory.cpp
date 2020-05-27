//
//  VertexFactor.cpp
//  Dissert
//
//  Created by Olivier Legat on 10/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include <platform.h>
#include <Engine/Tools/Math.h> // just for PI.
#include "VertexFactory.h"

VertexFactory::VertexFactory() {
    
}
VertexFactory::~VertexFactory() {
    
}

/*template<class T> void VertexFactory::ToArray(List<T> &l, Array<T> &a) 
{
    a = Array<T>(l.size());
    
    int i = 0;
    List<T>::iterator it;
    for (it = l.begin(); it != l.end(); it++)
        a[i++] = * it;
}*/

void VertexFactory::ToArray(List<float> &l, Array<float> &a) {
    a = Array<float>(l.size());
    
    int i = 0;
    List<float>::iterator it;
    for (it = l.begin(); it != l.end(); it++)
        a[i++] = * it;
}
void VertexFactory::ToArray(List<int> &l, Array<int> &a) {
    a = Array<int>(l.size());
    
    int i = 0;
    List<int>::iterator it;
    for (it = l.begin(); it != l.end(); it++)
        a[i++] = * it;
}

void VertexFactory::MergeVertices(List<float> &verts1, List<int> &inds1,
                                  const Array<float> &verts2, const Array<int> &inds2)
{
    int i, ioff = (int) verts1.size();
    
    for (i = 0; i < verts2.size(); i++) verts1.push_back(verts2[i]);
    for (i = 0; i < inds2.size(); i++) inds1.push_back(inds2[i] + ioff);
}

void VertexFactory::MergeVertices(const Array<float> &verts1, const Array<int> &inds1,
                          const Array<float> &verts2, const Array<int> &inds2,
                          Array<float> &out_verts, Array<int> &out_inds) 
{
    int i, voff = (int) verts1.size(), ioff = (int) verts2.size();
    
    out_verts = Array<float>(verts1.size() + verts2.size());
    out_inds  = Array<int>( inds1.size() +  inds2.size());
    
    for (i = 0; i < verts1.size(); i++) out_verts[i] = verts1[i];
    for (i = 0; i < inds2.size();  i++) out_inds[i]  = inds1[i];
    
    for (i = 0; i < verts2.size(); i++) out_verts[i + voff] = verts2[i];
    for (i = 0; i < inds2.size();  i++) out_inds[i + ioff] = inds2[i] + voff;
}


void VertexFactory::CreatePlane(Array<float> &vertices, Array<int> &indices, 
                                Vector3 o, Quaternion r, float w, float l, int dw, int dl, int mode)
{
    int ix, iz;
    int nx = dw + 1; // number of verts in the x-axis.
    int nz = dl + 1; // number of verts in the z-axis.
    
    // TODO: optimize... init vertices, indices once (no push_back)
    
    float x = o.x - (w / 2.0f); // init x-coord of first vertex.
    float y = o.y;
    float z;
    
    // Create vertices.
    for (ix = 0; ix < nx; ix++) // For each vertex.
    {
        // Reset the z-coord. for this row.
        z = o.z - (l / 2.0f);
        
        for (iz = 0; iz < nz; iz++) 
        {
            // Rotate the vertex:
            Vector3 v = Vector3(x, y, z);
            v = v - o; // Bring to 0,0,0
            v = v * r; // rotate
            v = v + o; // shift back to ox,oy,oz
            
            // Add the vertex:
            vertices.push_back(v.x);
            vertices.push_back(v.y);
            vertices.push_back(v.z);
            
            // Shift the z-coord. for the next vertex.
            z += l / dl;
        }
        
        // Shift the x-coord. for the next row of vertices.
        x += w / dw;
    }
    
    // Create indices:
    for (ix = 0; ix < dw; ix++) // For each square.
        for (iz = 0; iz < dl; iz++)
        {
            /*               .---.
             *               |   |
             * (ix, iz) --> (.)--.
             */
            
            // Get indices
            int bl = iz + (ix * nz);       // bottom-left index.
            int br = iz + ((ix+1) * nz);   // bottom-right index.
            int tl = iz+1 + (ix * nz);     // top-left index.
            int tr = iz+1 + ((ix+1) * nz); // top-right index.
            
            switch (mode) 
            {
                case GL_QUADS:
                    // Add a quad:
                    indices.push_back(bl * 3);
                    indices.push_back(tl * 3);
                    indices.push_back(tr * 3);
                    indices.push_back(br * 3);
                    break;
            
                case GL_TRIANGLES:
                default:
                    // Add 2 triangles:
                    indices.push_back(tr * 3);
                    indices.push_back(br * 3);
                    indices.push_back(bl * 3);
                    
                    indices.push_back(tr * 3);
                    indices.push_back(bl * 3);
                    indices.push_back(tl * 3);
                    break;
            }
        }
}

void VertexFactory::CreateCuboid(Array<float> &vertices, Array<int> &indices,
                                 Vector3 o, Quaternion r, Vector3 v, int dw, int dh, int dl, int mode)
{
    List<float> lvertices = List<float>();
    List<int> lindices = List<int>();
    Array<float> planeVerts = Array<float>();
    Array<int> planeInds = Array<int>();
    Vector3 center; // center of the plane
    Quaternion orient; // orientation of the plane
    
    // Make front face:
    center = o + Vector3(0, 0, v.z / 2.0f);
    orient = Quaternion(Vector3( - PI / 2, 0, 0));
    CreatePlane(planeVerts, planeInds, center, orient, v.x, v.y, dw, dh, mode);
    MergeVertices(lvertices, lindices, planeVerts, planeInds);
    planeVerts.clear();
    planeInds.clear();
    
    // Make back face:
    center = o - Vector3(0, 0, v.z / 2.0f);
    orient = Quaternion(Vector3( PI / 2, 0, 0));
    CreatePlane(planeVerts, planeInds, center, orient, v.x, v.y, dw, dh, mode);
    MergeVertices(lvertices, lindices, planeVerts, planeInds);
    planeVerts.clear();
    planeInds.clear();
    
    // Make left face:
    center = o + Vector3(v.x / 2.0f, 0, 0);
    orient = Quaternion(Vector3( 0, 0, PI / 2));
    CreatePlane(planeVerts, planeInds, center, orient, v.y, v.z, dh, dl, mode);
    MergeVertices(lvertices, lindices, planeVerts, planeInds);
    planeVerts.clear();
    planeInds.clear();
    
    // Make right face:
    center = o - Vector3(v.x / 2.0f, 0, 0);
    orient = Quaternion(Vector3( 0, 0, -PI / 2));
    CreatePlane(planeVerts, planeInds, center, orient, v.y, v.z, dh, dl, mode);
    MergeVertices(lvertices, lindices, planeVerts, planeInds);
    planeVerts.clear();
    planeInds.clear();
    
    // Make top face:
    center = o + Vector3(0, v.y / 2.0f, 0);
    orient = Quaternion(Vector3( 0, 0, 0) );
    CreatePlane(planeVerts, planeInds, center, orient, v.x, v.z, dw, dl, mode);
    MergeVertices(lvertices, lindices, planeVerts, planeInds);
    planeVerts.clear();
    planeInds.clear();
    
    // Make bottom face:
    center = o - Vector3(0, v.y / 2.0f, 0);
    orient = Quaternion(Vector3( PI , 0, 0) );
    CreatePlane(planeVerts, planeInds, center, orient, v.x, v.z, dw, dl, mode);
    MergeVertices(lvertices, lindices, planeVerts, planeInds);
    planeVerts.clear();
    planeInds.clear();
    
    // Convert lists into arrays:
    VertexFactory::ToArray(lvertices, vertices);
    VertexFactory::ToArray(lindices, indices);
    
    // Rotate each vertex around the origin o:
    int n = (int) vertices.size();
    for (int i = 0; i < n; i = i + 3)
    {
        Vector3 v = Vector3(vertices[i], vertices[i+1], vertices[i+2]);
        v = v - o;
        v = v * r;
        v = v + o;
        vertices[i]   = v.x;
        vertices[i+1] = v.y;
        vertices[i+2] = v.z;
    }
}

void VertexFactory::CreateColorArray(Array<float> &colors, int len, float r, float g, float b) 
{
    for (int i = 0; i < len; i++) 
    {
        colors.push_back(r);
        colors.push_back(g);
        colors.push_back(b);
    }
}
