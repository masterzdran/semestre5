// CriacaoTarefas.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


const int NumThreads = 5;

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
    _tsetlocale( LC_ALL, TEXT("portuguese_portugal") );

    
    _tprintf( TEXT("[main] Vou criar as tarefas.\n") );


    HANDLE hThreads[ NumThreads ];
    DWORD idThreads[ NumThreads ];

    for (int idThread=0; idThread<NumThreads; ++idThread) {
        // Utilizando a função "CreateThread"
        //hThreads[ idThread ] = CreateThread( NULL, 0, ImprimeThread, (LPVOID)idThread, NULL, &idThreads[ idThread ] );

        // Utiliznado a macro "chBEGINTHREADEX"
        //hThreads[ idThread ] = chBEGINTHREADEX( NULL, 0, ImprimeThread, (LPVOID)idThread, NULL, &idThreads[ idThread ] );

        // Utilizando a macro "chBEGINTHREADEX" e uma estrutura para passar argumentos
        ThreadArgs args[ NumThreads ];
        args[ idThread ].id = idThread;
        hThreads[ idThread ] = chBEGINTHREADEX( NULL, 0, ImprimeThreadArgsByStruct, (LPVOID)(&args[ idThread ]), NULL, &idThreads[ idThread ] );
    
        // Utilizando a macro "chBEGINTHREADEX" e uma estrutura, partilhada por todas as tarefas, 
        // para passar argumentos 
        // NOTA: perceber porque é errada esta opção
        //ThreadArgs arg;
        //arg.id = idThread;
        //hThreads[ idThread ] = chBEGINTHREADEX( NULL, 0, ImprimeThreadArgsByStruct, (LPVOID)(&arg), NULL, &idThreads[ idThread ] );
    }


    _tprintf( TEXT("[main] Esperar pela terminação das tarefas.\n") );

    WaitForMultipleObjects( NumThreads, hThreads, TRUE, INFINITE );

    _tprintf( TEXT("[main] [HANDLES abertos] Mostrar o código de terminação das tarefas.\n") );
    showThreadExitCode( hThreads );

    _tprintf( TEXT("[main] Fechar os HANDLES das tarefas.\n") );
    for (int idThread=0; idThread<NumThreads; ++idThread) {
        CloseHandle( hThreads[ idThread ] );
    }

    //_tprintf( TEXT("[main] [HANDLES fechados] Mostrar o código de terminação das tarefas.\n") );
    //showThreadExitCode( hThreads );

    _tprintf( TEXT("[main] Função principal a terminar.\nPrima uma tecla para continuar.\n") );
    _gettch();

    return 0;
}
