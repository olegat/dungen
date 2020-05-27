#ifndef LOOP_DIGGER_H_
#define LOOP_DIGGER_H_

#include <platform.h>
#include <Generator/Maze/Digger/Digger.h>

class LoopDigger
extends Digger
{
public:
    LoopDigger(Maze* maze, RandomI* randomI, RandomF* randomF, float removeProb);
    ~LoopDigger();
    
    virtual void Init();
    virtual bool Step();
    virtual void End();
    
    virtual void GetRandomsUsed(Array<RandomI*> &array);
    virtual void GetRandomsUsed(Array<RandomF*> &array);
    
private:
    RandomI* randomI;
    RandomF* randomF;
    float removeProb;
    int x,z;
    
    /**
     * @param deadEnd A dead-end (i.e. cell with 3 walls).
     * @return A random cell other than the corridor cell adjacent to the dead-end.
     */
    MazeCell* GetRandomNextCell(MazeCell* deadEnd);
    
    /**
     * @param deadEnd A dead-end (i.e. cell with 3 walls).
     * @return The corridor cell adjacent to the dead-end
     */
    MazeCell* GetCorridorOfDeadEnd(MazeCell* deadEnd);
};

#endif
