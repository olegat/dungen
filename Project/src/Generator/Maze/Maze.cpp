//
//  Maze.cpp
//  Dissert
//
//  Created by Olivier Legat on 07/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "Maze.h"

Maze::Maze(int width, int length)
{
    // Local variables:
    int x, z, w, l;
    
    this->width = width;
    this->length = length;
    
    // Initialize cells:
    w = width;
    l = length;
    cells = Array<MazeCell*>(w * l);
    for (x = 0; x < w; x++)
        for (z = 0; z < l; z++)
            cells [ x + (z * w) ] = new MazeCell(x, z, MAZE_CELL_FLOOR);
    
    
    // Initialize Vertical walls:
    w = width + 1;
    l = length;
    vwalls = Array<MazeWall*>(w * l);
    for (x = 0; x < w; x++)
        for (z = 0; z < l; z++)
            vwalls [ x + (z * w) ] = new MazeWall();
    
    // Initialize Horizontal walls:
    w = width;
    l = length + 1;
    hwalls = Array<MazeWall*>(w * l);
    for (x = 0; x < w; x++)
        for (z = 0; z < l; z++)
            hwalls [ x + (z * w) ] = new MazeWall();
}

Maze::~Maze()
{
    int i,n;
    
    // Destroy ALL the cells!
    n = (int) cells.size();
    for (i = 0; i < n; i++) {
        delete cells[i];
    }
    cells.clear();
    
    
    // Destroy ALL the vertical walls!
    n = (int) vwalls.size();
    for (i = 0; i < n; i++) {
        delete vwalls[i];
    }
    vwalls.clear();
    
    
    // Destroy ALL the horizontal walls!
    n = (int) hwalls.size();
    for (i = 0; i < n; i++) {
        delete hwalls[i];
    }
    hwalls.clear();
}

void Maze::BreakWalls(const MazeCell* cell1, const MazeCell* cell2)
{
    BreakVWalls(cell1, cell2);
    BreakHWalls(cell1, cell2);
}

void Maze::BreakVWalls(const MazeCell* cell1, const MazeCell* cell2)
{
    int x, XX, xi; // min / max x values, iterator for x.
    int z, ZZ, zi; // min / max z values, iterator for z.
    
    x = cell1->X() < cell2->X() ? cell1->X() : cell2->X();
    XX= cell1->X() > cell2->X() ? cell1->X() : cell2->X();
    z = cell1->Z() < cell2->Z() ? cell1->Z() : cell2->Z();
    ZZ= cell1->Z() > cell2->Z() ? cell1->Z() : cell2->Z();

    for ( xi = x ; xi < XX ; xi ++ )
        for (zi = z; zi <= ZZ ; zi ++ )
            GetWall(xi, zi, MAZE_WALLPOS_RIGHT)->SetType(MAZE_WALLTYPE_NONE);
}

void Maze::BreakHWalls(const MazeCell* cell1, const MazeCell* cell2)
{
    int x, XX, xi; // min / max x values, iterator for x.
    int z, ZZ, zi; // min / max z values, iterator for z.
    
    x = cell1->X() < cell2->X() ? cell1->X() : cell2->X();
    XX= cell1->X() > cell2->X() ? cell1->X() : cell2->X();
    z = cell1->Z() < cell2->Z() ? cell1->Z() : cell2->Z();
    ZZ= cell1->Z() > cell2->Z() ? cell1->Z() : cell2->Z();
    
    for ( zi = z ; zi < ZZ ; zi ++ )
        for (xi = x; xi <= XX ; xi ++ )
            GetWall(xi, zi, MAZE_WALLPOS_DOWN)->SetType(MAZE_WALLTYPE_NONE);
}

bool Maze::AreAdjacent(const MazeCell* cell1, const MazeCell* cell2) const
{
    int sum1 = cell1->X() + cell1->Z();
    int sum2 = cell2->X() + cell2->Z();
    
    // Do sum1 and sum2 differ by 1 ?
    if (sum1 != sum2 + 1 && sum1 + 1 != sum2) return false; // no!
    
    // Do cell1 and cell2 have either x or z in common?
    else return 
        cell1->X() == cell2->X() || 
        cell1->Z() == cell2->Z();
}

void Maze::WallOff(MazeCell* cell)
{
    GetWall(cell, MAZE_WALLPOS_DOWN)->SetType(MAZE_WALLTYPE_DEFAULT);
    GetWall(cell, MAZE_WALLPOS_UP)->SetType(MAZE_WALLTYPE_DEFAULT);
    GetWall(cell, MAZE_WALLPOS_RIGHT)->SetType(MAZE_WALLTYPE_DEFAULT);
    GetWall(cell, MAZE_WALLPOS_LEFT)->SetType(MAZE_WALLTYPE_DEFAULT);
    cell->SetCellType(MAZE_CELL_WALL);
}

int Maze::GetWallCount(const MazeCell* cell) const
{
    int i = 0;
    
    if (GetWall(cell, MAZE_WALLPOS_DOWN) ->GetType() == MAZE_WALLTYPE_DEFAULT) i++;
    if (GetWall(cell, MAZE_WALLPOS_UP)   ->GetType() == MAZE_WALLTYPE_DEFAULT) i++;
    if (GetWall(cell, MAZE_WALLPOS_RIGHT)->GetType() == MAZE_WALLTYPE_DEFAULT) i++;
    if (GetWall(cell, MAZE_WALLPOS_LEFT) ->GetType() == MAZE_WALLTYPE_DEFAULT) i++;
    
    return i;
}

MazeCell* Maze::GetCell(const int x, const int z) const 
{
    // Check range:
    if (x >= width || z >= length || x < 0 || z < 0) return NULL;
    
    // Range ok:
    return cells[x + z * width];
}

void Maze::GetTopAndBottomCell(const int x, const int z, MazeCell** top, MazeCell** bottom) const
{
    *top    = NULL;
    *bottom = NULL;
    
    if ( z > 0 ) *top = GetCell(x, z-1);
    if ( z < HWallWidth()) *bottom = GetCell(x, z);
}

void Maze::GetLeftAndRightCell(const int x, const int z, MazeCell** left, MazeCell** right) const
{
    *left  = NULL;
    *right = NULL;
    
    if ( x > 0 ) *left = GetCell(x-1, z);
    if ( x < VWallWidth()) *right = GetCell(x, z);
}

MazeWall* Maze::GetWall(const MazeCell* cell, MazeWallPosition pos) const 
{
    return GetWall(cell->X(), cell->Z(), pos);
}

MazeWall* Maze::GetWall(const int x, const int z, MazeWallPosition pos) const 
{
    switch(pos)
    {
        case MAZE_WALLPOS_UP:    return GetHWall(x, z);
        case MAZE_WALLPOS_DOWN:  return GetHWall(x, z+1);
        case MAZE_WALLPOS_LEFT:  return GetVWall(x, z);
        case MAZE_WALLPOS_RIGHT: return GetVWall(x+1, z);
        default: assert(0);
    }
    
    return NULL;
}

int Maze::GetUnvisitedCells(const MazeCell* cell, MazeCell** children) const
{
    int x = cell->X(), z = cell->Z();
    int count = 0;
    MazeCell* child;
    
    if (x != 0 && !(child = GetCell(x - 1, z))->IsVisited())
        if(children==NULL) count++; else children[count++] = child;
    
    if (z != 0 && !(child = GetCell(x, z - 1))->IsVisited())
        if(children==NULL) count++; else children[count++] = child;
    
    if (x != width - 1 && !(child = GetCell(x + 1, z))->IsVisited())
        if(children==NULL) count++; else children[count++] = child;
    
    if (z != length- 1 && !(child = GetCell(x, z + 1))->IsVisited())
        if(children==NULL) count++; else children[count++] = child;
    
    return count;
}

int Maze::GetAdjacentCells(const MazeCell* cell, MazeCell** children) const
{
    int x = cell->X(), z = cell->Z();
    int count = 0;
    MazeCell* child;
    
    if (x != 0 && (child = GetCell(x - 1, z)))
        if(children==NULL) count++; else children[count++] = child;
    
    if (z != 0 && (child = GetCell(x, z - 1)))
        if(children==NULL) count++; else children[count++] = child;
    
    if (x != width - 1 && (child = GetCell(x + 1, z)))
        if(children==NULL) count++; else children[count++] = child;
    
    if (z != length- 1 && (child = GetCell(x, z + 1)))
        if(children==NULL) count++; else children[count++] = child;
    
    return count;
}

bool Maze::IsRoom(const MazeCell* cell1, const MazeCell* cell2)
{
    int x, XX, xi; // min / max x values, iterator for x.
    int z, ZZ, zi; // min / max z values, iterator for z.
    
    x = cell1->X() < cell2->X() ? cell1->X() : cell2->X();
    XX= cell1->X() > cell2->X() ? cell1->X() : cell2->X();
    z = cell1->Z() < cell2->Z() ? cell1->Z() : cell2->Z();
    ZZ= cell1->Z() > cell2->Z() ? cell1->Z() : cell2->Z();
    
    MazeCell* cell;
    
    // Check corner 1:
    cell = this->GetCell(x,z);
    if (this->GetWall(cell, MAZE_WALLPOS_RIGHT)->GetType() != MAZE_WALLTYPE_NONE ||
        this->GetWall(cell, MAZE_WALLPOS_DOWN)->GetType()  != MAZE_WALLTYPE_NONE)
        return false;
    
    // Check corner 2:
    cell = this->GetCell(x,ZZ);
    if (this->GetWall(cell, MAZE_WALLPOS_RIGHT)->GetType() != MAZE_WALLTYPE_NONE ||
        this->GetWall(cell, MAZE_WALLPOS_UP)->GetType()    != MAZE_WALLTYPE_NONE)
        return false;
    
    // Check corner 3:
    cell = this->GetCell(XX,z);
    if (this->GetWall(cell, MAZE_WALLPOS_LEFT)->GetType()  != MAZE_WALLTYPE_NONE ||
        this->GetWall(cell, MAZE_WALLPOS_DOWN)->GetType()  != MAZE_WALLTYPE_NONE)
        return false;
    
    // Check corner 4:
    cell = this->GetCell(XX,ZZ);
    if (this->GetWall(cell, MAZE_WALLPOS_LEFT)->GetType()  != MAZE_WALLTYPE_NONE ||
        this->GetWall(cell, MAZE_WALLPOS_UP)->GetType()    != MAZE_WALLTYPE_NONE)
        return false;
    
    // Check top-most and bottom-most cells:
    for (xi = x+1; xi < XX-1; xi++)
    {
        // top cell
        cell = this->GetCell(xi,z);
        if (this->GetWall(cell, MAZE_WALLPOS_RIGHT)->GetType()  != MAZE_WALLTYPE_NONE ||
            this->GetWall(cell, MAZE_WALLPOS_LEFT)->GetType()   != MAZE_WALLTYPE_NONE ||
            this->GetWall(cell, MAZE_WALLPOS_DOWN)->GetType()   != MAZE_WALLTYPE_NONE)
            return false;
        
        // bottom cell
        cell = this->GetCell(xi,z);
        if (this->GetWall(cell, MAZE_WALLPOS_RIGHT)->GetType()  != MAZE_WALLTYPE_NONE ||
            this->GetWall(cell, MAZE_WALLPOS_LEFT)->GetType()   != MAZE_WALLTYPE_NONE ||
            this->GetWall(cell, MAZE_WALLPOS_UP)->GetType()     != MAZE_WALLTYPE_NONE)
            return false;
    }
    
    // Check right-most and left-most cells:
    for (zi = z+1; zi < ZZ-1; zi++)
    {
        // left cell
        cell = this->GetCell(x,zi);
        if (this->GetWall(cell, MAZE_WALLPOS_UP)->GetType()      != MAZE_WALLTYPE_NONE ||
            this->GetWall(cell, MAZE_WALLPOS_DOWN)->GetType()    != MAZE_WALLTYPE_NONE ||
            this->GetWall(cell, MAZE_WALLPOS_RIGHT)->GetType()   != MAZE_WALLTYPE_NONE)
            return false;
        
        // right cell
        cell = this->GetCell(x,zi);
        if (this->GetWall(cell, MAZE_WALLPOS_UP)->GetType()      != MAZE_WALLTYPE_NONE ||
            this->GetWall(cell, MAZE_WALLPOS_DOWN)->GetType()    != MAZE_WALLTYPE_NONE ||
            this->GetWall(cell, MAZE_WALLPOS_LEFT)->GetType()    != MAZE_WALLTYPE_NONE)
            return false;
    }
    
    // Check middle cells:
    for (xi = x+1; xi < XX-1; xi++)
    for (zi = z+1; zi < ZZ-1; zi++)
    {
        cell = this->GetCell(xi,zi);
        if (this->GetWallCount(cell) != 4) return false;
    }
    
    // Constraints are respected. This subset is a room.
    return true;
}

void Maze::Print(FILE* output) const
{
    int x, z;
    
    // Print cells line-by-line.
    for (z = 0; z < length; z++)
    {
        // Print upper h-walls:
        for ( x = 0; x < width; x++ )
        {
            printHWall(output, x, z);
        } 
        fprintf(output, ".\n");
        
        // Print cells and v-walls:
        for ( x = 0; x < width; x++ )
        {
            printVWall(output, x, z);
            printCell (output, x, z);
        } 
        
        // Print last v-wall:
        printVWall(output, x, z);
        
        fprintf(output, "\n");
    }
    
    // Print last line of h-walls
    for ( x = 0; x < width; x++ )
    {
        printHWall(output, x, z);
    } fprintf(output, ".\n");
}
void Maze::Print() const {Print(stdout);}


void Maze::printHWall(FILE* output, int x, int z) const
{
    if (GetHWall(x, z)->GetType() == MAZE_WALLTYPE_NONE)
        fprintf(output, ". ");
    else
        fprintf(output, ".-");
}
void Maze::printVWall(FILE* output, int x, int z) const
{
    if (GetVWall(x, z)->GetType() == MAZE_WALLTYPE_NONE)
        fprintf(output, " ");
    else
        fprintf(output, "|");
}
void Maze::printCell (FILE* output, int x, int z) const
{
    if (GetCell(x, z)->GetCellType() == MAZE_CELL_WALL)
        fprintf(output, "X");
    else
        fprintf(output, " ");
}
        
