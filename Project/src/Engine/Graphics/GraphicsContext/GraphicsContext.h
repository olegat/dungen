//
//  GraphicsContext.h
//  Dissert
//
//  Created by Olivier Legat on 08/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef GRAPHICS_CONTEXT_H_
#define GRAPHICS_CONTEXT_H_

#include <platform.h>
#include <glfw/glfw.h>

class Object;
class DisplayMode;

class GraphicsContext
extends Object
{
public:
    GraphicsContext();
    GraphicsContext(GLFWvidmode &startingMode);
    ~GraphicsContext();
    
    void Start();
    void Start(GLFWvidmode& mode);
    
    bool SetDisplayMode(int w, int h, int r, int g, int b);
    GLFWvidmode GetDisplayMode() { return this->currentMode; }
    
    void SetFullscreen(const bool full) {this->fullscreen = full;}
    bool IsFullscreen() const {return this->fullscreen;}
    
    void Update();
    bool IsWindowOpen();
    
    void PrintAllModes(Ostream &out);
    
private:
    bool fullscreen;
    GLFWvidmode desktopMode;
    GLFWvidmode currentMode;
    Array<GLFWvidmode> displayModes;
};

#endif
