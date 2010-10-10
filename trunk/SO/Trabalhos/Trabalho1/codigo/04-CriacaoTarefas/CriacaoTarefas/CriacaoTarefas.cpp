// CriacaoTarefas.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

int NumThreads = -1;

int x;


typedef struct _ThreadArgs {
  DWORD id;
} ThreadArgs, * PThreadArgs;


DWORD WINAPI ImprimeThread(LPVOID args)
{
    int id = (int)args;
    _tprintf( TEXT("[Thread nº %2d] Olá Mundo.\n"), id);

    //ExitThread( (DWORD)id );
    //chENDTHREADEX( (DWORD)id );

    return (DWORD)id;
}


DWORD WINAPI ImprimeThreadArgsByStruct(LPVOID _args)
{
    PThreadArgs args = (PThreadArgs)_args;
    _tprintf( TEXT("[Thread nº %2d] Olá Mundo.\n"), args->id);

    //chENDTHREADEX( args->id );

    return args->id;
}


void showThreadExitCode(HANDLE * hThreads)
{
  DWORD exitCode;

  for(int idThread=0; idThread<NumThreads; ++idThread) {

    if (GetExitCodeThread(hThreads[idThread], &exitCode)==0) {
        ReportErrorSystem( TEXT("Erro ao obter o código de terminação da tarefa %d"), idThread);
    }
    else {
        if ( exitCode==STILL_ACTIVE ) {
            _tprintf( TEXT("A tarefa %d ainda se encontra em execução.\n"), idThread );
        }
        else {
            _tprintf( TEXT("A tarefa %d terminou com o valor %d.\n"), idThread, exitCode );
        }
    }
  }
} 


int _tmain(int argc, _TCHAR* argv[])
{
	if(argc < 2){
		_tprintf(TEXT("CriacaoTarefas <number-of-threads> <time>\n\n"));		
		return -1;
	}
    _tsetlocale( LC_ALL, TEXT("portuguese_portugal") );
    _tprintf( TEXT("[main] Vou criar as tarefas.\n") );

	DWORD num = _wtoi(argv[1]);
	DWORD time = _wtoi(argv[2]);
	
	NumThreads = num;

	HANDLE* hThreads = (HANDLE*) calloc(num,sizeof(HANDLE));
	DWORD* idThreads = (DWORD *)calloc(time,sizeof(DWORD));

    //HANDLE hThreads[ NumThreads ];
    //DWORD idThreads[ NumThreads ];
	//ThreadArgs args[ num ];

	ThreadArgs* args = (ThreadArgs*)calloc(num,sizeof(ThreadArgs));

    for (DWORD idThread=0; idThread<num; ++idThread) {
		//_tprintf(TEXT("FOR NAO ESTA A FAZER NADA!!\n"));
        // Utilizando a função "CreateThread"
        //hThreads[ idThread ] = CreateThread( NULL, 0, ImprimeThread, (LPVOID)idThread, NULL, &idThreads[ idThread ] );

        // Utiliznado a macro "chBEGINTHREADEX"
        //hThreads[ idThread ] = chBEGINTHREADEX( NULL, 0, ImprimeThread, (LPVOID)idThread, NULL, &idThreads[ idThread ] );

        // Utilizando a macro "chBEGINTHREADEX" e uma estrutura para passar argumentos

        args[idThread].id = idThread;
        hThreads[idThread] = chBEGINTHREADEX(NULL,
											0,
											ImprimeThreadArgsByStruct,
											(LPVOID)(&args[ idThread ]),
											NULL, 
											&idThreads[ idThread ] );
    


        // Utilizando a macro "chBEGINTHREADEX" e uma estrutura, partilhada por todas as tarefas, 
        // para passar argumentos 
        // NOTA: perceber porque é errada esta opção
        //ThreadArgs arg;
        //arg.id = idThread;
        //hThreads[ idThread ] = chBEGINTHREADEX( NULL, 0, ImprimeThreadArgsByStruct, (LPVOID)(&arg), NULL, &idThreads[ idThread ] );
    }


    _tprintf( TEXT("[main] Esperar pela terminação das tarefas através da função Sleep.\n") );

    //WaitForMultipleObjects( num, hThreads, TRUE, INFINITE );
	Sleep(time);

    _tprintf( TEXT("[main] [HANDLES abertos] Mostrar o código de terminação das tarefas.\n") );
    showThreadExitCode( hThreads );

    _tprintf( TEXT("[main] Fechar os HANDLES das tarefas.\n") );
    for (int idThread=0; idThread<NumThreads; ++idThread) {
        CloseHandle( hThreads[ idThread ] );
    }

    _tprintf( TEXT("[main] [HANDLES fechados]Não está a mostrar o código de terminação das tarefas.\n") );
    //showThreadExitCode( hThreads ); //--> esta a dar erro ainda nao percebi porque... :S


    _tprintf( TEXT("[main] Função principal a terminar.\nPrima uma tecla para continuar.\n") );
    _gettch();

	free(args);
	free(hThreads);
	free(idThreads);
    return 0;
}
