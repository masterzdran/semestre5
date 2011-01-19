#include "Include\BeginThreadex.h"
#include "Include\LoggerDLL.h"
#include <windows.h>
#include <locale.h>
#include <tchar.h>
#include <stdio.h>
#define nbrTH  4

DWORD WINAPI threadProc(LPVOID bytes)
{
	CreateThreadLog((DWORD)bytes);
	AppendThreadLog((LPTSTR)"qwertyuiopasdfghjklz<xcvbnm");
	FreeThreadLog(27);
	BOOL r;
	if(ResetThreadLog()){
		r = DestroyThreadLog();
		if (r = FALSE)
			_tprintf(_T("Erro no DestroyLog\n"));

	}else{
		  _tprintf(_T("Erro no ResetLog\n"));
	}


    return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{
    _tsetlocale(LC_ALL, _T("portuguese_portugal"));
    // Criar as tarefas

    HANDLE thr[nbrTH];
    DWORD thId;
	DWORD bytes = 32 * 1024;

    for (int i=0; i < nbrTH; ++i) {
        
        thr[i]=chBEGINTHREADEX(NULL, 0, (LPTHREAD_START_ROUTINE)threadProc, (LPVOID)bytes, CREATE_SUSPENDED, &thId);
        if (thr[i] == NULL) 
            _tprintf(_T("Criação da tarefa %d (%d)\n"), i, GetLastError());
    }
  

    _tprintf(_T("Tarefas criadas. Esperar pelo término das tarefas.\n"));


    for (int i=0; i<nbrTH; ++i) {
        ResumeThread(thr[i]);
    }

    //Esperar que as tarefas terminem
    DWORD waitret = WaitForMultipleObjects( nbrTH,          // number of handles in array
                                            thr,        // object-handle array
                                            TRUE,       // wait option
                                            INFINITE    // time-out interval
                                          );
    if ( waitret == WAIT_FAILED ) 
        _tprintf(_T("Erro no WaitForMultipleObjects (%d)\n"), GetLastError());

    
	    for (int i=0; i<nbrTH; ++i) {
			CloseHandle(thr[i]);
		}
    _tprintf(_T("Enter para terminar...\n"));

    _gettchar();
}

