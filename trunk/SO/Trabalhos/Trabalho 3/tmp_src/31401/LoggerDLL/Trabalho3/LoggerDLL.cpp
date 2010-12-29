#include "LoggeDLL.h"
#include <windows.h>
#include <tchar.h>

static DWORD		_pageLimit	= 0;
static LPVOID		_loggerBase = NULL;
static SYSTEM_INFO	_systemInfo ;
static DWORD		_pageSize	= 0;

void exitReport(LPTSTR message){
	_tprintf(TEXT("Error!\nMessage: %s\nError Code: %ld\n"),message,GetLastError());
	exit(0);
}

/**
 * Uma fun��o para a inicia��o do suporte do registo de hist�rico de informa��o, 
 * da tarefa que invoca a fun��o, onde deve ser recebido a dimens�o m�xima admitida (CreateThreadLog(�)) ; 
 * */
void CreateThreadLog(DWORD bytes){
	if (bytes == 0) 
		exitReport((LPTSTR)"Invalid size to allocate.");

	GetSystemInfo(&_systemInfo);
	_pageSize = _systemInfo.dwPageSize;
	_pageLimit = bytes/_pageSize + 1;
	_loggerBase = VirtualAlloc(NULL , _pageLimit*_pageSize , MEM_RESERVE , PAGE_NOACCESS); 
	if (_loggerBase == NULL)
		exitReport((LPTSTR)"Error while use VirtualAlloc.");
}


/**
 * Uma fun��o para adicionar informa��o ao registo de hist�rico (AppendThreadLog(�)); 
 * */
void AppendThreadLog();

/**
 * Uma fun��o para que permita libertar um bloco de informa��o mais antigo 
 * (segundo a l�gica de um buffer circular), 
 * e.g.  FreeThreadLog(�, nBytes) o que significa que o espa�o dos  nBytes mais antigos � libertado;
 * */
void FreeThreadLog();


/**
 * Uma fun��o para libertar todos os recursos ocupados pelo registo de hist�rico (ResetThreadLog(�)); 
 * */
BOOL ResetThreadLog(){
	return VirtualFree(_loggerBase,_pageLimit * _pageSize, MEM_DECOMMIT);
}

/**
 * Uma fun��o para libertar o suporte do registo de hist�rico (DestroyThreadLog(�)).
 * */
BOOL DestroyThreadLog(){
	return  VirtualFree(_loggerBase, _pageLimit * _pageSize ,MEM_RELEASE);
}
