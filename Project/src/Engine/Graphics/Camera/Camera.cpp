//
//  Camera.cpp
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "Camera.h"
#include <Engine/Input/Input.h>
#include <Engine/Core/Core.h>

Camera::Camera() {
    fov = 45.0f;
    nearClip = 0.1f;
    farClip = 500.0f;
    freeCam = false;
    
    yaw = pitch = roll = x = y = z = 0.0f;
}

Camera::~Camera() {
    
}

Quaternion Camera::Orientation()
{
    /*Quaternion qpitch = glm::gtx::quaternion::angleAxis(pitch, Vector3(1,0,0));
    Quaternion qyaw   = glm::gtx::quaternion::angleAxis(yaw,   Vector3(0,1,0));
    Quaternion qroll  = glm::gtx::quaternion::angleAxis(roll,  Vector3(0,0,1));
    
    return qpitch * qyaw * qroll;*/
    
    return Quaternion(Vector3(0, yaw, roll));
}

void Camera::SetTranslation(Vector3 t) {
    this->x = t.x;
    this->y = t.y;
    this->z = t.z;
}

void Camera::Translate(Vector3 t, bool relative) {
    this->Translate(t.x, t.y, t.z, relative);
}

void Camera::Translate(float x, float y, float z, bool relative)
{
    if(relative)
    {
        Vector3 t = Vector3(x,y,z) * this->Orientation();
        this->x += t.x;
        this->y += t.y;
        this->z += t.z;
    }
    else
    {
        this->x += x;
        this->y += y;
        this->z += z;
    }
}

Vector3 Camera::Translation() 
{
    return Vector3(x,y,z);
}

Vector3 Camera::Up() 
{
    return Vector3(0, 1, 0) * this->Orientation();
}

void Camera::Update()
{
    if (IsFreeCam()) updateFreeCam();
}

void Camera::updateFreeCam()
{
    Vector3 move = Vector3(0);
    float c = 2.0f * Timing::GameTimeElapsed;
    float r = 3.142f * 0.06f * Timing::GameTimeElapsed;
    
    if(Keyboard::IsPressed('W')) 
        move += Vector3(0, 0, c);
    
    if(Keyboard::IsPressed('S'))
        move -= Vector3(0, 0, c);
    
    if(Keyboard::IsPressed('A')) 
        move += Vector3(c, 0, 0);
    
    if(Keyboard::IsPressed('D'))
        move -= Vector3(c, 0, 0);
    
    if(Mouse::IsPressed(GLFW_MOUSE_BUTTON_3) && Keyboard::IsPressed(GLFW_KEY_LALT)) 
    {
        Vector2 v = Mouse::GetDisplacement();
        this-> yaw   += v.x * r;
        this-> pitch += v.y * r;
    }
    
    else if(Mouse::IsPressed(GLFW_MOUSE_BUTTON_3)) 
    {
        float d = 1.0f * Timing::GameTimeElapsed;
        
        Vector2 v = Mouse::GetDisplacement();
        this->Translate(0, -d * v.y, 0, false);
        
        Quaternion yaw = Quaternion(Vector3(0, this->yaw, 0));
        Vector3 strafe = Vector3(d * v.x, 0, 0) * yaw;
        this->Translate(strafe, false);
    }
    
    this->Translate(move, true);
}

