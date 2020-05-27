#include "WallDecoDigger.h"

#include <Engine/Tools/Math.h> // just for PI.

WallDecoDigger::WallDecoDigger(Maze* maze, RandomI* randomI, RandomF* randomF, float density, String filename) : Digger(maze)
{
	this->weightFile = WeightFile::CreateFromFile(filename, randomI);
	this->randomI = randomI;
	this->randomF = randomF;
	this->density = density;
	assert ( density>=0 && density <= 1);
}

WallDecoDigger::~WallDecoDigger()
{
}
    
void WallDecoDigger::Init()
{
}

bool WallDecoDigger::Step()
{
	if (weightFile == NULL)
	{
		std::cout << "WallDecoDigger:: Error. weightFile is NULL." << std::endl;
		return true;
	}

	// For each prop facing the front.
	MakeProps(Quaternion(Vector3(0)), Vector3(0.5f, 0, 0), Vector3(1, 0, 1), MAZE_WALLPOS_UP);

	// For each prop facing the left.
	MakeProps(Quaternion(Vector3(0, -PI / 2.0f, 0)), Vector3(0, 0, 0.5f), Vector3(1, 0, 1), MAZE_WALLPOS_LEFT);

	// For each prop facing the right.
	MakeProps(Quaternion(Vector3(0, PI / 2.0f, 0)), Vector3(1, 0, 0.5f), Vector3(1, 0, 1), MAZE_WALLPOS_RIGHT);

	// For each prop facing the back.
	MakeProps(Quaternion(Vector3(0, PI, 0)), Vector3(0.5f, 0, 1), Vector3(1, 0, 1), MAZE_WALLPOS_DOWN);

	return true;
}

void WallDecoDigger::MakeProps(Quaternion rot, Vector3 offset, Vector3 mult, MazeWallPosition whichWall)
{
	int x, z;
	int W = maze->Width(), L = maze->Length();

	// For each cell:
	for (x = 0; x < W; x++)
	for (z = 0; z < L; z++)
	{
		MazeCell* cell = maze->GetCell(x, z);

		if (   maze->GetWallCount(cell) != 4                                      // Is this cell accessible?
			&& maze->GetWall(x, z, whichWall)->GetType() == MAZE_WALLTYPE_DEFAULT // Does this wall exist?
			&& randomF->nextFloat(0, 1) <= density ) // Dice roll to see whether or not to decorate this wall.
		{
			// Add a random decoration item:
			String item = weightFile->GetRandomFile();

			// Calculate the center of the wall's base.
			Vector3 center = offset;
			center += Vector3(mult.x * x, 0, mult.z * z);

			// Add this item
			this->AddExternalMesh(item, center, rot);
		}
	}
}

void WallDecoDigger::End()
{
}
    
void WallDecoDigger::GetRandomsUsed(Array<RandomI*> &array)
{
	array.push_back(randomI);
}

void WallDecoDigger::GetRandomsUsed(Array<RandomF*> &array)
{
	array.push_back(randomF);
}
