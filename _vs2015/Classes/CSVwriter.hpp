#pragma once
#include <iostream>
#include <fstream>
#include <string>

class CSVwriter
{
public:
	CSVwriter(std::string pFileName);
	~CSVwriter();

	void AddFrameTime(int pFrameTime);
	void AddObjInView(int pObjInView);
private:
	std::ofstream statFile;
};

