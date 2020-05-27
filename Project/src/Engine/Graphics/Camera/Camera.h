//
//  Camera.h
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef CAMERA_H_
#define CAMERA_H_

#include <platform.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Object;
class Camera
extends Object
{
public:
    Camera();
    ~Camera();
    
    // Projection:
    float fov, nearClip, farClip;
    
    // Orientation:
    float yaw;
	float pitch;
	float roll;
    Quaternion Orientation();
    
    // Translation:
    float x, y, z;
    void SetTranslation(Vector3 t);
    void Translate(float x, float y, float z, bool relative);
    void Translate(Vector3 t, bool relative);
    Vector3 Translation();
    Vector3 Up();
    
    void Update();
    
    void SetFreeCam(bool free) {freeCam = free;}
    bool IsFreeCam() const {return freeCam;}
    
private:
    bool freeCam;
    void updateFreeCam();
};

#endif
