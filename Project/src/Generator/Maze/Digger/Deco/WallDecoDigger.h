#ifndef WALL_DECO_DIGGER_H_
#define WALL_DECO_DIGGER_H_

#include <platform.h>

#include <Generator/Maze/Maze.h>
#include <Generator/Maze/Digger/Digger.h>
#include <Generator/Maze/Digger/ExternalMeshDigger.h>
#include <Generator/Maze/Digger/WeightFile.h>

class WallDecoDigger
extends Digger
implements ExternalMeshDigger
{
public:
    WallDecoDigger(Maze* maze, RandomI* randomI, RandomF* randomF, float density, String filename);
    ~WallDecoDigger();
    
    virtual void Init();
    virtual bool Step();
    virtual void End();
    
    virtual void GetRandomsUsed(Array<RandomI*> &array);
    virtual void GetRandomsUsed(Array<RandomF*> &array);

private:
	RandomI* randomI;
	RandomF* randomF;
	float density;
	WeightFile* weightFile;

	/**
	 * Put random props on random walls. Only puts a prop on a wall if the wall exists.
	 * The total translation applied on the mesh is given by:
	 *    offset + (mult.x * cell index x, 0, mult.z * cell index z)
	 * @param rot Rotation to apply to the mesh.
	 * @param offset Constant translation to apply to the mesh.
	 * @param mult Translation to apply to the mesh, multipliedby the (x,z) index of the cell.
	 * @param whichWall For each cell, only consider placing a prop if a wall exists at this position.
	 */
	void MakeProps(Quaternion rot, Vector3 offset, Vector3 mult, MazeWallPosition whichWall);
};

#endif
