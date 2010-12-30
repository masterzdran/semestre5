#include "LoggeDLL.h"
#include <windows.h>
#include <tchar.h>

static DWORD		_pageLimit	= 	0;
static LPVOID		_loggerBase = 	NULL;
static SYSTEM_INFO	_systemInfo ;
static DWORD		_pageSize	= 	0;
stacic LPVOID		_loggerBaseFree = NULL;

static DWORD		_nextToBeFreed	=	0;
static DWORD		_nextToBeAlloc	=	0;


#define __DEFAULT_SIZE__	1024

void exitReport(LPTSTR message){
	_tprintf(TEXT("Error!\nMessage: %s\nError Code: %ld\n"),message,GetLastError());
	exit(0);
}

DWORD tlsIDX	= -1;

static void _DLL_TlsInit()
{
    if ((tlsIDX = TlsAlloc()) == -1)  
      FatalErrorSystem(_T("TlsAlloc failed!"));
}

static void _DLL_TlsEnd()
{
	if( tlsIDX != -1)
		if( !TlsFree(indxRnd) ) 
            FatalErrorSystem(_T("TlsFree failed!"));
}

static DWORD* _TlsInit()
{
	int *p = new int[1];  
	*p = 1;
	if (! TlsSetValue(tlsIDX, p)) 
        FatalErrorSystem(_T("TlsSetValue failed!")); 
	return p;
}

static void _TlsClose()
{
	int* p = (int*)TlsGetValue(tlsIDX); 
	if ( p ) { 
		delete p; 
		p=NULL;
		if ( !TlsSetValue(tlsIDX, p) ) 
            FatalErrorSystem(_T("TlsSetValue failed!")); 
	}
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
	_loggerBase = VirtualAlloc(NULL , _pageLimit * _pageSize , MEM_RESERVE , PAGE_NOACCESS); 
	if (_loggerBase == NULL)
		exitReport((LPTSTR)"Error while use VirtualAlloc.");
	
	_loggerBaseFree = _loggerBase;
}


/**
 * Uma fun��o para adicionar informa��o ao registo de hist�rico (AppendThreadLog(�)); 
 * */
void AppendThreadLog(LPTSTR message){
	if (_loggerBase == NULL)
		CreateThreadLog(__DEFAULT_SIZE__);

	DWORD size = sizeof(message);
	//Usar controlo de excep��es
	//Usar memcopy para copiar a mensagem para o endere�o de _loggerBaseFree
	//Se falhar a excep��o chamar a fun��o que vai fazer commit da proxima pagina 
	//ou paginas suficientes para agregar as p�ginas
	//Actualizar o valor de _loggerBaseFree para o proximo byte apos ter sido colocada a mensagem


}

/**
 * Uma fun��o para que permita libertar um bloco de informa��o mais antigo 
 * (segundo a l�gica de um buffer circular), 
 * e.g.  FreeThreadLog(�, nBytes) o que significa que o espa�o dos  nBytes mais antigos � libertado;
 * */
void FreeThreadLog(DWORD bytes);


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
