#include "CSVwriter.hpp"

CSVwriter::CSVwriter(std::string pFileName)
{
	statFile.open(pFileName);
	std::locale myLocale("");

	if (statFile)
	{
		std::cout << "Found CSV File" << std::endl;
		statFile << "Objects in View; FPS\n";
	}
	else 
	{
		std::cout << "Couldn't open file: " << pFileName << " -- Creating new file" << std::endl;
		std::ofstream statFile(pFileName + "new.csv");
	}

	statFile.imbue(myLocale);
}


void CSVwriter::AddFrameTime(float pFrameTime)
{
	statFile << std::to_string(pFrameTime) << "\n";//frametime gets called later in the frame calculations so this ends the current row
}

void CSVwriter::AddObjInView(int pObjInView)
{
	statFile << std::to_string(pObjInView) + ";";
}

CSVwriter::~CSVwriter()
{
	statFile.close();
}