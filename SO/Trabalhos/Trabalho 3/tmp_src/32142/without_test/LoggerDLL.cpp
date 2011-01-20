#include "LoggerDLL.h"
#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include "Include\SesError.h"


#define __DEFAULT_SIZE__	1024				//Default Log Size

/*
acabar a TLS
Finalizar o Buffer circular
ter um método para fazer print do Logger
e acabar/exportar/testar a utilização da DLL

DUVIDAS!!!

-> Onde devemos inicializar _loggerBase para que nao sejam gerados erros?


*/

//esta variável local sempre editada na funcao
DWORD _tlsIDX = -1;						 //index of last TLS

typedef struct _TlsElements {
	DWORD _pageLimit;							//number of pages
	DWORD _pageNbr;								//number of pages allocced
	DWORD _pageSize;							//size of the page

	LPVOID _loggerBase;							//address of the base virtual alloc
	LPTSTR _loggerNextPageFree;					//address of the nextpage
	SYSTEM_INFO	_systemInfo;					//system info

	LPTSTR _loggerNextFreeByte;	
	LPTSTR _loggerNextDeleteByte;				//address of the oldest byte
} TlsElements, * PTlsElements;

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
						(LPVOID) elem->_loggerNextPageFree, // next page to commit
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
	elem->_loggerNextPageFree += elem->_pageSize;

	// Continue execution where the page fault occurred.
	return EXCEPTION_CONTINUE_EXECUTION;
}

BOOL resetValues(PTlsElements elem)
{
	elem->_loggerNextPageFree=elem->_loggerNextFreeByte=elem->_loggerNextDeleteByte =(LPTSTR) elem->_loggerBase;
	return true;
}

PTlsElements GetElements(){
	if(_tlsIDX == -1) exitReport((LPTSTR)"Error index -1.");
	PTlsElements elem;
	if((elem = (PTlsElements) TlsGetValue(_tlsIDX)) == 0)
		FatalErrorSystem(_T("TlsGetValue failed!"));
	return elem;
}

void _DLL_TlsInit()
{
	if ((_tlsIDX = TlsAlloc()) == -1)
		FatalErrorSystem(_T("TlsAlloc failed!"));
}

void _DLL_TlsEnd()
{
	if( _tlsIDX != -1)
		if( !TlsFree(_tlsIDX) ) 
            FatalErrorSystem(_T("TlsFree failed!"));
}

BOOL _TlsInit(PTlsElements elem)
{
	if (! TlsSetValue(_tlsIDX, elem)) 
        FatalErrorSystem(_T("TlsSetValue failed!")); 
	return TRUE;
}

void _TlsClose()
{
	PTlsElements* p = (PTlsElements*)TlsGetValue(_tlsIDX);
	if ( p ) { 
		delete p; 
		p=NULL;
		if ( !TlsSetValue(_tlsIDX, p) )
            FatalErrorSystem(_T("TlsSetValue failed!"));
	}
}



/**
 * Uma função para a iniciação do suporte do registo de histórico de informação, 
 * da tarefa que invoca a função, onde deve ser recebido a dimensão máxima admitida (CreateThreadLog(…)) ;
 * */
void WINAPI CreateThreadLog(DWORD bytes){
	if (bytes == 0) 
		exitReport((LPTSTR)"Invalid size to allocate.");

	PTlsElements elem = (PTlsElements) TlsGetValue(_tlsIDX);
	if(!elem) elem = new TlsElements();

	//GetSystemInfo - Retrieves information about the current system.
	//A pointer to a SYSTEM_INFO structure that receives the information.
	/*
	typedef struct _SYSTEM_INFO {
		  union {
			DWORD  dwOemId;
			struct {
			  WORD wProcessorArchitecture;
			  WORD wReserved;
			};
		  };
		  DWORD     dwPageSize;
		  LPVOID    lpMinimumApplicationAddress;
		  LPVOID    lpMaximumApplicationAddress;
		  DWORD_PTR dwActiveProcessorMask;
		  DWORD     dwNumberOfProcessors;
		  DWORD     dwProcessorType;
		  DWORD     dwAllocationGranularity;
		  WORD      wProcessorLevel;
		  WORD      wProcessorRevision;
	} SYSTEM_INFO;
	*/
	GetSystemInfo(&elem->_systemInfo);
	//sei tamanho da pagina no meu sistema
	elem->_pageSize = elem->_systemInfo.dwPageSize;
	elem->_pageNbr = 0;
	//saber o numero de paginas pois e indicado por parametro o numero de bytes a ocupar
	//caso a divisao nao seja inteira entao arredondamos para cima para nao ficarem bytes em falta
	elem->_pageLimit = (DWORD) ceil((double)bytes/(double)elem->_pageSize);
	//acho que estamos a alocar mais uma pagina
	//elem->_pageLimit = bytes/elem->_pageSize + 1;
	/*
	LPVOID WINAPI VirtualAlloc(
		  __in_opt  LPVOID lpAddress,
		  __in      SIZE_T dwSize,
		  __in      DWORD flAllocationType,
		  __in      DWORD flProtect
	);
	MEM_RESERVE - Reserves a range of the process's virtual address space without allocating any actual physical storage in memory or in the paging file on disk.
	*/
	elem->_loggerBase = VirtualAlloc(NULL , elem->_pageLimit * elem->_pageSize ,
		MEM_RESERVE , PAGE_NOACCESS);

	if (elem->_loggerBase == NULL)
		exitReport((LPTSTR)"Error while use VirtualAlloc.");
	elem->_loggerNextPageFree=elem->_loggerNextFreeByte=elem->_loggerNextDeleteByte =(LPTSTR) elem->_loggerBase;

	//reservar uma entrada na TLS para que este espaço reservado ser associado a 1 thread
	_DLL_TlsInit();
	_TlsInit(elem);
}


/**
 * Uma função para adicionar informação ao registo de histórico (AppendThreadLog(…));
 * assumimos que mensagem não é maior que 
 * */
void WINAPI AppendThreadLog(LPTSTR message){
	PTlsElements elem = GetElements();
	if (elem->_loggerBase == NULL)
		CreateThreadLog(__DEFAULT_SIZE__);
	//saber tamanho da string
	DWORD size = _tcsclen(message);
	//Usar controlo de excepções
	//Usar memcopy para copiar a mensagem para o endereço de _loggerNextPageFree
	//Se falhar a excepção chamar a função que vai fazer commit da proxima pagina 
	//ou paginas suficientes para agregar as páginas
	//Actualizar o valor de _loggerNextPageFree para o proximo byte apos ter sido colocada a mensagem
	bool isIn = false;
	while(!isIn){
		__try
		{
			//copia mensagem os proximos bytes livres
			memccpy(elem->_loggerNextFreeByte,message,0,size);
			//se der excepçao significa que houve uma violaçao de acesso, por isso, temos de usar 
			//a proxima pagina - operacao do __except
			//se nao der excepcao - actualizar apontador
			elem->_loggerNextFreeByte += size;
			//condicao de saida do while pois ja foi efectuado o append
			isIn = true;
		}
		__except ( PageFaultExceptionFilter( GetExceptionCode() , GetExceptionInformation() , elem) )
		{
			if(elem-> _pageNbr == elem->_pageLimit){
				//aplicamos a teoria do array circular, ou seja, vamos começar a subrepor valores
				DWORD numberOfBytesFree = (char*) elem->_loggerNextPageFree - (char*) elem->_loggerNextFreeByte;
				//string aux = (string)message.substr(0,numberOfBytesFree);
				memccpy(elem->_loggerNextFreeByte,message,0,numberOfBytesFree);
				//actualizar ponteiro para os restantes bytes a serem inseridos
				message += numberOfBytesFree;
				//colocar _loggerNextFreeByte a apontar para 1º byte do array circular
				elem->_loggerNextFreeByte = (LPTSTR) elem->_loggerBase;
				
			} 
			else{
				//fazemos commit a proxima pagina
				elem->_loggerNextPageFree += elem->_pageSize;
				//permite escrever na pagina commited
				VirtualAlloc(elem->_loggerNextPageFree, elem->_pageSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
				elem->_pageNbr += 1;
			}
		}
	}

	_TlsInit(elem);
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
	if (bytes == 0 ) return;
	PTlsElements elem = GetElements();
	//_loggerNextDeleteByte estara sempre a apontar para o inicio de uma pagina
	LPTSTR firstToDelete = elem->_loggerNextDeleteByte;
	LPTSTR lastToDelete = elem->_loggerNextDeleteByte + bytes;
	//numero de paginas a "apagar"
	DWORD numberOfPages = bytes/elem->_pageSize;
	DWORD delay = 0;
	if(lastToDelete > (LPTSTR) elem->_loggerNextFreeByte){
		//saber quantas paginas estao entre estes dois ponteiros - nao devem ser "apagadas"
		delay = (lastToDelete - (LPTSTR) elem->_loggerNextFreeByte)/elem->_pageSize;
	}
	//retirar do numero total as paginas que nao podem ser "apagadas"
	numberOfPages = numberOfPages - delay;

	VirtualFree(firstToDelete, numberOfPages*elem->_pageSize, MEM_DECOMMIT);

	//actualizar indice elem->_loggerNextDeleteByte
	elem->_loggerNextDeleteByte = elem->_loggerNextDeleteByte + numberOfPages*elem->_pageSize;

	//guardar novos valores da estrutura na TLS
	_TlsInit(elem);
}

/**
 * Uma função para libertar todos os recursos ocupados pelo registo de histórico (ResetThreadLog(…));
 * ResetThreadLog é colocar o log no estado inicial (quando termina a função CreateThreadLog),
 * ou seja no seu caso ter apenas a região reservada. 
 * */
BOOL WINAPI ResetThreadLog(){
	PTlsElements elem = GetElements();
	return (VirtualFree(elem->_loggerBase,elem->_pageLimit * elem->_pageSize, MEM_DECOMMIT))?resetValues(elem):false;
}

/**
 * Uma função para libertar o suporte do registo de histórico (DestroyThreadLog(…)).
 * DestroyThreadLog deve eliminar totalmente o log
 * */
BOOL WINAPI DestroyThreadLog(){
	PTlsElements elem = GetElements();
	bool ret = VirtualFree(elem->_loggerBase, elem->_pageLimit * elem->_pageSize ,MEM_RELEASE);
	delete elem;
	return ret;
}
