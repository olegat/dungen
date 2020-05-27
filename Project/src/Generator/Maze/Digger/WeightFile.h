#ifndef WEIGHT_FILE_H_
#define WEIGHT_FILE_H_

#include <platform.h>
#include <Generator/Random/Random.h>

class WeightFile
extends Object
{
public:
	static WeightFile* CreateFromFile(String weightFile, RandomI* randi);
	String GetRandomFile();

private:
	int sum;
	Array<int> weights;
	Array<String> filenames;
	RandomI* randi;
};

#endif
