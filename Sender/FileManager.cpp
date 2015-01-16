#include "stdafx.h"

bool CFileManager::ReadData(char *Dest)
{
	Dest = (char *)malloc(this->fileSize);

	std::ifstream::pos_type pos = fileSize;
	std::vector<char>  result(pos);

	fileHnd.seekg(0, std::ios::beg);
	fileHnd.read(Dest, pos);

	return true;
}

void CFileManager::GetInformation(sHeader &Dest)
{
	Dest.filesize = fileSize;
}

CFileManager::CFileManager(char const* filename)
{
	std::ifstream fileHnd(filename, std::ios::binary | std::ios::ate);
	this->fileSize = fileHnd.tellg();
}


CFileManager::~CFileManager()
{
}
