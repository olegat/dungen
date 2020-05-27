//
//  EngineApplication.h
//  Dissert
//
//  Created by Olivier Legat on 08/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef ENGINE_APPLICATION_H_
#define ENGINE_APPLICATION_H_

#include "GameLogic.h"
#include <glfw/glfw.h>

class Object;
class GraphicsContext;
class Renderer;
class SceneSpace;

class EngineApplication
extends Object
{
public:
    EngineApplication(GameLogic* gameLogic);
    ~EngineApplication();
    
    // Stuff done before the game loop
    int Init(GLFWvidmode &mode);
    
    // Run app. Insure to run Init() first.
    int Run();
    
    GraphicsContext* GetGraphicsContext() const {return this->graphicsContext;}
    Renderer* GetRenderer() const {return this->renderer;}
    SceneSpace* GetSceneSpace() const {return this->scene;}
    
private:
    GraphicsContext* graphicsContext;
    Renderer* renderer;
    SceneSpace* scene;
    GameLogic* gameLogic;
    
    // Stuff done after the game loop
    int End();
    
protected:
    // Stuff done in the game loop.
    virtual bool Update();
};

#endif
