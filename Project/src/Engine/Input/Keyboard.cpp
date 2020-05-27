//
//  Keyboard.cpp
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "Keyboard.h"

bool Keyboard::keysPressed[KEY_COUNT] = {false};
bool Keyboard::keysClicked[KEY_COUNT] = {false};

void Keyboard::keyCallback(int key, int action)
{
    bool wasPressed = keysPressed[key];
    bool isPressed = (action == GLFW_PRESS);
    keysPressed[key] = isPressed;
    keysClicked[key] = wasPressed && !isPressed;
}

void Keyboard::Update() {
    for (int i=0; i<KEY_COUNT; i++)
        keysClicked[i] = false;
}
