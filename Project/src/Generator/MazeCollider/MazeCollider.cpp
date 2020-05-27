//
//  MazeCollider.cpp
//  Dissert
//
//  Created by Olivier Legat on 22/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "MazeCollider.h"

MazeCollider::MazeCollider() {}
MazeCollider::~MazeCollider() {}


void MazeCollider::GetAllMinMax(float* minX, float* minY, float* minZ,
                                float* maxX, float* maxY, float* maxZ) const
{
    *maxX = GetMaxX();
    *maxY = GetMaxY();
    *maxZ = GetMaxZ();
    *minX = GetMinX();
    *minY = GetMinY();
    *minZ = GetMinZ();
}

MazeColliderAABB::MazeColliderAABB()
{
    this->trans = Vector3 (0);
    this->vol = Vector3 (0);
}

MazeColliderAABB::~MazeColliderAABB()
{
    
}

void MazeColliderAABB::GetVolume(float* x, float* y, float* z)
{
    *x = vol.x;
    *y = vol.y;
    *z = vol.z;
}

void MazeColliderAABB::GetTranslation(float *x, float *y, float *z)
{
    *x = trans.x;
    *y = trans.y;
    *z = trans.z;
}

Vector3 MazeColliderAABB::GetMinCorner() const {
    return Vector3(GetMinX(), GetMinY(), GetMinZ());
}
Vector3 MazeColliderAABB::GetMaxCorner() const {
    return Vector3(GetMaxX(), GetMaxY(), GetMaxZ());
}
