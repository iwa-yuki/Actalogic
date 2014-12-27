#pragma once

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <math.h>
#include <assert.h>

#include <d2d1.h>

#include <chrono>

#pragma comment(lib, "d2d1.lib")

#define CHRONO_SYSTEM_TIME std::chrono::time_point<std::chrono::system_clock, std::chrono::system_clock::duration >

