#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#include "Socket.h"
#include "Structs.h"
#include "FileManager.h"