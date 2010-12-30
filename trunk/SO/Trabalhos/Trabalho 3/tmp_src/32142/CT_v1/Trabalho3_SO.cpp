// Trabalho3_SO.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Trab3.h"
#include <stdio.h>

#define PAGELIMIT 508768 // --------------------------------------------------->>>>>>>>>> VER COM GRUPO!!!!!!!!!!!!!!!
LPTSTR lpNxtPage;               // address of the next page to ask for
DWORD dwPages = 0;              // count of pages gotten so far
DWORD dwPageSize;               // the page size on this computer

/*
Uma função para a iniciação do suporte do registo de histórico de informação,
da tarefa que invoca a função, onde deve ser recebido a dimensão máxima
admitida (CreateThreadLog(…))
*/

INT WINAPI CreateThreadLog(int maxDimension){
	LPVOID plvoidBasePointer;
	/*
	VirtualAlloc - Memory allocated by this function is automatically initialized to zero, unless MEM_RESET is specified.
	*/
	plvoidBasePointer = VirtualAlloc(
                           (LPVOID) lpNxtPage, // next page to commit
                           maxDimension,         // page size, in bytes
                           MEM_COMMIT,         // allocate a committed page
                           PAGE_READWRITE);    // read/write access

	if (plvoidBasePointer == NULL )
    {
      printf("VirtualAlloc failed\n");
	  /*#define EXCEPTION_EXECUTE_HANDLER 1
		Exception is recognized. Transfer control
		to the exception handler by executing the
		__except compound statement, then continue
		execution after the __except block
	  */
      return EXCEPTION_EXECUTE_HANDLER;
    } 
    else {
       printf ("Allocating another page.\n");
    }

	DWORD index = TlsAlloc();

	TlsSetValue(index,plvoidBasePointer);

	/* #define EXCEPTION_CONTINUE_EXECUTION    -1
	   Exception is dismissed. Continue execution
	   at the point where the exception occurred.
	*/
	return EXCEPTION_CONTINUE_EXECUTION;
}

/*
Uma função para adicionar informação ao registo de histórico (AppendThreadLog(…))
*/
//ACHO QUE NAO FAZ SENTIDO O INDICE SER DADO POR PARAMETRO!!!
void AppendThreadLog(DWORD index, LPVOID appendInfo){
	LPVOID pointer = TlsGetValue(index);
	//pointer -> este ponteiro para a memoria virtual esta no inicio ou na proxima posiçao livre???
	//acho que e a base!
	//No ponto 6 a ideia é na situação de erros reportar através do lançamento de uma excepção
	//SEH em vez de retornar um código de erro (como é normalmente definido nas APIs).
	//Fazer algo semelhante ao que é possível na API Heaps da WIN32
	pointer = appendInfo;
	//as mensagens vão ficando contíguas (umas a seguir ás outras) vendo o buffer
	//como um array de bytes. Este array de bayte é formado por um conjunto de
	//páginas contíguas. Portanto se a mensagem não couber numa página os restantes
	//bytes ficam no início da página seguinte (não sei se é esta a dúvida)
}

/*
Uma função para que permita libertar um bloco de informação mais antigo
(segundo a lógica de um buffer circular), e.g.  FreeThreadLog(…, nBytes)
o que significa que o espaço dos  nBytes mais antigos é libertado
*/
bool FreeThreadLog(DWORD nBytes){
	//fazer uncommit das respectivas páginas mas tendo o cuidado de apenas
	//fazer uncommit de páginas que estejam totalmente “vazias”.
	return false;
}

/*
Uma função para libertar todos os recursos ocupados pelo registo de histórico 
(ResetThreadLog(…))
*/

void ResetThreadLog(){
	//ResetThreadLog é colocar o log no estado inicial (quando termina a função
	//CreateThreadLog), ou seja no seu caso ter apenas a região reservada.
	  BOOL bSuccess;                // flag
	  LPVOID lpvBase;               // base address of the test memory
	  bSuccess = VirtualFree(
                         lpvBase,                     // base address of block
                         PAGELIMIT*dwPageSize,        // Dimensão do bloco
                         MEM_DECOMMIT );              // decommit the pages     
}

/*
Uma função para libertar o suporte do registo de histórico (DestroyThreadLog(…))
*/

bool DestroyThreadLog(){
	//TlsFree
	//DestroyThreadLog Aqui é que é eliminar totalmente o log
	return false;
}
