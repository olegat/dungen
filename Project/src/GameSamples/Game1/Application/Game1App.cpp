//
//  Game1App.cpp
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "Game1App.h"
#include "Game1Logic.h"

bool Game1App::ShowGrid;
bool Game1App::ShowBVH;
bool Game1App::LogSearchPath;
String Game1App::FloorDiffuseFilename;
String Game1App::WallDiffuseFilename;
String Game1App::CeilingDiffuseFilename;
bool Game1App::UseRandomSeed;
unsigned long Game1App::Seed;
int Game1App::MazeWidth;
int Game1App::MazeLength;
String Game1App::ProfileFilename;
int Game1App::GfxWidth;
int Game1App::GfxHeight;
int Game1App::GfxRedBits;
int Game1App::GfxGreenBits;
int Game1App::GfxBlueBits;

Game1App::Game1App()
{    
    this->logic = new Game1Logic();
    this->app = new EngineApplication(logic);
        
    setDefaults();
}

void Game1App::setDefaults()
{
    ShowGrid               = false;
    ShowBVH                = false;
    LogSearchPath          = false;
    FloorDiffuseFilename   = "test2.png";
    CeilingDiffuseFilename = "test2.png";
    WallDiffuseFilename    = "test1.png";
    UseRandomSeed          = false;
    Seed                   = 0;
    MazeWidth              = 25;
    MazeLength             = 25;
    ProfileFilename        = "default.dungenprofile";
    GfxWidth               = 0;
    GfxHeight              = 0;
    GfxRedBits             = 0;
    GfxGreenBits           = 0;
    GfxBlueBits            = 0;
}

int Game1App::Run(int argc, const char** argv) 
{    
    // Check if help is asked:
    if ( ArgParser::getArgIndex("--help", "-?", argc, argv) != -1 )
    {
        printUsage();
        return 0;
    }
    
    // Check if gfx mode are requested:
    int i;
    if ((i = ArgParser::getArgIndex("--gfx-modes", NULL, argc, argv)) != -1)
    {
        GLFWvidmode mode;
        GraphicsContext* gfx = new GraphicsContext(mode);
        
        // Print to file
        if (ArgParser::hasValue(i, argc, argv))
        {
            Ofstream out (argv[i]);
            gfx->PrintAllModes(out);
            out.close();
            
            delete gfx;
            return 0;
        }
        // Print to stdout
        else
        {
            gfx->PrintAllModes(std::cout);
            
            delete gfx;
            return 0;
        }
    }
    
    // Run app normally:
    if (parseArgs(argc, argv))
    {
        GLFWvidmode vidmod;
        vidmod.Width = GfxWidth;
        vidmod.Height = GfxHeight;
        vidmod.RedBits = GfxRedBits;
        vidmod.GreenBits = GfxGreenBits;
        vidmod.BlueBits = GfxBlueBits;
        
        // Initialize app.
        int r;
        if( (r = app->Init(vidmod)) ) return r;
        
        return app->Run();
    }
    
    // If arguments aren't parsed correctly (user-input error).
    else
    {
        printUsage();
        return -1;
    }
}

/**
 * Check if a condition for an argument is met. If the condition is
 * not met, then the function calling this macro returns false.
 *
 * @param b [boolean]  An condition.
 * @param err [string] Error message if condition isn't met.
 */
#define check_parse(b, err) \
if(! ((b)) ) {std::cout<< (err) <<std::endl; return false;}

bool Game1App::parseArgs(int argc, const char **argv)
{
    int i;
    
    // Parse Width
    if ((i = ArgParser::getArgIndex("--width", "-x", argc, argv)) != -1)
    {
        check_parse(i < argc-1, "no width argument");
        MazeWidth = atoi(argv[i+1]);
        check_parse(MazeWidth >= 2, "width should be >= 2");
    }
    
    // Parse Length
    if ((i = ArgParser::getArgIndex("--length", "-z", argc, argv)) != -1)
    {
        check_parse(i < argc-1, "no length argument");
        MazeLength = atoi(argv[i+1]);
        check_parse(MazeLength >= 2, "length should be >= 2");
    }
    
    // Parse working dir.
    if ((i = ArgParser::getArgIndex("--pwd", NULL, argc, argv)) != -1)
    {
        check_parse(i < argc-1, "no pwd argument");
        File::SetWorkingDirectory( argv[i+1] );
    }
    
    // Parse floor filename:
    if ((i = ArgParser::getArgIndex("--floor", NULL, argc, argv)) != -1)
    {
        check_parse(i < argc-1, "no floor argument");
        FloorDiffuseFilename = argv[i+1];
    }
    
    // Parse floor filename:
    if ((i = ArgParser::getArgIndex("--ceiling", NULL, argc, argv)) != -1)
    {
        check_parse(i < argc-1, "no ceiling argument");
        CeilingDiffuseFilename = argv[i+1];
    }
    
    // Parse wall filename:
    if ((i = ArgParser::getArgIndex("--wall", NULL, argc, argv)) != -1)
    {
        check_parse(i < argc-1, "no wall argument");
        WallDiffuseFilename = argv[i+1];
    }
    
    // Parse seed:
    if ((i = ArgParser::getArgIndex("--seed", "-s", argc, argv)) != -1)
    {
        check_parse(i < argc-1, "no seed argument");
        Seed = (unsigned long) atol(argv[i+1]);
        UseRandomSeed = false;
    }
    else {
        Seed = (unsigned long) time(NULL);
        UseRandomSeed = true;
    }
    
    // Parse print-path
    if ((i = ArgParser::getArgIndex("--print-path", NULL, argc, argv)) != -1) {
        LogSearchPath = true;
    }
    
    // Parse show-grid:
    if ((i = ArgParser::getArgIndex("--show-grid", NULL, argc, argv)) != -1) {
        ShowGrid = true;
    }
    
    // Parse show bvhs:
    if ((i = ArgParser::getArgIndex("--show-bvh", NULL, argc, argv)) != -1) {
        ShowBVH = true;
    }
    
    // Parse dungen-profile filename:
    if ((i = ArgParser::getArgIndex("--profile", NULL, argc, argv)) != -1)
    {
        check_parse(i < argc-1, "no profile filename");
        ProfileFilename = argv[i+1];
    }
    
    // Parse gfx options:
    if ((i = ArgParser::getArgIndex("--gfx", NULL, argc, argv)) != -1)
    {
        check_parse(i < argc-5, "missing argument(s) for --gfx");
        GfxWidth     = atoi (argv[i+1]);
        GfxHeight    = atoi (argv[i+2]);
        GfxRedBits   = atoi (argv[i+3]);
        GfxGreenBits = atoi (argv[i+4]);
        GfxBlueBits  = atoi (argv[i+5]);
    }
    
    return true;
}

void Game1App::printUsage()
{
         //         10        20        30        40        50        60        70
         //         |         |         |         |         |         |         |
    outln("Usage: dungen [OPTIONS]");
    outln("  --width [-x] ARG     width of the maze. Default 25.");
    outln("  --length [-z] ARG    length of the maze. Default 25.");
    outln("  --pwd ARG            use ARG as the program working directory.");
    outln("                       Default: here.");
    outln("  --floor ARG          filename of the floor's diffuse texture");
    outln("                       (relative to pwd).");
    outln("  --ceiling ARG        filename of the ceiling's diffuse texture");
    outln("                       (relative to pwd).");
    outln("  --wall ARG           filename of the wall's diffuse texture");
    outln("                       (relative to pwd).");
    outln("  --seed [-s] ARG      random number seed used. Default: clock time.");
    outln("  --print-path         tells the search-diggers to print the order in");
    outln("                       they visit cells.");
    outln("  --show-grid          renders a grid.");
    outln("  --show-bvh           renders the bounding volumes.");
    outln("  --profile            filename of the dungenprofile used.");
    outln("  --gfx-modes ARG      print all supported video modes into ARG file");
    outln("                       Default: stdout.");
    outln("  --gfx W H R G B      select a video mode amongst the supported video");
    outln("                       formats. Default: first in --gfx-modes");
}
