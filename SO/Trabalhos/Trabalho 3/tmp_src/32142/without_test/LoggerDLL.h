#ifndef _LOGGER_DLL_H_
#define _LOGGER_DLL_H_

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "Include\SesError.h"

void WINAPI CreateThreadLog(DWORD bytes);
void WINAPI AppendThreadLog(LPTSTR message);
void WINAPI FreeThreadLog(DWORD bytes);
BOOL WINAPI ResetThreadLog();
BOOL WINAPI DestroyThreadLog();

#endif