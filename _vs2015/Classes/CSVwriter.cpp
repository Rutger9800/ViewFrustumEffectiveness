#include "CSVwriter.hpp"

CSVwriter::CSVwriter(std::string pFileName)
{
	statFile.open(pFileName);
	//std::locale myLocale("Dutch");

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

	//statFile.imbue(myLocale);
}


void CSVwriter::AddFrameTime(float pFrameTime)
{
	fps = pFrameTime;
	fpsReceived = true;
	if (fpsReceived && objsReceived) sendInfoToFile();
}

void CSVwriter::AddObjInView(int pObjInView)
{
	objInView = pObjInView;
	objsReceived = true;
	if (fpsReceived && objsReceived) sendInfoToFile();
}

void CSVwriter::sendInfoToFile()
{
	fpsReceived = false;
	objsReceived = false;
	statFile << std::to_string(objInView) + ";";
	statFile << std::to_string(fps) << "\n";//frametime gets called later in the frame calculations so this ends the current row
	//std::cout << "SEND INFO TO FILE" << std::endl;
}

CSVwriter::~CSVwriter()
{
	statFile.close();
}