#pragma once

#define _CRTDBG_MAP_ALLOC

#include <windows.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <string.h>
#include <tchar.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include <d2d1_1.h>
#include <dwrite_1.h>
#include <wincodec.h>

#include <chrono>
#include <unordered_map>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

#define CHRONO_SYSTEM_TIME std::chrono::time_point<std::chrono::system_clock, std::chrono::system_clock::duration >

typedef std::basic_string<TCHAR> tstring;

