//
//  Mesh.cpp
//  Dissert
//
//  Created by Olivier Legat on 07/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "Mesh.h"
#include "vertexTexcoords.h"
#include <Generator/MazeMesh/MazeMesh.h>
#include <Engine/Graphics/Texture/Texture.h>
#include <Engine/Graphics/Material/Material.h>
#include <Engine/Graphics/Mesh/OBJLoader/ObjLoader.h>

Mesh::Mesh()
{
    this->displayMode = MESH_SOLID;
    this->twoSided = false;
    this->primitiveType = GL_TRIANGLES;
    this->material = new Material();
}

Mesh::~Mesh()
{
    vertices.clear();
    indices.clear();
    color.clear();
    texcoords.clear();
    
    material->DeleteTextures();
    delete material;
}

void Mesh::SetVertices(const float* vertices, const int count) 
{
    this->vertices.clear();
    this->vertices = Array<float>(count, 0);
    
    for (int i = 0; i < count; i++) {
        this->vertices[i] = vertices[i];
    }
}

void Mesh::SetIndices(const int* indices, const int count)
{
    this->indices.clear();
    this->indices = Array<int>(count, 0);
    
    for (int i = 0; i < count; i++) {
        this->indices[i] = indices[i];
    }
}

void Mesh::SetColors(const float* colors, const int count)
{
    this->color.clear();
    this->color = Array<float>(count, 0);
    
    for (int i = 0; i < count; i++) {
        this->color[i] = colors[i];
    }
}

void Mesh::SetTexCoords(const float* texcoords, const int count)
{
    this->texcoords.clear();
    this->texcoords = Array<float>(count, 0);
    
    for (int i = 0; i < count; i++) {
        this->texcoords[i] = texcoords[i] ;
    }
}

float* Mesh::GetVertices(int* n) const {
    *n = (int) vertices.size();
    return (float*) &vertices[0];
}
int* Mesh::GetIndices(int* n) const {
    *n = (int) indices.size();
    return (int*) &indices[0];
}
float* Mesh::GetColors(int* n) const {
    *n = (int) color.size();
    return (float*) &color[0];
}
float* Mesh::GetTexCoords(int* n) const {
    *n = (int) texcoords.size();
    return (float*) &texcoords[0];
}

Mesh* Mesh::CreateFromMazeMesh(MazeMesh* maze)
{
    Mesh* mesh = new Mesh();
    
    int nverts, ninds, ncols, ntex;
    float* vertices; int* indices; float* colors; float* texcoords;
    
    vertices = maze->GetVertices(&nverts);
    indices  = maze->GetIndices(&ninds);
    colors   = maze->GetColors(&ncols);
    texcoords= maze->GetTexCoords(&ntex);
    
    mesh->SetVertices(vertices, nverts);
    mesh->SetIndices(indices, ninds);
    mesh->SetColors(colors, ncols);
    mesh->SetTexCoords(texcoords, ntex);
    
    return mesh;
}

void Mesh::RotateVertices(Quaternion q)
{
	assert (vertices.size() % 3 == 0);

	int end = (int) vertices.size() / 3;
	for (int i = 0; i < end; i++)
	{
		int i3 = i*3;
		Vector3 v;

		// Copy vertex data into GLM vector3
		v.x = vertices[i3 + 0];
		v.y = vertices[i3 + 1];
		v.z = vertices[i3 + 2];

		// Rotate vertex using GLM
		v = v * q;

		// Copy vertex data back into the array.
		vertices[i3 + 0] = v.x;
		vertices[i3 + 1] = v.y;
		vertices[i3 + 2] = v.z;
	}
}

void Mesh::TranslateVertices(Vector3 t)
{
	assert (vertices.size() % 3 == 0);

	int end = (int) vertices.size() / 3;
	for (int i = 0; i < end; i++)
	{
		int i3 = i*3;
		Vector3 v;

		// Copy vertex data into GLM vector3
		v.x = vertices[i3 + 0];
		v.y = vertices[i3 + 1];
		v.z = vertices[i3 + 2];

		// Rotate vertex using GLM
		v = v + t;

		// Copy vertex data back into the array.
		vertices[i3 + 0] = v.x;
		vertices[i3 + 1] = v.y;
		vertices[i3 + 2] = v.z;
	}
}

Mesh* Mesh::CreateFromOBJFile(String filename)
{
	int i, j, k;

	ObjLoader loader;
	loader.load(filename.c_str());

	Mesh* createdMesh = new Mesh();

	/**
	 * OBJ files re-use data for vertices that have the same position / tex-coords.
	 * The engine doesn't do that sadly, so we need to duplicate the vertices.
	 * In this section we first set all indices whilst constructively building the
	 * vertices. The vertices will be copied into the Mesh later on.
	 */
	Array<VertexTexcoord> allVerts;
	createdMesh->indices = Array<int>(loader.faceCount * 3);
	for ( i = 0; i < loader.faceCount; i++)
	{
		if (loader.faceList[i]->vertex_count != 3) 
            printf("Only triangle faces are supported in OBJ. Face ignored.");
		
		else for ( j = 0; j < 3; j++ )
		{
			// Get vertex data j from the face.
			int obj_vertex_index = loader.faceList[i]->vertex_index[j];
			obj_vector* obj_vertex = loader.vertexList[obj_vertex_index];

			// Get texture data j from the face.
			int obj_texture_index = loader.faceList[i]->texture_index[j];
			obj_vector* obj_texture = loader.textureList[obj_texture_index];

			// Extract OBJ data:
			VertexTexcoord vt;
			vt.x = obj_vertex->e[0];
			vt.y = obj_vertex->e[1];
			vt.z = obj_vertex->e[2];
			vt.u = obj_texture->e[0];
			vt.v = obj_texture->e[1];

			// Find the index of this vertex. If it doesn't exist, create it.
			bool exists = false;
			for ( k = 0 ; k < allVerts.size(); k++)
			{
				if (allVerts[k] == vt) 
				{
					exists = true;
					break;
				}
			}
			if (!exists) allVerts.push_back(vt);

			// Multiply index by 3 (because 3 components to each vertex; x,y,z).
			// That's how it works in this engine.
			createdMesh->indices[ i*3 + j ] = k * 3;
		}
	}

	/**
	 * Now we have all the data in allVerts. We need only to copy this
	 * into the Mesh.
	 */
	createdMesh->vertices = Array<float>(allVerts.size() * 3);
	createdMesh->texcoords = Array<float>(allVerts.size() * 2);
	for ( i = j = k = 0 ; k < allVerts.size(); k++)
	{
		createdMesh->vertices[i++] = allVerts[k].x;
		createdMesh->vertices[i++] = allVerts[k].y;
		createdMesh->vertices[i++] = allVerts[k].z;

		createdMesh->texcoords[j++] = allVerts[k].u;
		createdMesh->texcoords[j++] = allVerts[k].v;
	}
	allVerts.clear(); // we don't need this anymore.

	/**
	 * Assign the Material to the Mesh.
	 */
	if (loader.materialCount > 0)
	{
		// Create Texture.
		File diffuseFile (loader.materialList[0]->texture_filename);
		Texture* createdTexture = Texture::CreateFromFile(diffuseFile);

		// Create Material.
		Material* createdMaterial = new Material();
		createdMaterial->SetDiffuse(createdTexture);
		createdMesh->SetMaterial(createdMaterial);
		createdMesh->SetDisplayMode(MESH_TEXTURED);
		createdMesh->SetTwoSided(true);
	}

	return createdMesh;
}
