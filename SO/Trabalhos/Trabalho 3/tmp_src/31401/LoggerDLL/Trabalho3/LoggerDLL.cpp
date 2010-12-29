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
 * Uma função para a iniciação do suporte do registo de histórico de informação, 
 * da tarefa que invoca a função, onde deve ser recebido a dimensão máxima admitida (CreateThreadLog(…)) ; 
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
 * Uma função para adicionar informação ao registo de histórico (AppendThreadLog(…)); 
 * */
void AppendThreadLog();

/**
 * Uma função para que permita libertar um bloco de informação mais antigo 
 * (segundo a lógica de um buffer circular), 
 * e.g.  FreeThreadLog(…, nBytes) o que significa que o espaço dos  nBytes mais antigos é libertado;
 * */
void FreeThreadLog();


/**
 * Uma função para libertar todos os recursos ocupados pelo registo de histórico (ResetThreadLog(…)); 
 * */
BOOL ResetThreadLog(){
	return VirtualFree(_loggerBase,_pageLimit * _pageSize, MEM_DECOMMIT);
}

/**
 * Uma função para libertar o suporte do registo de histórico (DestroyThreadLog(…)).
 * */
BOOL DestroyThreadLog(){
	return  VirtualFree(_loggerBase, _pageLimit * _pageSize ,MEM_RELEASE);
}
