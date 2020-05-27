#ifndef VERTEX_TEXCOORDS_STRUCT
#define VERTEX_TEXCOORDS_STRUCT


typedef struct VertexTexcoord
{
	float x;
	float y;
	float z;
	float u;
	float v;
} VertexTexcoord;
bool operator==(VertexTexcoord vt1, VertexTexcoord vt2);

bool operator==(VertexTexcoord vt1, VertexTexcoord vt2)
{
	return (
		vt1.x == vt2.x &&
		vt1.y == vt2.y &&
		vt1.z == vt2.z &&
		vt1.u == vt2.u &&
		vt1.v == vt2.v );
}

#endif
