//
//  Digger.cpp
//  Dissert
//
//  Created by Olivier Legat on 12/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "Digger.h"

#include <Generator/Random/Random.h>
#include <Generator/Random/DiggerDependant.h>

Digger::Digger(Maze* maze)
{
    assert( maze );
    
    this->maze = maze;
}

Digger::~Digger()
{
    
}

void Digger::Init() 
{
    // Get random number generators used by this digger:
    Array<RandomI*> randomIArray = Array<RandomI*>();
    Array<RandomF*> randomFArray = Array<RandomF*>();
    GetRandomsUsed(randomIArray);
    GetRandomsUsed(randomFArray);
    
    // Declare local vars
    size_t i, n;
    DiggerDependant* depend = NULL;
    
    // For each digger-dependant generator, set the digger to this.
    n = randomIArray.size();
    for (i = 0; i < n; i++)
    {
        depend = dynamic_cast<DiggerDependant*>( randomIArray[i] );
        if ( depend != NULL )
            depend->SetDigger(this);
    }
    randomIArray.clear();
    
    // same for float generators:
    n = randomFArray.size();
    for (i = 0; i < n; i++)
    {
        depend = dynamic_cast<DiggerDependant*>( randomFArray[i] );
        if ( depend != NULL )
            depend->SetDigger(this);
    }
    randomFArray.clear();
    
    
    this->lastVisitedCell = this->maze->GetCell(0, 0);
    this->lastVisitedCell->SetVisited(true);
}
void Digger::End() { }

void Digger::DigFully()
{
    Init();
    while(!Step());
    End();
}
