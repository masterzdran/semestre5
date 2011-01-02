#include "LoggerDLL.h"
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "Include\SesError.h"


#define __DEFAULT_SIZE__	1024				//Default Log Size

static DWORD		_pageLimit	= 	0;			//number of pages
static DWORD		_pageNbr	= 	0;			//number of pages allocced
static DWORD		_pageSize	= 	0;			//size of the page

static LPVOID		_loggerBase = 	NULL;		//address of the base virtual alloc
static LPTSTR		_loggerBaseFree = NULL;		//address of the nextpage
static SYSTEM_INFO	_systemInfo ;				//system info

static LPTSTR		_loggerNextFreeByte	 = NULL;	
static LPTSTR		_loggerNextClearByte = NULL; //address of the oldest byte
DWORD tlsIDX		= -1;



void exitReport(LPTSTR message){
	_tprintf(TEXT("Error!\nMessage: %s\nError Code: %ld\n"),message,GetLastError());
	exit(0);
}

INT PageFaultExceptionFilter(DWORD dwCode, LPEXCEPTION_POINTERS info){
	// If the exception is not a page fault, exit.
	if (dwCode != EXCEPTION_ACCESS_VIOLATION){
		printf("Exception code = %d\n", dwCode);
		return EXCEPTION_EXECUTE_HANDLER;
	}

	//PEXCEPTION_RECORD pErec = info->ExceptionRecord;
	//unsigned long* Einfo = pErec->ExceptionInformation;
	//printf("Exception is a page fault: ProgAddress=%x DataAddress=%x Access = %s \n",
	//	(UINT_PTR)pErec->ExceptionAddress, Einfo[1], Einfo[0]==0 ? "Read":"Write" );

	// If the reserved pages are used up, exit.
	if (_pageNbr >= _pageLimit){
		printf("Exception: out of pages\n");
		return EXCEPTION_EXECUTE_HANDLER;
	}

	// Otherwise, commit another page.
	LPVOID lpvResult = VirtualAlloc(
						(LPVOID) _loggerBaseFree, // next page to commit
						_pageSize,				  // page size, in bytes
						MEM_COMMIT,				  // allocate a committed page
						PAGE_READWRITE);          // read/write access
	
	if (lpvResult == NULL ){
		printf("VirtualAlloc failed\n");
		return EXCEPTION_EXECUTE_HANDLER;
	}else {
		printf ("Allocating another page.\n");
	}

	// Increment the page count, and advance lpNxtPage to the next page.
	_pageNbr++;
	_loggerBaseFree += _pageSize;

	// Continue execution where the page fault occurred.
	return EXCEPTION_CONTINUE_EXECUTION;
}

BOOL resetValues()
{
	_loggerBaseFree=_loggerNextFreeByte=_loggerNextClearByte =(LPTSTR) _loggerBase;
	return true;
}
//
//static void _DLL_TlsInit()
//{
//    if ((tlsIDX = TlsAlloc()) == -1)  
//      FatalErrorSystem(_T("TlsAlloc failed!"));
//}
//
//static void _DLL_TlsEnd()
//{
//	if( tlsIDX != -1)
//		if( !TlsFree(tlsIDX) ) 
//            FatalErrorSystem(_T("TlsFree failed!"));
//}
//
//static INT* _TlsInit()
//{
//	int *p = new int[1];  
//	*p = 1;
//	if (! TlsSetValue(tlsIDX, p)) 
//        FatalErrorSystem(_T("TlsSetValue failed!")); 
//	return p;
//}
//
//static void _TlsClose()
//{
//	int* p = (int*)TlsGetValue(tlsIDX); 
//	if ( p ) { 
//		delete p; 
//		p=NULL;
//		if ( !TlsSetValue(tlsIDX, p) ) 
//            FatalErrorSystem(_T("TlsSetValue failed!")); 
//	}
//}
//


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
	
	_loggerBaseFree=_loggerNextFreeByte=_loggerNextClearByte =(LPTSTR) _loggerBase;
}


/**
 * Uma função para adicionar informação ao registo de histórico (AppendThreadLog(…)); 
 * */
void AppendThreadLog(LPTSTR message){
	if (_loggerBase == NULL)
		CreateThreadLog(__DEFAULT_SIZE__);

	DWORD size = _tcsclen(message);
	//Usar controlo de excepções
	//Usar memcopy para copiar a mensagem para o endereço de _loggerBaseFree
	//Se falhar a excepção chamar a função que vai fazer commit da proxima pagina 
	//ou paginas suficientes para agregar as páginas
	//Actualizar o valor de _loggerBaseFree para o proximo byte apos ter sido colocada a mensagem

	__try
	{
		memccpy(_loggerNextFreeByte,message,0,size);
		_loggerNextFreeByte += size;
	}
	__except ( PageFaultExceptionFilter( GetExceptionCode(),GetExceptionInformation() ) )
	{
	}
}

/**
 * Uma função para que permita libertar um bloco de informação mais antigo 
 * (segundo a lógica de um buffer circular), 
 * e.g.  FreeThreadLog(…, nBytes) o que significa que o espaço dos  nBytes mais antigos é libertado;
 * 1ª versão libertar só espaço não havendo preocupação com as págians commit
 * 2ª versão fazer uncommit das respectivas páginas mas tendo o cuidado de apenas fazer uncommit de páginas 
 * que estejam totalmente “vazias”.
 * */
void FreeThreadLog(DWORD bytes){
	if (bytes == 0 ) return;
	//VirtualFree: para libertar os bytes indicados
	//se a pagina estiver toda disponivel fazer release
	//controlar o espaço com buffer circular
	int remain = ((_loggerNextClearByte+bytes)>=((LPTSTR)_loggerBase + _pageLimit*_pageSize))?((LPTSTR)_loggerBase + _pageLimit*_pageSize) - (_loggerNextClearByte+bytes):0;
	BOOL freeLog = VirtualFree(_loggerNextClearByte,bytes - remain ,MEM_DECOMMIT);
	if(freeLog){
		if (remain){
			freeLog = VirtualFree(_loggerBase,remain ,MEM_DECOMMIT);
			if(freeLog)
				_loggerNextClearByte=(LPTSTR)_loggerBase + remain;
		}else{
			_loggerNextClearByte += bytes;
			if (_loggerNextClearByte == (LPTSTR)_loggerBase + _pageLimit*_pageSize)
				_loggerNextClearByte = (LPTSTR)_loggerBase;
		}
	}
}


/**
 * Uma função para libertar todos os recursos ocupados pelo registo de histórico (ResetThreadLog(…)); 
 * */
BOOL ResetThreadLog(){
	return (VirtualFree(_loggerBase,_pageLimit * _pageSize, MEM_DECOMMIT))?resetValues():false;
}

/**
 * Uma função para libertar o suporte do registo de histórico (DestroyThreadLog(…)).
 * */
BOOL DestroyThreadLog(){

	return  VirtualFree(_loggerBase, _pageLimit * _pageSize ,MEM_RELEASE);
}
