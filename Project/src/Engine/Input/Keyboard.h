//
//  Keyboard.h
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#define KEY_COUNT GLFW_KEY_LAST+1

#include <platform.h>
#include <glfw/glfw.h>

class Keyboard
extends Object
{
public:
    static bool IsPressed(int key)  { return keysPressed[key]; }
    static bool IsClicked(int key)  { return keysClicked[key]; }
    static bool IsReleased(int key) { return !keysPressed[key]; }
    
	// glfw callbacks
    static void keyCallback(int key, int action);
    
    static void Update();
    
private:
	/* Keyboard Handling variables: */
	static bool keysPressed[KEY_COUNT];
    static bool keysClicked[KEY_COUNT];
};

#endif
