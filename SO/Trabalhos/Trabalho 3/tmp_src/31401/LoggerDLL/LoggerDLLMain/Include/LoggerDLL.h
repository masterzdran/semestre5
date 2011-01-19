#ifndef _LOGGERDLL_H_
#define _LOGGERDLL_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <windows.h>

#define EXPORT __declspec (dllexport)
#define IMPORT __declspec (dllimport)


#ifdef loggerdll_build
#define __TAG__ EXPORT
#else
#define __TAG__ IMPORT
#endif //loggerdll_build

__TAG__ void WINAPI CreateThreadLog(DWORD bytes);
__TAG__ void WINAPI AppendThreadLog(LPTSTR message);
__TAG__ void WINAPI FreeThreadLog(DWORD bytes);
__TAG__ BOOL WINAPI ResetThreadLog();
__TAG__ BOOL WINAPI DestroyThreadLog();


//Definições para carregamento explícito com a função LoadLibray:
typedef void (WINAPI *TpCreateThreadLog)(DWORD bytes);
typedef void (WINAPI *TpAppendThreadLog)(LPTSTR message);
typedef void (WINAPI *TpFreeThreadLog)(DWORD bytes);
typedef BOOL (WINAPI *TpResetThreadLog)();
typedef BOOL (WINAPI *TpDestroyThreadLog)();


#ifdef __cplusplus
} //extern "C" {
#endif // __cplusplus








#endif