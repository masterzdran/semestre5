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



/*
Sucess Messages
*/
#define THREAD_LOG_SUCCESS				0x20080001 //0010 0000 0000 1000 0000 0000 0000 0001 
/*
Error Messages
*/
#define NULL_POINTER_EXPECTION			0xE0080000 //1110 0000 0000 1000 0000 0000 0000 0000 
#define UNABLE_TLS_ALLOC				0xE0080002 //1110 0000 0000 1000 0000 0000 0000 0010 
#define UNABLE_TLS_FREE					0xE0080004 //1110 0000 0000 1000 0000 0000 0000 0100 
#define UNABLE_TLS_SET_VALUE			0xE0080008 //1110 0000 0000 1000 0000 0000 0000 1000 
#define UNABLE_VIRTUAL_ALLOC			0xE0080010 //1110 0000 0000 1000 0000 0000 0001 0000 
#define UNABLE_VIRTUAL_FREE_DECOMMIT	0xE0080020 //1110 0000 0000 1000 0000 0000 0010 0000 
#define UNABLE_VIRTUAL_FREE_RELEASE		0xE0080040 //1110 0000 0000 1000 0000 0000 0100 0000 
#define INVALID_SIZE_TO_BUFFER			0xE0080080 //1110 0000 0000 1000 0000 0000 1000 0000 
/*
Information Error Messages
*/
#define BUFFER_FULL						0x60080100 //0110 0000 0000 1000 0000 0001 0000 0000 
#define BUFFER_EMPTY					0x60080200 //0110 0000 0000 1000 0000 0010 0000 0000 
#define BUFFER_SIZE_OVERFLOW			0x60080300 //0110 0000 0000 1000 0000 0011 0000 0000 
#define BUFFER_SIZE_EMPTY				0x60080400 //0110 0000 0000 1000 0000 0100 0000 0000 
/*
Warning Erros Messages
*/
#define RESET_THREAD_LOG_INSUCCESS		0xA0080400 //1010 0000 0000 1000 0000 0100 0000 0000 
#define DESTROY_THREAD_LOG_INSUCCESS	0xA0080400 //1010 0000 0000 1000 0000 1000 0000 0000 





#endif