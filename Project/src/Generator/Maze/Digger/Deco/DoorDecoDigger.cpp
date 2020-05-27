#include "DoorDecoDigger.h"

#include <Engine/Tools/Math.h> // just for PI.

DoorDecoDigger::DoorDecoDigger(Maze* maze, RandomI* randomI, RandomF* randomF, float density, String filename) : Digger(maze)
{
	this->weightFile = WeightFile::CreateFromFile(filename, randomI);
	this->randomI = randomI;
	this->randomF = randomF;
	this->density = density;
	assert ( density>=0 && density <= 1);
}

DoorDecoDigger::~DoorDecoDigger()
{
}

void DoorDecoDigger::Init()
{
}

bool DoorDecoDigger::Step()
{
	if (weightFile == NULL)
	{
		std::cout << "DoorDecoDigger:: Error. weightFile is NULL." << std::endl;
		return true;
	}
    
    int x, z, W, L;
    Quaternion q;
    
    /// --------------------------------------------
    ///    Horizontal walls:
    /// --------------------------------------------
    q = Quaternion(Vector3(0));
    W = maze->HWallWidth();
    L = maze->HWallLength();
    for (x = 0; x < W; x++)
    for (z = 0; z < L; z++)
    {
        if (   canBeHDoor(x, z)  // check if this slot is ok for a door.
            && randomF->nextFloat(0, 1) <= density ) // dice roll.
        {
            Vector3 pos = Vector3(0.5f + x, 0, z);
            MakeRandomDoor(q, pos);
        }
    }
    
    /// --------------------------------------------
    ///    Vertical walls:
    /// --------------------------------------------
    q = Quaternion(Vector3(0, PI / 2.0f, 0));
    W = maze->VWallWidth();
    L = maze->VWallLength();
    for (x = 0; x < W; x++)
    for (z = 0; z < L; z++)
    {
        if (   canBeVDoor(x, z)  // check if this slot is ok for a door.
            && randomF->nextFloat(0, 1) <= density ) // dice roll.
        {
            Vector3 pos = Vector3(x, 0, z + 0.5f);
            MakeRandomDoor(q, pos);
        }
    }
    
    return true;
}

void DoorDecoDigger::End()
{
}

void DoorDecoDigger::GetRandomsUsed(Array<RandomI*> &array)
{
	array.push_back(randomI);
}

void DoorDecoDigger::GetRandomsUsed(Array<RandomF*> &array)
{
	array.push_back(randomF);
}

bool DoorDecoDigger::canBeHDoor(int x, int z)
{
    // Check if this wall slot is free:
    {
        if ( maze->GetHWall(x, z)->GetType() != MAZE_WALLTYPE_NONE )
            return false; // Not free. In use by a wall. We shouldn't place a door here.
    }
    
    int W = maze->Width();
    int L = maze->Length();
    
    // Check for neighbour walls
    {
        // Check if there's a wall or the left (vert. or horiz.)
        if (x > 0 && maze->GetHWall(x-1, z)->GetType() != MAZE_WALLTYPE_DEFAULT &&// hori wall.
            z > 0 && maze->GetVWall(x, z-1)->GetType() != MAZE_WALLTYPE_DEFAULT &&// v-wall above.
            z < L && maze->GetVWall(x, z)->GetType()   != MAZE_WALLTYPE_DEFAULT ) // v-wall below.
            return false; // no left neighbour. Bad place for a wall.
        
        // Do the same with the right wall:
        if (x < W-1 && maze->GetHWall(x+1, z)->GetType()   != MAZE_WALLTYPE_DEFAULT &&// hori wall.
            z > 0   && maze->GetVWall(x+1, z-1)->GetType() != MAZE_WALLTYPE_DEFAULT &&// v-wall above.
            z < L   && maze->GetVWall(x+1, z)->GetType()   != MAZE_WALLTYPE_DEFAULT ) // v-wall below.
            return false; // no right neighbour. Bad place for a wall.
    }
    
    // Check for adjacent room:
    {        
        // We need to try find a small 2x2 room near this wall.
        // Let us check the top-left, top-right, bottom-right, and bottom-left
        // 2x2 sections touching this wall.
        MazeCell *corner1, *corner2;
        
        
        // top-left:
        if ( x >= 1 && z >= 2 )
        {
            corner1  = maze->GetCell(x-1, z-2); // -2 for z because there's extra h-wall on the top.
            corner2  = maze->GetCell( x , z-1);
            if (maze->IsRoom(corner1, corner2)) return true;
        }
        
        // top-right:
        if ( x < W-1 && z >= 2 )
        {
            corner1  = maze->GetCell( x , z-2);
            corner2  = maze->GetCell(x+1, z-1);
            if (maze->IsRoom(corner1, corner2)) return true;
        }
        
        // bottom-left:
        if ( x >= 1 && (z < L-1) )
        {
            corner1  = maze->GetCell(x-1,  z );
            corner2  = maze->GetCell( x , z+1);
            if (maze->IsRoom(corner1, corner2)) return true;
        }
        
        // bottom-right:
        if ( x < W-1 && (z < L-1) )
        {
            corner1  = maze->GetCell( x ,  z);
            corner2  = maze->GetCell(x+1, z+1);
            if (maze->IsRoom(corner1, corner2)) return true;
        }
    }
    
    return false;
}

bool DoorDecoDigger::canBeVDoor(int x, int z)
{
    // Check if this wall slot is free:
    {
        if (maze->GetVWall(x, z)->GetType() != MAZE_WALLTYPE_NONE)
            return false; // Not free. In use by a wall. We shouldn't place a door here.
    }
        
    int W = maze->Width();
    int L = maze->Length();
    
    // Check for neighbour walls
    {
        // Check if the top wall isn't broken (or doesn't exist).
        if (z > 0 && maze->GetVWall(x, z-1)->GetType() != MAZE_WALLTYPE_DEFAULT &&// vert. wall
            x > 0 && maze->GetHWall(x-1, z)->GetType() != MAZE_WALLTYPE_DEFAULT &&// h-wall on left.
            x < W && maze->GetHWall(x, z)->GetType()   != MAZE_WALLTYPE_DEFAULT ) // h-wall on right.
            return false;
        
        // Do the same with the bottom wall:
        if (z < L-1 && maze->GetVWall(x,   z+1)->GetType() != MAZE_WALLTYPE_DEFAULT &&// vert. wall
            x > 0   && maze->GetHWall(x-1, z+1)->GetType() != MAZE_WALLTYPE_DEFAULT &&// h-wall on left.
            x < W   && maze->GetHWall(x,   z+1)->GetType() != MAZE_WALLTYPE_DEFAULT ) // h-wall on right.
            return false;
    }
    
    // Check for adjacent rooms:
    {
        // We need to try find a small 2x2 room near this wall.
        // Let us check the top-left, top-right, bottom-right, and bottom-left
        // 2x2 sections touching this wall.
        MazeCell *corner1, *corner2;
        
        
        // top-left:
        if ( x >= 2 && z >= 1 )
        {
            corner1  = maze->GetCell(x-2, z-1); // -2 for x because there's extra v-wall on the left.
            corner2  = maze->GetCell(x-1,  z);
            if (maze->IsRoom(corner1, corner2)) return true;
        }
        
        // top-right:
        if ( x < W-1 && z >= 1 )
        {
            corner1  = maze->GetCell( x , z-1);
            corner2  = maze->GetCell(x+1,  z);
            if (maze->IsRoom(corner1, corner2)) return true;
        }
        
        // bottom-left:
        if ( x >= 2 && z < L-1 )
        {
            corner1  = maze->GetCell(x-2,  z );
            corner2  = maze->GetCell(x-1, z+1);
            if (maze->IsRoom(corner1, corner2)) return true;
        }
        
        // bottom-right:
        if ( x < W-1 && z < L-1 )
        {
            corner1  = maze->GetCell( x ,  z);
            corner2  = maze->GetCell(x+1, z+1);
            if (maze->IsRoom(corner1, corner2)) return true;
        }
    }
    
    return false;
}

void DoorDecoDigger::MakeRandomDoor(Quaternion rot, Vector3 translation)
{
    // Add a random decoration item:
    String item = weightFile->GetRandomFile();
    
    // Add this item
    this->AddExternalMesh(item, translation, rot);
}
