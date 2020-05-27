//
//  Game1App.h
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef GAME1_APP_H_
#define GAME1_APP_H_

#include <Engine/Engine.h>

class Game1App
extends Object
{
public:
    Game1App();
    
    int Run(int argc, const char** argv);
    
    // Arguments:
    
    static bool ShowGrid;
    static bool ShowBVH;
    static bool LogSearchPath;
    static String FloorDiffuseFilename;
    static String CeilingDiffuseFilename;
    static String WallDiffuseFilename;
    static bool UseRandomSeed;
    static unsigned long Seed;
    static int MazeWidth;
    static int MazeLength;
    static String ProfileFilename;
    static int GfxWidth, GfxHeight, GfxRedBits, GfxBlueBits, GfxGreenBits;
    
private:
    EngineApplication* app;
    GameLogic* logic;
    
    void setDefaults();
    bool parseArgs(int argc, const char** argv);
    void printUsage();
};

#endif
