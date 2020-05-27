#include "ExternalMeshDigger.h"	

void ExternalMeshDigger::AddExternalMesh(ExternalMesh& mesh)
{
	externalMeshes.push_back(mesh);
}
	
void ExternalMeshDigger::AddExternalMesh(String filename, Vector3& position, Quaternion& rotation)
{
	ExternalMesh mesh;
	mesh.filename = filename;
	mesh.position = position;
	mesh.rotation = rotation;
	externalMeshes.push_back(mesh);
}

ExternalMesh* ExternalMeshDigger::GetExternalMeshes(int* count)
{
	int c = (int)externalMeshes.size();

	if (count != NULL) *count = c;

	return c == 0 ? NULL : &externalMeshes[0];
}
