#ifndef EXTERNAL_MESH_DIGGER_H
#define EXTERNAL_MESH_DIGGER_H

#include <platform.h>

typedef struct ExternalMesh
{
	String filename;
	Vector3 position;
	Quaternion rotation;
}
ExternalMesh;

interface ExternalMeshDigger
{
protected:
	Array<ExternalMesh> externalMeshes;

public:
	/**
	 * Add an external mesh file to the array.
	 * @param mesh Any ExternalMesh variable.
	 */
	virtual void AddExternalMesh(ExternalMesh& mesh);

	/**
	 * Add an external mesh file to the array. Creates an instance of ExternalMesh stored
	 * in the array.
	 * @param filename Name of the mesh file.
	 * @param position 3D offset vector of the mesh.
	 * @param rotation Orientation of the mesh.
	 */
	virtual void AddExternalMesh(String filename, Vector3& position, Quaternion& rotation);

	/**
	 * Get all the external meshes.
	 * @param count [output] Number of external meshes in the array. NULL is acceptable,
	 *        in which case no output is provided.
	 * @return An array of External meshes. NULL if count is 0.
	 */
	virtual ExternalMesh* GetExternalMeshes(int* count = NULL);
};

#endif
