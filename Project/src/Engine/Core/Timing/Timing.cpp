//
//  Timing.cpp
//  Dissert
//
//  Created by Olivier Legat on 08/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include <platform.h>
#include <glfw/glfw.h>

#include "Timing.h"

float Timing::GameCurrentTime = 0.0f;
float Timing::GameTimeElapsed = 0.0f;

void Timing::Init() {
    Timing::GameCurrentTime = (float)glfwGetTime();
    Timing::GameTimeElapsed = 0.0;
}

void Timing::Update() {
    float now = (float)glfwGetTime();
    float dt = now - Timing::GameCurrentTime;
    Timing::GameCurrentTime = now;
    Timing::GameTimeElapsed = dt;
}
