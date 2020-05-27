//
//  MazeCollider.h
//  Dissert
//
//  Created by Olivier Legat on 22/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef MAZE_COLLIDER_H_
#define MAZE_COLLIDER_H_

#include <platform.h>

class MazeCollider : public Object
{
protected:
    MazeCollider();
    
public:
    ~MazeCollider();
    
    virtual float GetMinX()const =0;
    virtual float GetMinY()const =0;
    virtual float GetMinZ()const =0;
    virtual float GetMaxX()const =0;
    virtual float GetMaxY()const =0;
    virtual float GetMaxZ()const =0;
    
    /**
     * @param maxX [output] set to GetMaxX().
     * @param maxY [output] set to GetMaxY().
     * @param maxZ [output] set to GetMaxZ().
     * @param minX [output] set to GetMinX().
     * @param minY [output] set to GetMinY().
     * @param minZ [output] set to GetMinZ().
     */
    void GetAllMinMax(float* minX, float* minY, float* minZ,
                      float* maxX, float* maxY, float* maxZ) const;
};

class MazeColliderAABB : public MazeCollider
{
public:
    MazeColliderAABB();
    ~MazeColliderAABB();
    
    void    GetVolume(float* x, float* y, float* z);
    Vector3 GetVolume() const { return vol; }
    float GetWidth()  const { return vol.x; }
    float GetLength() const { return vol.z; }
    float GetHeight() const { return vol.y; }
    
    void    GetTranslation(float* x, float* y, float* z);
    Vector3 GetTranslation() const { return trans; }
    float GetX() const { return trans.x; }
    float GetY() const { return trans.y; }
    float GetZ() const { return trans.z; }
    
    void SetVolume(Vector3 v) { this->vol = v; }
    void SetWidth (float x) { this->vol.x = x; }
    void SetLength(float z) { this->vol.z = z; }
    void SetHeight(float y) { this->vol.y = y; }
    
    void SetTranslation(Vector3 t) { this->trans = t; }
    void SetX(float x) { this->trans.x = x; }
    void SetY(float y) { this->trans.y = y; }
    void SetZ(float z) { this->trans.z = z; }
    
    virtual float GetMinX()const {return trans.x - vol.x / 2.0f;}
    virtual float GetMinY()const {return trans.y - vol.y / 2.0f;}
    virtual float GetMinZ()const {return trans.z - vol.z / 2.0f;}
    virtual float GetMaxX()const {return trans.x + vol.x / 2.0f;}
    virtual float GetMaxY()const {return trans.y + vol.y / 2.0f;}
    virtual float GetMaxZ()const {return trans.z + vol.z / 2.0f;}
    
    Vector3 GetMinCorner() const;
    Vector3 GetMaxCorner() const;
    
private:
    Vector3 vol;
    Vector3 trans;
};

#endif
