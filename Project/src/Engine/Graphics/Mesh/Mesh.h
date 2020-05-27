//
//  Mesh.h
//  Dissert
//
//  Created by Olivier Legat on 07/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef MESH_H_
#define MESH_H_

#include <platform.h>
#include <Engine/Graphics/Material/Material.h>

class MazeMesh;

enum MeshDisplayMode
{
    MESH_SOLID,
    MESH_WIREFRAME,
    MESH_EDGED,
    MESH_TEXTURED
};

class objLoader;
class Mesh
extends Object 
{
public:
    // Create a new mesh. Creates an instance of Material.
    Mesh();
    
    // Delete this mesh. Deletes textures in this->material.
    ~Mesh();
    
    /**
     * @param vertices An array of floats: [x0, y0, z0, x1, y1, z1, ..]
     * @param count Number of vertices * 3.
     */
    void SetVertices(const float* vertices, const int count);
    /**
     * @param indices An array of int: [a0, b0, c0, a1, b1, c1, ..]
     * @param count Number of triangles * 3.
     */
    void SetIndices(const int* indices, const int count);
    /**
     * @param vertices An array of floats: [r0, g0, b0, r1, g1, b1, ..]
     * @param count Number of colors * 3.
     */
    void SetColors(const float* colors, const int count);
    /**
     * @param vertices An array of floats: [u0, v0, u1, v1, ..]
     * @param count Number of vertices * 2.
     */
    void SetTexCoords(const float* texcoords, const int count);
    
    /**
     * @param n [output] Number of vertices * 3 (Length of returned array).
     * @return An array of floats: [x0, y0, z0, x1, y1, z1, ..]
     */
    float* GetVertices(int* n) const;
    /**
     * @param n [output] Number of triangles * 3 (Length of returned array).
     * @return An array of int: [a0, b0, c0, a1, b1, c1, ..]
     */
    int* GetIndices(int* n) const;
    /**
     * @param n [output] Number of colors * 3 (Length of returned array).
     * @return An array of floats: [r0, g0, b0, r1, g1, b1, ..]
     */
    float* GetColors(int* n) const;
    /**
     * @param n [output] Number of vertices * 3 (Length of returned array).
     * @return An array of floats: [u0, v0, u1, v1, ..]
     */
    float* GetTexCoords(int* n) const;
    
    Material* GetMaterial() const {return material;}
	void SetMaterial(Material* mat) {delete material; material = mat;}
    
    /**
     * deprecated. Use Set/GetDisplayMode
     */
    bool IsWireFramed() const {return displayMode == MESH_WIREFRAME;}
    void SetWireFramed(bool wire) {displayMode = wire ? MESH_WIREFRAME : MESH_SOLID;}
    
    MeshDisplayMode GetDisplayMode() const {return displayMode;}
    void SetDisplayMode(MeshDisplayMode mode) {displayMode = mode;}
    
    bool IsTwoSided() const {return twoSided;}
    void SetTwoSided(bool two) {twoSided = two;}
    
    /**
     * @return Primitive type. See mode param in glBegin(int);
     */
    int GetPrimitiveType() const {return primitiveType;}
    /**
     * @param glmode See mode param in glBegin(int).
     */
    void SetPrimitiveType(int glmode) {this->primitiveType = glmode;}

	void RotateVertices(Quaternion q);
	void TranslateVertices(Vector3 v);
    
    static Mesh* CreateFromMazeMesh(MazeMesh* maze);
	static Mesh* CreateFromOBJFile(String filename);

private:
    Array<float> vertices;
    Array<int> indices;
    Array<float> color;
    Array<float> texcoords;
    
    int primitiveType;
    MeshDisplayMode displayMode;
    bool twoSided;
    
    Material* material;
};

#endif
