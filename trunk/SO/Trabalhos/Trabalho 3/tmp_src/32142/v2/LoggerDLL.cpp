#include "LoggerDLL.h"
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "Include\SesError.h"


#define __DEFAULT_SIZE__	1024				//Default Log Size

/*
static DWORD		_pageLimit	= 	0;			//number of pages
static DWORD		_pageNbr	= 	0;			//number of pages allocced
static DWORD		_pageSize	= 	0;			//size of the page
*/

/*
static LPVOID		_loggerBase = 	NULL;		//address of the base virtual alloc
static LPTSTR		_loggerBaseFree = NULL;		//address of the nextpage
static SYSTEM_INFO	_systemInfo ;				//system info 
*/

/*
static LPTSTR		_loggerNextFreeByte	 = NULL;	
static LPTSTR		_loggerNextClearByte = NULL; //address of the oldest byte
*/

DWORD _tlsIDX		= -1;						 //index of last TLS

typedef struct _TlsElements {
	DWORD _pageLimit;							//number of pages
	DWORD _pageNbr;								//number of pages allocced
	DWORD _pageSize;							//size of the page

	DWORD _pageLimit;							//number of pages
	DWORD _pageNbr;								//number of pages allocced
	DWORD _pageSize;    						//size of the page
	
	LPVOID _loggerBase;							//address of the base virtual alloc
	LPTSTR _loggerBaseFree;						//address of the nextpage
	SYSTEM_INFO	_systemInfo;					//system info

	LPTSTR _loggerNextFreeByte;	
	LPTSTR _loggerNextClearByte;				//address of the oldest byte
} TlsElements, * PTlsElements;

//PTlsElements elem;

void exitReport(LPTSTR message){
	_tprintf(TEXT("Error!\nMessage: %s\nError Code: %ld\n"),message,GetLastError());
	exit(0);
}

INT PageFaultExceptionFilter(DWORD dwCode, LPEXCEPTION_POINTERS info, PTlsElements elem){
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
	if (elem->_pageNbr >= elem->_pageLimit){
		printf("Exception: out of pages\n");
		return EXCEPTION_EXECUTE_HANDLER;
	}

	// Otherwise, commit another page.
	LPVOID lpvResult = VirtualAlloc(
						(LPVOID) elem->_loggerBaseFree, // next page to commit
						elem->_pageSize,				  // page size, in bytes
						MEM_COMMIT,				  // allocate a committed page
						PAGE_READWRITE);          // read/write access
	
	if (lpvResult == NULL ){
		printf("VirtualAlloc failed\n");
		return EXCEPTION_EXECUTE_HANDLER;
	}else {
		printf ("Allocating another page.\n");
	}

	// Increment the page count, and advance lpNxtPage to the next page.
	elem->_pageNbr++;
	elem->_loggerBaseFree += elem->_pageSize;

	// Continue execution where the page fault occurred.
	return EXCEPTION_CONTINUE_EXECUTION;
}

BOOL resetValues(PTlsElements elem)
{
	elem->_loggerBaseFree=elem->_loggerNextFreeByte=elem->_loggerNextClearByte =(LPTSTR) elem->_loggerBase;
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

	PTlsElements elem = new TlsElements();

	GetSystemInfo(&elem->_systemInfo);
	elem->_pageSize = elem->_systemInfo.dwPageSize;
	elem->_pageLimit = bytes/elem->_pageSize + 1;
	elem->_loggerBase = VirtualAlloc(NULL , elem->_pageLimit * elem->_pageSize , MEM_RESERVE , PAGE_NOACCESS); 

	if (elem->_loggerBase == NULL)
		exitReport((LPTSTR)"Error while use VirtualAlloc.");
	elem->_loggerBaseFree=elem->_loggerNextFreeByte=elem->_loggerNextClearByte =(LPTSTR) elem->_loggerBase;

	//reservar uma entrada na TLS para que este espaço reservado ser associado a 1 thread
	_tlsIDX = TlsAlloc();
	if(_tlsIDX == -1) FatalErrorSystem(_T("TlsAlloc failed!"));
	if(_tlsIDX == TLS_OUT_OF_INDEXES)
		exitReport((LPTSTR)"Error while use TlsAlloc.");
	if(!TlsSetValue(_tlsIDX, elem))
		FatalErrorSystem(_T("TlsSetValue failed!"));
}


/**
 * Uma função para adicionar informação ao registo de histórico (AppendThreadLog(…)); 
 * */
void AppendThreadLog(LPTSTR message){
	if(_tlsIDX == -1)
		exitReport((LPTSTR)"Error index -1.");
	PTlsElements elem = (PTlsElements) TlsGetValue(_tlsIDX);
	if (elem->_loggerBase == NULL)
		CreateThreadLog(__DEFAULT_SIZE__);

	DWORD size = _tcsclen(message);
	//Usar controlo de excepções
	//Usar memcopy para copiar a mensagem para o endereço de _loggerBaseFree
	//Se falhar a excepção chamar a função que vai fazer commit da proxima pagina 
	//ou paginas suficientes para agregar as páginas
	//Actualizar o valor de _loggerBaseFree para o proximo byte apos ter sido colocada a mensagem

	__try
	{
		memccpy(elem->_loggerNextFreeByte,message,0,size);
		elem->_loggerNextFreeByte += size;
	}
	__except ( PageFaultExceptionFilter( GetExceptionCode() , GetExceptionInformation() , elem) )
	{
	}

	if(!TlsSetValue(_tlsIDX, elem))
		FatalErrorSystem(_T("TlsSetValue failed!"));
}

/**
 * Uma função para que permita libertar um bloco de informação mais antigo 
 * (segundo a lógica de um buffer circular), 
 * e.g.  FreeThreadLog(…, nBytes) o que significa que o espaço dos  nBytes mais antigos é libertado;
 * 1ª versão libertar só espaço não havendo preocupação com as págians commit
 * 2ª versão fazer uncommit das respectivas páginas mas tendo o cuidado de apenas fazer uncommit de páginas 
 * que estejam totalmente “vazias”.
 * */
//MEM_DECOMMIT -> memoria é libertada 
void FreeThreadLog(DWORD bytes){
	if (bytes == 0 ) return;
	if(_tlsIDX == -1) exitReport((LPTSTR)"Error index -1.");
	PTlsElements elem = (PTlsElements) TlsGetValue(_tlsIDX);
	//VirtualFree: para libertar os bytes indicados
	//se a pagina estiver toda disponivel fazer release
	//controlar o espaço com buffer circular

	//remain indica se ainda existem bytes por ocupar no logger, se sim entao remain == 0,
	//caso contrario em remain ficam o numero de bytes que estao em excesso
	int remain = ((elem->_loggerNextClearByte+bytes)>=((LPTSTR)elem->_loggerBase + elem->_pageLimit*elem->_pageSize))?
				((LPTSTR)elem->_loggerBase + elem->_pageLimit*elem->_pageSize) - (elem->_loggerNextClearByte+bytes):0;
	BOOL freeLog = VirtualFree(elem->_loggerNextClearByte,bytes - remain ,MEM_DECOMMIT);
	//se foi libertada memoria
	if(freeLog){
		//se existem bytes ainda a libertar
		if (remain){
			freeLog = VirtualFree(elem->_loggerBase,remain ,MEM_DECOMMIT);
			//se a memoria foi libertada com sucesso
			if(freeLog)//actualizar _loggerNextClearByte
				elem->_loggerNextClearByte=(LPTSTR)elem->_loggerBase + remain;
		}else{//actualizaçao de bytes
			elem->_loggerNextClearByte += bytes;
			if (elem->_loggerNextClearByte == (LPTSTR)elem->_loggerBase + elem->_pageLimit*elem->_pageSize)
				elem->_loggerNextClearByte = (LPTSTR)elem->_loggerBase;
		}
	}
	//guardar novos valores da estrutura na TLS
	if(!TlsSetValue(_tlsIDX, elem))
		FatalErrorSystem(_T("TlsSetValue failed!"));
}


/**
 * Uma função para libertar todos os recursos ocupados pelo registo de histórico (ResetThreadLog(…));
 * ResetThreadLog é colocar o log no estado inicial (quando termina a função CreateThreadLog),
 * ou seja no seu caso ter apenas a região reservada. 
 * */
BOOL ResetThreadLog(){
	if(_tlsIDX == -1) exitReport((LPTSTR)"Error index -1.");
	PTlsElements elem = (PTlsElements) TlsGetValue(_tlsIDX);
	return (VirtualFree(elem->_loggerBase,elem->_pageLimit * elem->_pageSize, MEM_DECOMMIT))?resetValues(elem):false;
}

/**
 * Uma função para libertar o suporte do registo de histórico (DestroyThreadLog(…)).
 * DestroyThreadLog deve eliminar totalmente o log
 * */
BOOL DestroyThreadLog(){
	if(_tlsIDX == -1) exitReport((LPTSTR)"Error index -1.");
	PTlsElements elem = (PTlsElements) TlsGetValue(_tlsIDX);
	return  VirtualFree(elem->_loggerBase, elem->_pageLimit * elem->_pageSize ,MEM_RELEASE);
}
