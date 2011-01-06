#ifndef _LOGGERDLL_H_
#define _LOGGERDLL_H_

void CreateThreadLog(DWORD bytes);
void AppendThreadLog(LPTSTR message);
void FreeThreadLog(DWORD bytes);
BOOL ResetThreadLog();
BOOL DestroyThreadLog();
#endif