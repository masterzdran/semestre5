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
 * Uma função para a iniciação do suporte do registo de histórico de informação, 
 * da tarefa que invoca a função, onde deve ser recebido a dimensão máxima admitida (CreateThreadLog(…)) ; 
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
 * Uma função para adicionar informação ao registo de histórico (AppendThreadLog(…)); 
 * */
void AppendThreadLog(LPTSTR message){
	if (_loggerBase == NULL)
		CreateThreadLog(__DEFAULT_SIZE__);

	DWORD size = sizeof(message);
	//Usar controlo de excepções
	//Usar memcopy para copiar a mensagem para o endereço de _loggerBaseFree
	//Se falhar a excepção chamar a função que vai fazer commit da proxima pagina 
	//ou paginas suficientes para agregar as páginas
	//Actualizar o valor de _loggerBaseFree para o proximo byte apos ter sido colocada a mensagem


}

/**
 * Uma função para que permita libertar um bloco de informação mais antigo 
 * (segundo a lógica de um buffer circular), 
 * e.g.  FreeThreadLog(…, nBytes) o que significa que o espaço dos  nBytes mais antigos é libertado;
 * */
void FreeThreadLog(DWORD bytes);


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
