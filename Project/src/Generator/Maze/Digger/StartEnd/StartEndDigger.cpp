#include "StartEndDigger.h"

StartEndDigger::StartEndDigger(Maze* maze) : Digger(maze)
{}
StartEndDigger::~StartEndDigger()
{}

void StartEndDigger::Init()
{
    int w = maze->Width(), l = maze->Length();
    maze->BreakWalls(maze->GetCell(0,  0),  maze->GetCell(1,  1));  // starting area.
    maze->BreakWalls(maze->GetCell(w-2,l-2),maze->GetCell(w-1,l-1));// goal area.
}
 
bool StartEndDigger::Step() {return true;}
void StartEndDigger::End() {}
    
void StartEndDigger::GetRandomsUsed(Array<RandomI*> &array) {}
void StartEndDigger::GetRandomsUsed(Array<RandomF*> &array) {}
