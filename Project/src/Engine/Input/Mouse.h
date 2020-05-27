//
//  Mouse.h
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef MOUSE_H_
#define MOUSE_H_

#define MOUSE_BUTTON_COUNT GLFW_MOUSE_BUTTON_LAST+1

#include <platform.h>
#include <glfw/glfw.h>

class Mouse
extends Object
{    
public:
    static bool IsPressed(int button)  { return buttonsPressed[button]; }
    static bool IsClicked(int button)  { return buttonsClicked[button]; }
    static bool IsReleased(int button) { return !buttonsPressed[button]; }
    
    static Vector2 GetPosition() { return mousePosition; }
    static Vector2 GetDisplacement() { return mousePosition - oldMousePosition; }
    
	// glfw callbacks
    static void mouseCallback(int x, int y);
    static void buttonCallback (int button, int action);
    
    static void Update();
    
private:
    
	/* Mouse Button Handling variables: */
	static bool buttonsPressed[MOUSE_BUTTON_COUNT];
    static bool buttonsClicked[MOUSE_BUTTON_COUNT];
    
    static Vector2 mousePosition, oldMousePosition;
};

#endif
