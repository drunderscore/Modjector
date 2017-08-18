#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#else
#error Windows is required to build this DLL.
#endif