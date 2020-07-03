#include "CSVwriter.hpp"

CSVwriter::CSVwriter(std::string pFileName)
{
	statFile.open(pFileName);

	if (statFile) std::cout << "Found CSV File" << std::endl;
	else std::cout << "Couldn't find file: " << pFileName << std::endl;

}


void CSVwriter::AddFrameTime(int pFrameTime)
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