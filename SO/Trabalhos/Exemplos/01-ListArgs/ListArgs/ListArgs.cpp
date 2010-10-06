// ListArgs.cpp : Print the arguments on the console. 

#ifndef _UNICODE
	#define _UNICODE   // for c run-time header files
#endif

#include <tchar.h>   // for _tprintf definition _TEXT
#include <stdio.h>   // for printf and wprintf
#include <windows.h>
#include <locale.h>

int _tmain(int argc, TCHAR* argv[])
{
	_tsetlocale(LC_ALL, _T("portuguese_portugal"));

	_tprintf( _TEXT("Listagem dos argumentos:\n") );
	for(int i=0; i<argc; ++i) { 
		_tprintf( _TEXT("Argumento[%d] = %s\n"), i, argv[i]);
	}

	return 0;
}
