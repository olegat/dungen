//
//  GraphicsContext.cpp
//  Dissert
//
//  Created by Olivier Legat on 08/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include <glfw/glfw.h>
#include "GraphicsContext.h"


/**
 * Contructor
 */
GraphicsContext::GraphicsContext()
{
    glfwInit();
    fullscreen = false;

    GLFWvidmode vidModes[100];
    int nmodes = glfwGetVideoModes(vidModes, 100);
    
    for (int i=0; i<nmodes; i++)
    {
        this->displayModes.push_back(vidModes[i]);
    }
    
    glfwGetDesktopMode(&desktopMode);
    
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
}

/**
 * Contructor
 */
GraphicsContext::GraphicsContext(GLFWvidmode& startingMode)
{
    glfwInit();
	fullscreen = false;
    
    GLFWvidmode vidModes[100];
    int nmodes = glfwGetVideoModes(vidModes, 100);
    
    for (int i=0; i<nmodes; i++)
    {
        this->displayModes.push_back(vidModes[i]);
    }
    
    glfwGetDesktopMode(&desktopMode);
    
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
    
    SetDisplayMode(startingMode.Width, startingMode.Height,
                   startingMode.RedBits, startingMode.GreenBits, startingMode.BlueBits);
}

/**
 * Destructor
 */
GraphicsContext::~GraphicsContext() {
    
}

bool GraphicsContext::SetDisplayMode(int w, int h, int r, int g, int b)
{
    for (size_t i = 0; i < this->displayModes.size(); i++)
    {
        if (displayModes[i].Width == w &&
            displayModes[i].Height == h &&
            displayModes[i].RedBits == r &&
            displayModes[i].GreenBits == g &&
            displayModes[i].BlueBits == b)
        {
            currentMode  = displayModes[i];
            return true;
        }
    }
    
    /* else */ return false;
}

void GraphicsContext::Start() {
    this->Start(this->currentMode);
}

void GraphicsContext::Start(GLFWvidmode& mode) 
{    
    int screenMode = fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW;
    
    glfwSetWindowTitle("These are words");
    glfwOpenWindow(mode.Width, mode.Height, mode.RedBits, mode.GreenBits, mode.BlueBits, 0, 24, 8, screenMode);
}

void GraphicsContext::Update() {
    glfwSwapBuffers();
    glfwSleep(0.01f);
}

bool GraphicsContext::IsWindowOpen() {
    return glfwGetWindowParam(GLFW_OPENED) ? true : false ;
}

void GraphicsContext::PrintAllModes(Ostream &out)
{
    for (size_t i = 0; i < this->displayModes.size(); i++)
    {
        out << displayModes[i].Width << " "
        << displayModes[i].Height << " "
        << displayModes[i].RedBits << " "
        << displayModes[i].GreenBits << " "
        << displayModes[i].BlueBits << std::endl;
    }
}

