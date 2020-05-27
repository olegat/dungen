#ifndef START_END_DIGGER_H_
#define START_END_DIGGER_H_

#include <platform.h>
#include <Generator/Maze/Digger/Digger.h>

class StartEndDigger
extends Digger
{
public:
    StartEndDigger(Maze* maze);
    ~StartEndDigger();

    virtual void Init();
    virtual bool Step();
    virtual void End();
    
    virtual void GetRandomsUsed(Array<RandomI*> &array);
    virtual void GetRandomsUsed(Array<RandomF*> &array);
private:
};

#endif
