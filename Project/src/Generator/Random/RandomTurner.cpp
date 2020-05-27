//
//  RandomTurner.cpp
//  Dissert
//
//  Created by Olivier Legat on 25/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "RandomTurner.h"

#include <Generator/Maze/Maze.h>
#include <Generator/Maze/MazeCell.h>
#include <Generator/Maze/Digger/Digger.h>

bool checkConstraints(RandomI* di, RandomF* df, float l, float r);
bool checkConstraints(RandomI* di, RandomF* df, float l, float r)
{
    return df && di && 0 < l && l < 1 && 0 < r && r < 1 && r + l < 1;
}

RandomTurner::RandomTurner(RandomI* di, RandomF* df, float leftProb, float rightProb)
{
    assert (checkConstraints(di, df, leftProb, rightProb));
    
    this->randomi    = di;
    this->randomf    = df;
    this->leftProb   = leftProb;
    this->rightProb  = rightProb;
    this->SetDigger( NULL );
}

RandomTurner::RandomTurner(RandomI* di, RandomF* df, float leftProb, float rightProb, Digger* digger)
{
    assert (checkConstraints(di, df, leftProb, rightProb) && digger);
    
    this->randomi    = di;
    this->randomf    = df;
    this->leftProb   = leftProb;
    this->rightProb  = rightProb;
    this->SetDigger( digger );
}

int RandomTurner::nextInt()
{
    // Get maze & current cell:
    Maze* maze = GetDigger()->GetMaze();
    MazeCell* here = GetDigger()->GetLastVisited();
    
    assert (maze->GetUnvisitedCells(here, NULL) > 0) ;
    
    if ( maze->IsDeadEnd(here) )
    {
        // Get children:
        MazeCell* straight;
        MazeCell* left;
        MazeCell* right;
        GetStraightLeftRight(&straight, &left, &right);
        
        bool canStraight = (straight != NULL) && (! straight->IsVisited() );
        bool canLeft     = (left != NULL) && (! left->IsVisited() );
        bool canRight    = (right!= NULL) && (!right->IsVisited() );
        bool canTurn     = canLeft || canRight;
        
        if ( !canStraight || !canTurn )
        {
            goto pick_random;
        }
        else 
        {
            float rightThres = this->rightProb;
            float leftThres  = this->leftProb;
            float straightThres = 1 - rightThres - leftThres;
            
            // are straight / left / right possible? change probabilities if impossible.
            straightThres = canStraight ? straightThres : 0;
            rightThres    = canRight    ? rightThres    : 0;
            leftThres     = canLeft     ? leftThres     : 0;
            
            // total probability. =1 if (canStraight && canLeft && canRight).
            float P = straightThres + rightThres + leftThres;
            
            // normalize probs from [0, P] into [0, 1]
            straightThres /= P;
            rightThres    /= P;
            leftThres     /= P;
            
            // calc thresholds:
            rightThres += straightThres;
            leftThres  += rightThres;
            
            // get random value in [0, 1] interval:
            float t = randomf->nextFloat(0, 1);
            
            // figure out which cell to go to:
            MazeCell* goHere = NULL;
                 if ( t < straightThres ) goHere = straight;
            else if ( t < rightThres    ) goHere = right;
            else if ( t < leftThres     ) goHere = left;
            
            // get the children:
            MazeCell* children[4];  int n;
            n = maze->GetUnvisitedCells(here, children);
            
            // find and return the index of goHere.
            for ( int i = 0; i < n; i ++ )
                if (children[i] == goHere) return i;
            
            // if an un-expected result occurs (e.g. floating-point error)
            // then just return something valid.
            goto pick_random;
        }
    }
    else {
        // The notion of "straight" is ambigious. Just pick random number
        goto pick_random;
    }
    
pick_random:
    int n = maze->GetUnvisitedCells(here, NULL);
    return this->randomi->nextInt(0, n);
}
int RandomTurner::nextInt(int max)
{
    int x = nextInt();
    
    // cap at max:
    return x > max ? max : x ;
}
int RandomTurner::nextInt(int min, int max)
{
    // cap at max:
    int x = nextInt(max);
    
    // cap at min:
    return x < min ? min : x ;
}
void RandomTurner::GetStraightLeftRight(MazeCell** straight, MazeCell** left, MazeCell** right)
{
    // Get maze & current cell:
    Maze* maze = GetDigger()->GetMaze();
    MazeCell* here = GetDigger()->GetLastVisited();
    
    // Which cell is straight? which is left and right?
    if ( maze->GetWall(here, MAZE_WALLPOS_UP)->GetType() == MAZE_WALLTYPE_NONE )
    {
        *straight = maze->GetCell( here->X(),     here->Z() + 1);
        *left     = maze->GetCell( here->X() + 1, here->Z() );
        *right    = maze->GetCell( here->X() - 1, here->Z() );
    }
    else if ( maze->GetWall(here, MAZE_WALLPOS_DOWN)->GetType() == MAZE_WALLTYPE_NONE )
    {
        *straight = maze->GetCell( here->X(),     here->Z() - 1);
        *left     = maze->GetCell( here->X() - 1, here->Z() );
        *right    = maze->GetCell( here->X() + 1, here->Z() );
    }
    else if ( maze->GetWall(here, MAZE_WALLPOS_LEFT)->GetType() == MAZE_WALLTYPE_NONE )
    {
        *straight = maze->GetCell( here->X() + 1, here->Z() );
        *left     = maze->GetCell( here->X(),     here->Z() - 1 );
        *right    = maze->GetCell( here->X(),     here->Z() + 1 );
    }
    else if ( maze->GetWall(here, MAZE_WALLPOS_RIGHT)->GetType() == MAZE_WALLTYPE_NONE )
    {
        *straight = maze->GetCell( here->X() - 1, here->Z() );
        *left     = maze->GetCell( here->X(),     here->Z() + 1 );
        *right    = maze->GetCell( here->X(),     here->Z() - 1 );
    }
    
    return;
}

