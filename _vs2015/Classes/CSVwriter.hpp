#pragma once
#include <iostream>
#include <fstream>
#include <string>
std::locale;

class CSVwriter
{
public:
	CSVwriter(std::string pFileName);
	~CSVwriter();
	void AddFrameTime(float pFrameTime);
	void AddObjInView(int pObjInView);
private:
	std::ofstream statFile;
};

