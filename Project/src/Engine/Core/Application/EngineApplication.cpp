//
//  EngineApplication.cpp
//  Dissert
//
//  Created by Olivier Legat on 08/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include <glfw/glfw.h>

#include <Engine/Core/File/File.h>
#include <Engine/Core/Timing/Timing.h>
#include <Engine/Graphics/Camera/Camera.h>
#include <Engine/Graphics/Renderer/Renderer.h>
#include <Engine/Graphics/Renderer/RenderPipeline.h>
#include <Engine/Graphics/GraphicsContext/GraphicsContext.h>
#include <Engine/Input/Input.h>
#include <Engine/Scene/SceneSpace.h>

#include "EngineApplication.h"

EngineApplication::EngineApplication(GameLogic* gameLogic) {
    this->gameLogic = gameLogic;
    this->gameLogic->engine = this;
    
    // Initialize file system:
    File::InitFilesystem();
}

EngineApplication::~EngineApplication() {
    
}

int EngineApplication::Run() 
{    
    while ( Update() );
    
    return End();
}

int EngineApplication::Init(GLFWvidmode& mode) 
{    
    // Initialize graphics context:
    this->graphicsContext = new GraphicsContext(mode);
    this->graphicsContext->Start();
    
    // Initialize input:
    Input::Init();
    
    // Initialize the scene:
    this->scene = new SceneSpace();
    
    // Initialize the renderer-scene pipeline:
    RenderPipeline* pipe = new RenderPipeline(this->scene);
    
    // Initialize renderer:
    this->renderer = new Renderer(pipe);
    
    Timing::Init();
    
    return gameLogic->Init();
}

int EngineApplication::End() 
{
    delete graphicsContext;
    delete renderer;
    
    Input::Destroy();
    
    return gameLogic->End();
}

bool EngineApplication::Update()
{
    // Update the Engine Logic:
    Timing::Update();
    scene->Update();
    
    // Update the Game Logic:
    bool stillGoing = gameLogic->Update();
    
    // Draw the Game:
    Input::Update();
    renderer->Render();
    graphicsContext->Update();
    
    return graphicsContext->IsWindowOpen() && stillGoing;
}
