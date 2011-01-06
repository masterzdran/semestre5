#ifndef _LOGGERDLL_H_
#define _LOGGERDLL_H_

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "Include\SesError.h"

void CreateThreadLog(DWORD bytes);
void AppendThreadLog(LPTSTR message);
void FreeThreadLog(DWORD bytes);
BOOL ResetThreadLog();
BOOL DestroyThreadLog();

#endif