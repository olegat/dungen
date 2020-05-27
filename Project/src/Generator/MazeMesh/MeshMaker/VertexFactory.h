//
//  VertexFactor.h
//  Dissert
//
//  Created by Olivier Legat on 10/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef VERTEX_FACTOR_H_
#define VERTEX_FACTOR_H_

#include <Object.h>

class VertexFactory : Object 
{
public:
    
    static void ToArray(List<float> &l, Array<float> &a);
    static void ToArray(List<int> &l, Array<int> &a);
    
    /**
     * Merges two arrays of verts/inds by pouring content from one into the
     * other
     *
     * @param verts1 [in/output] Vertex list [x0, y0, z0, x1, y1, z1, ...]
     * @param inds1  [in/output] Index list [a0, b0, c0, a1, b1, c1, ...]
     * @param verts2 Vertex array data to append to verts1.
     * @param inds2 Index array data to append to inds1.
     */
    static void MergeVertices(List<float> &verts1, List<int> &inds1,
                              const Array<float> &verts2, const Array<int> &inds2);
    
    /**
     * Merges two arrays of verts/inds into a single array. Doesn't
     * change original content.
     *
     * @param verts1 Vertex array [x0, y0, z0, x1, y1, z1, ...]
     * @param inds1 Index array [a0, b0, c0, a1, b1, c1, ...]
     * @param verts2 Vertex array [x0, y0, z0, x1, y1, z1, ...]
     * @param inds2 Index array [a0, b0, c0, a1, b1, c1, ...]
     * @param out_verts [output] verts1 and verts2 merged.
     * @param out_inds [output] inds1 and inds2 merged. Offsets indices
     *                 to insure that the indices match the correct vertices.
     */
    static void MergeVertices(const Array<float> &verts1, const Array<int> &inds1,
                              const Array<float> &verts2, const Array<int> &inds2,
                              Array<float> &out_verts, Array<int> &out_inds);
    
    /**
     * Create the vertices and indices of the horizontal plane:
     *
     * @param vertices [output] Vertices created. Initially empty.
     * @param indices [output] Indices created. Initially empty.
     * @param o origin of the mesh (center).
     * @param r rotation of the plane.
     * @param w width of the grid.
     * @param l length of the grid.
     * @param dw number of divisions along the x-axis. w >= 1
     * @param dl number of divisions along the z-axis. h >= 1
     * @param mode GLenum. Either GL_TRIANGLE or GL_QUADS (GL_LINES not supported yet). If
     *             mode doesn't match a valid option, then GL_TRIANGLE is defaulted.
     */
    static void CreatePlane(Array<float> &vertices, Array<int> &indices, 
                            Vector3 o, Quaternion r, float w, float l, int dw, int dl, int mode);
    
    /**
     * Create the vertices and indices of the horizontal plane:
     *
     * @param vertices [output] Vertices created. Initially empty.
     * @param indices [output] Indices create. Initially empty.
     * @param o origin of the mesh (center).
     * @param r rotation of the plane.
     * @param v volume of on the x,y,z (width, length, height) axes.
     * @param dw number of divisions along the x-axis. dw >= 1
     * @param dl number of divisions along the y-axis. dl >= 1
     * @param dh number of divisions along the z-axis. dh >= 1
     * @param mode GLenum. Either GL_TRIANGLE or GL_QUADS (GL_LINES not supported yet). If
     *             mode doesn't match a valid option, then GL_TRIANGLE is defaulted.
     */
    static void CreateCuboid(Array<float> &vertices, Array<int> &indices,
                             Vector3 o, Quaternion r, Vector3 v, int dw, int dh, int dl, int mode);
    
    /**
     * Adds colors into an array.
     *
     * @param color [output] Colors created. Initially empty. Length at the end is len * 3.
     * @param len Number of colors to add.
     * @param r Red channel.
     * @param g Green channel.
     * @param b Blue channel.
     */
    static void CreateColorArray(Array<float> &colors, int len, float r, float g, float b);
    
private:
    VertexFactory();
    ~VertexFactory();
};

#endif
