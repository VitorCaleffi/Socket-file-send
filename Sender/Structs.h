#pragma once
#include "stdafx.h"

typedef struct
{
	int filesize;
	char filename[64];
	int CRC;
}sHeader;

typedef struct
{
	char pkt[32];
}sPackage;