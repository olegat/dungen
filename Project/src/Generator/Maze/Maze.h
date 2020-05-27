//
//  Maze.h
//  Dissert
//
//  Created by Olivier Legat on 07/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef MAZE_H_
#define MAZE_H_

#include <platform.h>

#include "MazeCell.h"
#include "MazeWall.h"

class Maze
extends Object
{
public:
    Maze(int width, int length);
    ~Maze();
    
    /**
     * Get a cell.
     * @param A pointer to cell. If [x,z] is out of range, NULL is returned.
     */
    MazeCell* GetCell(const int x, const int z) const;
    MazeWall* GetWall(const MazeCell* cell, MazeWallPosition pos) const;
    MazeWall* GetWall(const int x, const int z, MazeWallPosition pos) const;
    
    MazeWall* GetVWall(const int x, const int z) const {return vwalls[x + z * (width+1)];};
    MazeWall* GetHWall(const int x, const int z) const {return hwalls[x + z * (width)];};
    
    /**
     * Get the cells above and below of the horizontal wall (x, z).
     * @param (x,z) A h-wall's coordinates.
     * @param top [output] Cell above the h-wall (x,z).
     * @param bottom [output] Cell below the h-wall (x,z).
     */
    void GetTopAndBottomCell(const int x, const int z, MazeCell** top, MazeCell** bottom) const;
    
    /**
     * Get the cells on the left and right of the vertical wall (x, z).
     * @param (x,z) A v-wall's coordinates.
     * @param left [output] Cell on the left of the v-wall (x,z).
     * @param right [output] Cell on the right of the v-wall (x,z).
     */
    void GetLeftAndRightCell(const int x, const int z, MazeCell** left, MazeCell** right) const;
    
    /**
     * Break the wall between two adjacent cells (i.e. Set it to WALLTYPE_NONE).
     *
     * @param cell1 Any cell.
     * @param cell2 Any cell.
     */
    void BreakWalls(const MazeCell* cell1, const MazeCell* cell2);
    
    /**
     * Break all the vertical walls within the region of cell1 and cell2 (excluding borders)
     * @param cell1 Any cell.
     * @param cell2 Any cell.
     */
    void BreakVWalls(const MazeCell* cell1, const MazeCell* cell2);
    
    /**
     * Break all the horizontal walls within the region of cell1 and cell2 
     * (excluding borders)
     * @param cell1 Any cell.
     * @param cell2 Any cell.
     */
    void BreakHWalls(const MazeCell* cell1, const MazeCell* cell2);
    
    /**
     * @return true if cell1 and cell2 are adjacent (i.e. x, z indices differ by 1 exactly)
     */
    bool AreAdjacent(const MazeCell* cell1, const MazeCell* cell2) const;
    
    /**
     * @param cell Which cell to wall off completely. This cell is set to MAZE_CELL_WALL.
     */
    void WallOff(MazeCell* cell);
    
    /**
     * @param cell Any cell.
     * @return The number of walls this cell is touching.
     */
    int GetWallCount(const MazeCell* cell) const;
    
    /**
     * @return True if cell is considered a dead-end (i.e. wall count = 3).
     */
    bool IsDeadEnd(const MazeCell* cell) const {return GetWallCount(cell) == 3;}
    
    /**
     * @return True if their are no walls in between cell1 to cell2.
     */
    bool IsRoom(const MazeCell* cell1, const MazeCell* cell2);
    
    int Width() const {return width;}
    int Length() const {return length;}
    
    int VWallWidth() const {return width + 1;}
    int VWallLength() const {return length;}
    
    int HWallWidth() const {return width;}
    int HWallLength() const {return length + 1;}
    
    /**
     * @param cell Parent cell.
     * @param children [output] An array of atleast an initial size 4. Points to adjacent
     *        unvisited cells. Use NULL if you just want the count.
     * @return number of visited children.
     */
    int GetUnvisitedCells(const MazeCell* cell, MazeCell** children) const;
    
    /**
     * @param cell Parent cell.
     * @param children [output] An array of atleast an initial size 4. Points to adjacent
     *        cells. Use NULL if you just want the count.
     * @return number of adjacent cell.
     */
    int GetAdjacentCells(const MazeCell* cell, MazeCell** children) const;
    
    /**
     * Print maze to file:
     */
    void Print(FILE* output) const;
    
    /**
     * Print maze to stdout:
     */
    void Print() const;
    
private:
    int width;
    int length;
    
    Array<MazeCell*> cells;
    Array<MazeWall*> vwalls;
    Array<MazeWall*> hwalls;
    
    void printHWall(FILE* output, int x, int z) const;
    void printVWall(FILE* output, int x, int z) const;
    void printCell (FILE* output, int x, int z) const;
};

#endif
