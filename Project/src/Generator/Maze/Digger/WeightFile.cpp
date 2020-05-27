#include "WeightFile.h"

WeightFile* WeightFile::CreateFromFile(String weightFile, RandomI* randi)
{
	// Try open the file.
	Ifstream file;
    file.open ( weightFile.c_str() );
	if (file.fail())
	{
		std::cout<< "Error opening file " << weightFile << std::endl;
		return NULL;
	}

	// The file has opened correctly. Lets initialise some variables and start reading it.
	WeightFile* wf = new WeightFile();
	String line;

	while( !file.eof())
	{
		// Read the line:
		getline(file, line);

		// Locate the ':'. Ignore this line if it cannot be found.
		int index = (int)line.find_first_of(':');
		if (index == -1 ) continue;

		// Parse the weight:
		int weight = atoi ( line.substr(0, index).c_str() );

		// Add this line's data to the object:
		wf->weights.push_back(weight);
		wf->filenames.push_back(line.substr(index+1, line.length() - index - 1));
	}

	// Pre-Calculate the sum:
	wf->sum = 0;
	for (int i = 0; i < wf->weights.size(); i++)
		wf-> sum += wf->weights[i];

	// Set the random int generator.
	wf->randi = randi;

	file.close();

	return wf;
}

String WeightFile::GetRandomFile()
{
	// Get a random value
	int x = randi->nextInt(1, sum + 1);
	int threshold = 0;

	// Find the smallest threshold greater than (or equal to) x.
	String s = filenames[0];
	for (int i = 0; i < weights.size(); i++)
	{
		threshold += weights[i];
		if (x <= threshold)
		{
			s = filenames[i];
			break;
		}
	}

	return s;
}
