//
//  Input.cpp
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "Input.h"

void Input::Init() {
    remapInputHandlers();
}

void Input::Destroy() {
    
}

void Input::remapInputHandlers() {
    glfwEnable(GLFW_MOUSE_CURSOR);
    
    glfwSetKeyCallback(Keyboard::keyCallback);
    glfwSetMouseButtonCallback(Mouse::buttonCallback);
    glfwSetMousePosCallback(Mouse::mouseCallback);
}
