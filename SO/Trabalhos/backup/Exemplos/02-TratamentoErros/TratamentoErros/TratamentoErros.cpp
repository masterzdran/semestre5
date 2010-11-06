// TratamentoErros.cpp : Show how to handle errors

#ifndef _UNICODE
	#define _UNICODE   // for c run-time header files
#endif

#ifndef UNICODE
	#define UNICODE   // for windows API
#endif


#include "..\..\Include\SesError.h"


int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hFile = CreateFile(TEXT("DummyFile"), 0, 0, NULL, OPEN_EXISTING, 0, NULL); 
    
    if (hFile == INVALID_HANDLE_VALUE)
        FatalErrorSystem(TEXT("Erro na abertura do ficheiro %s"), TEXT("DummyFile"));
	
	return 0;
}
