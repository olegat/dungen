//
//  Game1Logic.h
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef GAME1_LOGIC_H_
#define GAME1_LOGIC_H_

#include <Engine/Engine.h>

class Game1Logic
extends GameLogic 
{
public:
    virtual int Init();
    virtual bool Update();
    virtual int End();
    
private:
    Camera* camera;
    SceneSpace* scene;
    SceneObject* theCube;
    SceneDynamic* player;
    bool playing;
    
    Mesh* mesh1;
    Mesh* mesh2;
    Mesh* mesh3;
    MeshDisplayMode display;
    
    void setUpCube();
    void setUpMaze();
    void setUpPlayer();
    
    void UpdatePlaying();
    void UpdateViewing();
    
    void mazeMeshToEngineMesh(MazeMesh* mazeMesh, Mesh** meshRef, GLenum primitiveType, const String& diffuse);
};

#endif
