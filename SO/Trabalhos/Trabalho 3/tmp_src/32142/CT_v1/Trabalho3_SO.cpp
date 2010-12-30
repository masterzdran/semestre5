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
Uma fun��o para a inicia��o do suporte do registo de hist�rico de informa��o,
da tarefa que invoca a fun��o, onde deve ser recebido a dimens�o m�xima
admitida (CreateThreadLog(�))
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
Uma fun��o para adicionar informa��o ao registo de hist�rico (AppendThreadLog(�))
*/
//ACHO QUE NAO FAZ SENTIDO O INDICE SER DADO POR PARAMETRO!!!
void AppendThreadLog(DWORD index, LPVOID appendInfo){
	LPVOID pointer = TlsGetValue(index);
	//pointer -> este ponteiro para a memoria virtual esta no inicio ou na proxima posi�ao livre???
	//acho que e a base!
	//No ponto 6 a ideia � na situa��o de erros reportar atrav�s do lan�amento de uma excep��o
	//SEH em vez de retornar um c�digo de erro (como � normalmente definido nas APIs).
	//Fazer algo semelhante ao que � poss�vel na API Heaps da WIN32
	pointer = appendInfo;
	//as mensagens v�o ficando cont�guas (umas a seguir �s outras) vendo o buffer
	//como um array de bytes. Este array de bayte � formado por um conjunto de
	//p�ginas cont�guas. Portanto se a mensagem n�o couber numa p�gina os restantes
	//bytes ficam no in�cio da p�gina seguinte (n�o sei se � esta a d�vida)
}

/*
Uma fun��o para que permita libertar um bloco de informa��o mais antigo
(segundo a l�gica de um buffer circular), e.g.  FreeThreadLog(�, nBytes)
o que significa que o espa�o dos  nBytes mais antigos � libertado
*/
bool FreeThreadLog(DWORD nBytes){
	//fazer uncommit das respectivas p�ginas mas tendo o cuidado de apenas
	//fazer uncommit de p�ginas que estejam totalmente �vazias�.
	return false;
}

/*
Uma fun��o para libertar todos os recursos ocupados pelo registo de hist�rico 
(ResetThreadLog(�))
*/

void ResetThreadLog(){
	//ResetThreadLog � colocar o log no estado inicial (quando termina a fun��o
	//CreateThreadLog), ou seja no seu caso ter apenas a regi�o reservada.
	  BOOL bSuccess;                // flag
	  LPVOID lpvBase;               // base address of the test memory
	  bSuccess = VirtualFree(
                         lpvBase,                     // base address of block
                         PAGELIMIT*dwPageSize,        // Dimens�o do bloco
                         MEM_DECOMMIT );              // decommit the pages     
}

/*
Uma fun��o para libertar o suporte do registo de hist�rico (DestroyThreadLog(�))
*/

bool DestroyThreadLog(){
	//TlsFree
	//DestroyThreadLog Aqui � que � eliminar totalmente o log
	return false;
}
