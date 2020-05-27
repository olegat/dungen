//
//  Mouse.cpp
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "Mouse.h"

bool Mouse::buttonsPressed[MOUSE_BUTTON_COUNT] = {false};
bool Mouse::buttonsClicked[MOUSE_BUTTON_COUNT] = {false};

Vector2 Mouse::mousePosition = Vector2(0);
Vector2 Mouse::oldMousePosition = Vector2(0);

void Mouse::buttonCallback(int key, int action) {
    bool wasPressed = buttonsPressed[key];
    bool isPressed = (action == GLFW_PRESS);
    buttonsPressed[key] = isPressed;
    buttonsClicked[key] = wasPressed && !isPressed;
}

void Mouse::mouseCallback(int x, int y) {
    mousePosition = Vector2(x, y);
}

void Mouse::Update() {
    oldMousePosition = mousePosition;
    
    for(int i=0; i<MOUSE_BUTTON_COUNT; i++)
        buttonsClicked[i] = false;
}
