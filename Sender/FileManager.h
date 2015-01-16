#pragma once
#include "stdafx.h"

class CFileManager
{
private:
	int fileSize;
	char * FileName;
	int CRC;
	std::ifstream fileHnd;
public:
	bool ReadData(char *Dest);
	void GetInformation(sHeader &Dest);

	CFileManager(char const* filename);
	~CFileManager();
};

