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
	float fps = 0.0f;
	int objInView = 0;
	bool fpsReceived = false, objsReceived = false;

	void sendInfoToFile();

};

