#include "LoopDigger.h"

#include <Generator/Random/Random.h>

LoopDigger::LoopDigger(Maze* maze, RandomI* randomI, RandomF* randomF, float removeProb) : Digger(maze)
{
    assert(removeProb >= 0  && removeProb <= 1);
    
    this->randomI = randomI;
    this->randomF = randomF;
    this->removeProb = removeProb;
}
LoopDigger::~LoopDigger()
{
    
}

void LoopDigger::Init()
{
    x = z = 0;
}
bool LoopDigger::Step()
{
    // Get the cell we're looking at:
    MazeCell* cell = maze->GetCell(x, z);
    
    // Is (x, z) a dead-end? should it be looped?
    if ( maze->GetWallCount(cell) == 3 && randomF->nextFloat(0, 1) <= removeProb)
    {
        bool loopComplete = false;
        
        while ( !loopComplete )
        {
            // Get a new cell and check if it created a loop:
            MazeCell* nextCell = GetRandomNextCell(cell);
            loopComplete = maze->GetWallCount(nextCell) < 4;
            
            // Break the walls.
            maze->BreakWalls(cell, nextCell);
            nextCell->SetCellType(MAZE_CELL_FLOOR);
            
            // Iterate:
            cell = nextCell;
        }
    }
    
    z++;
    if (z == maze->Length())
    {
        z = 0;
        x++;
    }
    return x == maze->Width();
}
void LoopDigger::End()
{
    
}

void LoopDigger::GetRandomsUsed(Array<RandomI*> &array)
{
    array.push_back(randomI);
}
void LoopDigger::GetRandomsUsed(Array<RandomF*> &array)
{
    array.push_back(randomF);
}

MazeCell* LoopDigger::GetRandomNextCell(MazeCell* deadEnd)
{
    MazeCell* allAdjacents   [4]; // max of 4 adjacent cells. Less for border cells.
    MazeCell* validAdjacents [3]; // allAdjacents excluding the corridor.
    
    // Get the adjacent cells and count:
    int count = maze->GetAdjacentCells(deadEnd, allAdjacents);
    
    // Get the corridor:
    MazeCell* corridor = GetCorridorOfDeadEnd(deadEnd);
    
    // Exclude the corridor from the set allAdjacents.
    int j = 0;
    for (int i = 0; i < count; i++)
        if (allAdjacents[i] != corridor)
            validAdjacents[j++] = allAdjacents[i];
    
    assert(j < 4);
    
    return validAdjacents[randomI->nextInt(0, j)];
}

MazeCell* LoopDigger::GetCorridorOfDeadEnd(MazeCell* deadEnd)
{
    //assert( maze->GetWallCount(deadEnd) == 3);
    
    int x = deadEnd->X(), z = deadEnd->Z();
    
    if ( maze->GetWall(deadEnd, MAZE_WALLPOS_UP)->GetType() == MAZE_WALLTYPE_NONE )
        return maze->GetCell(x, z-1);
    
    if ( maze->GetWall(deadEnd, MAZE_WALLPOS_DOWN)->GetType() == MAZE_WALLTYPE_NONE )
        return maze->GetCell(x, z+1);
    
    if ( maze->GetWall(deadEnd, MAZE_WALLPOS_RIGHT)->GetType() == MAZE_WALLTYPE_NONE )
        return maze->GetCell(x+1, z);
    
    if ( maze->GetWall(deadEnd, MAZE_WALLPOS_LEFT)->GetType() == MAZE_WALLTYPE_NONE )
        return maze->GetCell(x-1, z);
    
    return NULL; // shouldn't ever happen.
}
