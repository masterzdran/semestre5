#define loggerdll_build

#include "LoggerDLL.h"
#include <tchar.h>
#include <stdio.h>
#include <locale.h>
#include "Include\SesError.h"

typedef struct{
	DWORD	_pageLimit;
	DWORD	_pageNbr;
	DWORD	_pageSize;
	LPVOID	_loggerBase;
	DWORD	_startPtr;
	DWORD	_endPtr;


}LogDef;

#define __DEFAULT_SIZE__	1024				//Default Log Size
/*
	static DWORD		_pageLimit	= 	0;			//number of pages
	static DWORD		_pageNbr	= 	0;			//number of pages allocced
	static DWORD		_pageSize	= 	0;			//size of the page
	static LPVOID		_loggerBase = 	NULL;		//address of the base virtual alloc
	static LPTSTR		_loggerBaseFree = NULL;		//address of the nextpage
	static LPTSTR		_loggerNextFreeByte	 = NULL;	
	static LPTSTR		_loggerNextClearByte = NULL; //address of the oldest byte
*/
//TLS Entry
DWORD tlsIDX		= -1;

//Routine to Treat The exption and 
INT PageFaultExceptionFilter(DWORD dwCode, LPEXCEPTION_POINTERS info){
	// If the exception is not a page fault, exit.
	if (dwCode != EXCEPTION_ACCESS_VIOLATION){
		printf("Exception code = %d\n", dwCode);
		return EXCEPTION_EXECUTE_HANDLER;
	}
	// If the reserved pages are used up, exit.
	LogDef* logger = (LogDef*)TlsGetValue(tlsIDX);
	if (logger->_pageNbr >= logger->_pageLimit){
		printf("Exception: out of pages\n");
		return EXCEPTION_EXECUTE_HANDLER;
	}

	// Otherwise, commit another page.
	LPVOID lpvResult = VirtualAlloc(
						logger->_loggerBase, // next page to commit
						logger-> _pageSize,  // page size, in bytes
						MEM_COMMIT,			 // allocate a committed page
						PAGE_READWRITE);    // read/write access
	
	if (lpvResult == NULL ){
		printf("VirtualAlloc failed\n");
		return EXCEPTION_EXECUTE_HANDLER;
	}else {
		printf ("Allocating another page.\n");
	}

	// Increment the page count
	logger->_pageNbr++;

	// Continue execution where the page fault occurred.
	return EXCEPTION_CONTINUE_EXECUTION;
}

VOID resetValues()
{
	LogDef* logger = (LogDef*)TlsGetValue(tlsIDX);
	logger->_endPtr = logger->_startPtr = 0;
}

static void _DLL_TlsInit()
{
    if ((tlsIDX = TlsAlloc()) == -1)  
		RaiseException(UNABLE_TLS_ALLOC,0,0,NULL);
}

static void _DLL_TlsEnd()
{
	if( tlsIDX != -1)
		if( !TlsFree(tlsIDX) ) 
			RaiseException(UNABLE_TLS_FREE,0,0,NULL);
}

static LogDef* _TlsInit()
{
	LogDef* p = new LogDef[1];  
	p->_endPtr = p->_startPtr = p->_pageNbr = 0;
	p->_pageLimit = p->_pageSize = 0 ;
	p->_loggerBase = 0;

	if (! TlsSetValue(tlsIDX, p)) 
        RaiseException(UNABLE_TLS_SET_VALUE,0,0,NULL);
	return p;
}

static void _TlsClose()
{
	LogDef* p = (LogDef*)TlsGetValue(tlsIDX); 
	if ( p ) { 
		delete p; 
		p=NULL;
		if ( !TlsSetValue(tlsIDX, p) ) 
            RaiseException(UNABLE_TLS_SET_VALUE,0,0,NULL);
	}
}

static BOOL isEmpty(){
	LogDef* values = (LogDef*)TlsGetValue(tlsIDX);
	return (values->_startPtr == values->_endPtr);
}

static BOOL isFull(){
	LogDef* values = (LogDef*)TlsGetValue(tlsIDX);
	return (values->_endPtr+1 == values->_startPtr);
}

/**
 * Uma função para a iniciação do suporte do registo de histórico de informação, 
 * da tarefa que invoca a função, onde deve ser recebido a dimensão máxima admitida (CreateThreadLog(…)) ; 
 * */
void WINAPI CreateThreadLog(DWORD bytes){
	if (bytes == 0) 
		RaiseException(INVALID_SIZE_TO_BUFFER,0,0,NULL);
	
	LogDef* logger = (LogDef*)TlsGetValue(tlsIDX);
	SYSTEM_INFO	systemInfo ; GetSystemInfo(&systemInfo);

	logger->_pageSize = systemInfo.dwPageSize;
	logger->_pageLimit = bytes/logger->_pageSize + 1;
	logger->_loggerBase = VirtualAlloc(NULL , logger->_pageLimit * logger->_pageSize , MEM_RESERVE , PAGE_NOACCESS); 

	if (logger->_loggerBase == NULL)
		RaiseException(UNABLE_VIRTUAL_ALLOC,0,0,NULL);
	
	//Reseting	the buffer pointers, acknowledging the buffer is empty at start. 
	logger->_endPtr = logger->_startPtr = logger->_pageNbr = 0;
}


/**
 * Uma função para adicionar informação ao registo de histórico (AppendThreadLog(…)); 
 * */
void WINAPI AppendThreadLog(LPTSTR message){
	
	if (message == NULL) RaiseException(NULL_POINTER_EXPECTION,0,0,NULL);
	
	LogDef* logger = (LogDef*)TlsGetValue(tlsIDX);
	if (logger->_loggerBase == NULL)
		CreateThreadLog(__DEFAULT_SIZE__);

	DWORD size = _tcsclen(message);
	//Usar controlo de excepções
	//Usar memcopy para copiar a mensagem para o endereço de _loggerBaseFree
	//Se falhar a excepção chamar a função que vai fazer commit da proxima pagina 
	//ou paginas suficientes para agregar as páginas
	//Actualizar o valor de _loggerBaseFree para o proximo byte apos ter sido colocada a mensagem
	if (isFull()) RaiseException(BUFFER_FULL,0,0,NULL);
	
	__try
	{

		_memccpy((LPVOID)( (int)logger->_loggerBase + (logger->_endPtr)),message,0,size);
		logger->_endPtr =  (logger->_endPtr + size)%(logger->_pageSize * logger->_pageLimit);
	}
	__except ( PageFaultExceptionFilter( GetExceptionCode(),GetExceptionInformation() ) )
	{
		//one more page commited
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
void WINAPI FreeThreadLog(DWORD bytes){
	if (bytes == 0 ) RaiseException(BUFFER_SIZE_EMPTY,0,0,NULL);

	//VirtualFree: para libertar os bytes indicados
	//se a pagina estiver toda disponivel fazer release
	//controlar o espaço com buffer circular
	//Admitindo que bytes é sempre inferior ao total do buffer

	if (isEmpty()) RaiseException(BUFFER_EMPTY,0,0,NULL);

	LogDef* logger = (LogDef*)TlsGetValue(tlsIDX);

	if (bytes > (logger->_pageLimit * logger->_pageSize)) 
		RaiseException(BUFFER_SIZE_OVERFLOW,0,0,NULL);
	
	//Relallocating the pointers
	DWORD releasedPtr =  (bytes +  logger->_startPtr) % (logger->_pageLimit * logger->_pageSize); 

	//if start pointer is greater than end pointer, is beacause the end pointer has flipped in the circular buffer
	if (logger->_startPtr > logger->_endPtr){ 
		//if the future pointer is less than the start pointer is because the size in bytes is greater than the allocated space.
		//Realocation of the pointer
		if (releasedPtr < logger->_startPtr) 
			releasedPtr = logger->_endPtr;
	}else{
		//if future pointer is greater than end pointer or lesser than the start pointer
		//reallocate the pointer
		if (releasedPtr > logger->_endPtr || releasedPtr < logger->_startPtr)
			releasedPtr = logger->_endPtr;
	}

	//Decommiting the space.
	DWORD startPageIdx = logger->_startPtr / logger->_pageSize;
	DWORD endPageIdx = releasedPtr / logger->_pageSize;


	if (startPageIdx != endPageIdx){
		BOOL freeLog;
		LPVOID freeAddr = logger->_loggerBase;
		for (;startPageIdx < endPageIdx; ((startPageIdx++)%(logger->_pageLimit))){
			freeAddr =(LPVOID)( (int)logger->_loggerBase + startPageIdx * logger->_pageSize);
			freeLog = VirtualFree(freeAddr, 2 ,MEM_DECOMMIT);
			
			if (!freeLog){
				_tprintf(TEXT("Error while decommiting: %d"),GetLastError());
				RaiseException(RESET_THREAD_LOG_INSUCCESS,0,0,NULL);
			}else{
				logger->_pageNbr--;
			}
		}
	}
}


/**
 * Uma função para libertar todos os recursos ocupados pelo registo de histórico (ResetThreadLog(…)); 
 * */
BOOL WINAPI ResetThreadLog(){
	LogDef* logger = (LogDef*)TlsGetValue(tlsIDX);
	if (!VirtualFree(logger->_loggerBase,0, MEM_DECOMMIT))
		RaiseException(RESET_THREAD_LOG_INSUCCESS,0,0,NULL);
	resetValues();
	return TRUE;
}

/**
 * Uma função para libertar o suporte do registo de histórico (DestroyThreadLog(…)).
 * */
BOOL WINAPI DestroyThreadLog(){
	LogDef* logger = (LogDef*)TlsGetValue(tlsIDX);
	if (!VirtualFree((logger->_loggerBase), 0 ,MEM_RELEASE))
		RaiseException(DESTROY_THREAD_LOG_INSUCCESS,0,0,NULL);
	return  TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// Função DllMain ///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved )
{
    BOOL Result = TRUE;
     
    _tsetlocale(LC_ALL, _T("portuguese_portugal"));

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            // A DDL está a ser mapeada no espaço de endereçamento do processo
            _tprintf(_T("LoggerDLL.dll: A DDL está a ser mapeada no espaço de endereçamento do processo\n"));
            _tprintf(_T("0x%p\n"), hinstDLL);
            if ((tlsIDX = TlsAlloc()) == -1) { 
                Result = FALSE; break;
            }
            //Atribuir espaço na entrada do thread corrente
            Result = _TlsInit() != NULL;
            break;

        case DLL_THREAD_ATTACH:
            // Está a ser criada uma thread
            _tprintf(_T("LoggerDLL.dll: Está a ser criada uma thread\n"));
            //Atribuir espaço na entrada TLS do thread corrente
            _TlsInit();
            break;

        case DLL_THREAD_DETACH:
            // Existe uma thread a terminar (sem ser através do TerminateThread
            _tprintf(_T("LoggerDLL.dll: Existe uma thread a terminar (sem ser através do TerminateThread)\n"));
            //Libertar espaço ocupado pelo thread na entrada TLS
            _TlsClose();
            break;

        case DLL_PROCESS_DETACH:
            // A DLL está a ser desmapeada do espaço de endereçamento do processo
            _tprintf(_T("LoggerDLL.dll: A DLL está a ser desmapeada do espaço de endereçamento do processo\n"));
            //Libertar espaço ocupado pelo thread na entrada TLS
            _TlsClose();
            //Fechar a entrada de TLS no processo
            if( !TlsFree(tlsIDX) ) Result = FALSE;
            break;

        default:
            _tprintf(_T("LoggerDLL.dll: DllMain chamada com um motivo desconhecido (%ld)\n"), fdwReason); 
            Result = FALSE;
    }
    return Result; // Utilizado apenas para DLL_PROCESS_ATTACH

}
